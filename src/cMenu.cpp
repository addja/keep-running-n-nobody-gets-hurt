// menu class

#include "include/cMenu.hpp"

cMenu::cMenu() {
	button = -1;
	gameOn = false;
	initGL();
}

cMenu::~cMenu() {
	glDeleteBuffers(1, &vertexbuffer);                                                                                                      
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &textureID);
}

void cMenu::keyPressed(char c) {

}

void cMenu::render() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

   	glUseProgram(programID);

   	// Send our transformation to the currently bound shader, 
   	// in the "MVP" unifor
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
							glm::vec3(0,0,1), // Camera is at (4,3,3), in World Space
							glm::vec3(0,0,0), // and looks at the origin
							glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);	
	glm::mat4 MVP = Projection * View * glm::mat4(1);
   	glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &MVP[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, loadTex(TEX_TITLE_PATH));
 	glUniform1i(textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,           // attribute. No particular reason for 0, but must match the layout in the shader.
		3,           // size
		GL_FLOAT,    // type
		GL_FALSE,    // normalized?
		0,           // stride
		(void*)0     // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
						     1,           // attribute. No particular reason for 1, but must match the layout in the shader.
					 	     2,           // size
					 	     GL_FLOAT,    // type
					 	     GL_FALSE,    // normalized?
					 	     0,           // stride
					 	     (void*)0     // array buffer offset
 	);

	glDrawArrays(GL_QUADS, 0, 4); 

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

bool cMenu::gameSelected() {
	return gameOn;
}

void cMenu::initGL() {
 	// Initialize GLEW                                                                                                                            
	if (glewInit() != GLEW_OK) {
    	fprintf(stderr, "Failed to initialize GLEW\n");
	}

	GLfloat vertices[] = {
		0.25,0.25,0,
		0.25,0,0,
		-0.25,0,0,
		-0.25,0.25,0
	};
	
	glGenBuffers(1, &vertexbuffer);                                                                                                         
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) , vertices, GL_STATIC_DRAW);


	GLfloat uv[] = {
		1,0,
		1,1,
		0,1,
		0,0
	};
	
	glGenBuffers(1, &uvbuffer);                                                                                                         
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv) , uv, GL_STATIC_DRAW);
	programID = loadShaders("src/shaders/menu.vert", "src/shaders/menu.frag");

	textureID  = glGetUniformLocation(programID, "myTextureSampler");
	mvp_handle = glGetUniformLocation(programID, "MVP");
}
