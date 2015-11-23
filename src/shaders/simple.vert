#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(vertexPosition_modelspace,1);
}
