#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Interpolated values from the vertex shaders
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(vertexPosition_modelspace,1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}
