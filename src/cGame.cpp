// Game class

#include "include/cGame.hpp"

cGame::cGame() {
	initOpenGL();
}

cGame::~cGame() {}

void cGame::update(float dt) {

}

void cGame::render() {

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use shader
	glUseProgram(programID);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);

}

void cGame::initOpenGL() {

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);	
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	    -1.0f, -1.0f, 0.0f,
	    1.0f, -1.0f, 0.0f,
	    0.0f,  1.0f, 0.0f,
	};
	
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	// Clear color screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "src/shaders/simple.vert", "src/shaders/simple.frag" );
}
