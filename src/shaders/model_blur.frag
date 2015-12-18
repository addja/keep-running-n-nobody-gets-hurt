#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Ouput data
out vec4 color;
out vec4 FragmentColor;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;

const vec2 gaussFilter[7] = 
vec2[]( 
	vec2(-3.0,	0.015625),
	vec2(-2.0,	0.09375),
	vec2(-1.0,	0.234375),
	vec2(0.0,	0.3125),
	vec2(1.0,	0.234375),
	vec2(2.0,	0.09375),
	vec2(3.0,	0.015625)
);

void main(){

	// Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 600.0f;
	vec2 new_uv;
	new_uv = vec2(UV.x, 1.0 - UV.y);

	color = vec4(0.0);
	vec2 u_Scale = vec2(0, 1.0/10);
	for( int i = 0; i < 7; i++ )
	{
		color += texture2D( myTextureSampler, vec2( new_uv.x+gaussFilter[i].x*u_Scale.x, new_uv.y+gaussFilter[i].x*u_Scale.y ) )*gaussFilter[i].y;
	}

	u_Scale = vec2(1.0/10, 0 );
 	for( int i = 0; i < 7; i++ )
	{
		color += texture2D( myTextureSampler, vec2( new_uv.x+gaussFilter[i].x*u_Scale.x, new_uv.y+gaussFilter[i].x*u_Scale.y ) )*gaussFilter[i].y;
	}

	// Material properties
	vec4 text_color = color;
	vec3 MaterialDiffuseColor = text_color.rgb;
	vec3 MaterialAmbientColor = vec3(0.5,0.5,0.5) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.9,0.9,0.9);

	// Distance to the light
	float distance = length( LightPosition_worldspace - Position_worldspace );

	// Normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace );
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle refle cts the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	vec3 n_color = 
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);

	color = vec4(n_color, text_color.a);
}