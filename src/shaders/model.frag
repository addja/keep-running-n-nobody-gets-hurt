#version 330 core

out vec3 color;

// Interpolated values from the vertex shaders
in vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main() {
	// Output color = color of the texture at the specified UV
	color = texture( myTextureSampler, UV).rgb;
	//color = vec3(1,0,0);
}
