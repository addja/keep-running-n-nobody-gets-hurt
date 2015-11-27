// Game class

#include "include/cGame.hpp"

cGame::cGame() {
	initOpenGL();
	initGame();
}

cGame::~cGame() {
	// Cleanup VBO and shader
 	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteTextures(1, &textureID);
}

void cGame::update(float dt) {

}

void cGame::render() {

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) WNDW_WIDTH / (float)WNDW_HEIGHT, 0.1f, 100.0f);
	
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	glm::mat4 View = glm::lookAt(
	               glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
	               glm::vec3(0,0,0), // and looks at the origin
	               glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	               );
	
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around


	// Use shader
	glUseProgram(programID);
	
	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data.getTextureID(TEX_CUBE));
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(textureID, 0);

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
	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
	     1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
	     2,                                // size
	     GL_FLOAT,                         // type
	     GL_FALSE,                         // normalized?
	     0,                                // stride
	     (void*)0                          // array buffer offset
	);	
	
	glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void cGame::initOpenGL() {

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);	

	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Texture coordinates.
	static const GLfloat g_uv_buffer_data[] = {
		0.000000f, 1.0f-0.000000f,
		0.000000f, 1.0f-0.333333f,
		0.333333f, 1.0f-0.333333f,
		1.000000f, 1.0f-0.000000f,
		0.666666f, 1.0f-0.333333f,
		1.000000f, 1.0f-0.333333f,
		0.666666f, 1.0f-0.333333f,
		0.333333f, 1.0f-0.666666f,
		0.666666f, 1.0f-0.666666f,
		1.000000f, 1.0f-0.000000f,
		0.666666f, 1.0f-0.000000f,
		0.666666f, 1.0f-0.333333f,
		0.000000f, 1.0f-0.000000f,
		0.333333f, 1.0f-0.333333f,
		0.333333f, 1.0f-0.000000f,
		0.666666f, 1.0f-0.333333f,
		0.333333f, 1.0f-0.333333f,
		0.333333f, 1.0f-0.666666f,
		1.000000f, 1.0f-0.666666f,
		1.000000f, 1.0f-0.333333f,
		0.666666f, 1.0f-0.333333f,
		0.666666f, 1.0f-0.000000f,
		0.333333f, 1.0f-0.333333f,
		0.666666f, 1.0f-0.333333f,
		0.333333f, 1.0f-0.333333f,
		0.666666f, 1.0f-0.000000f,
		0.333333f, 1.0f-0.000000f,
		0.000000f, 1.0f-0.333333f,
		0.000000f, 1.0f-0.666666f,
		0.333333f, 1.0f-0.666666f,
		0.000000f, 1.0f-0.333333f,
		0.333333f, 1.0f-0.666666f,
		0.333333f, 1.0f-0.333333f,
		0.666666f, 1.0f-0.666666f,
		1.000000f, 1.0f-0.666666f,
		0.666666f, 1.0f-0.333333f
	};

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	
	// Clear color screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Create and compile our GLSL program from the shaders
	programID = loadShaders( "src/shaders/simple.vert", "src/shaders/simple.frag" );
	
	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	mvp_handle = glGetUniformLocation(programID, "MVP");
	textureID  = glGetUniformLocation(programID, "myTextureSampler");

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);	

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
}

void cGame::initGame() {
	data = cData();
	data.loadTexture(TEX_CUBE,TEX_CUBE_PATH);
	//data.loadTexture(TEX_CHAR,TEX_CHAR_PATH);
	data.loadModel(MODEL_CHAR,MODEL_CHAR_PATH);
}
