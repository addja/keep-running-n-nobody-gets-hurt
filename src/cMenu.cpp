// menu class

#include "include/cMenu.hpp"

cMenu::cMenu() {
	initGL();
	title_index = death_index = next_index = 3;
	title_dir = death_dir = next_dir = 1;
	delay = 0;
}

cMenu::~cMenu() {
	glDeleteBuffers(1, &full_window_vertexbuffer);
	glDeleteBuffers(1, &semi_window_vertexbuffer);                                                                                                   
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &textureID);
	glDeleteTextures(1, &loading_tex);
	glDeleteTextures(1, &death_tex[0]);
	glDeleteTextures(1, &death_tex[1]);
	glDeleteTextures(1, &death_tex[2]);
	glDeleteTextures(1, &death_tex[3]);
	glDeleteTextures(1, &death_tex[4]);
	glDeleteTextures(1, &title_tex[0]);
	glDeleteTextures(1, &title_tex[1]);
	glDeleteTextures(1, &title_tex[2]);
	glDeleteTextures(1, &title_tex[3]);
	glDeleteTextures(1, &title_tex[4]);
	glDeleteTextures(1, &next_tex[0]);
	glDeleteTextures(1, &next_tex[1]);
	glDeleteTextures(1, &next_tex[2]);
	glDeleteTextures(1, &next_tex[3]);
	glDeleteTextures(1, &next_tex[4]);
	glDeleteTextures(1, &back_tex);
}

void cMenu::update() {
	if (delay < MENU_ANIMATION_DELAY) {
		delay += 1;
	} else {
		switch (state) {
			case MENU_STATE_MENU:
				title_index += title_dir;
				if (title_index == MENU_ANIMATION_LENGTH) {
					title_dir = -1;
					title_index = MENU_ANIMATION_LENGTH - 1;
				} else if (title_index == -1) {
					title_dir = 1;
					title_index = 0;
				}
				break;
			case MENU_STATE_DEATH:
				death_index += death_dir;
				if (death_index == MENU_ANIMATION_LENGTH) {
					death_dir = -1;
					death_index = MENU_ANIMATION_LENGTH - 1;
				} else if (death_index == -1) {
					death_dir = 1;
					death_index = 0;
				}
				break;
			case MENU_STATE_NEXT_LEVEL:
				next_index += next_dir;
				if (next_index == MENU_ANIMATION_LENGTH) {
					next_dir = -1;
					next_index = MENU_ANIMATION_LENGTH - 1;
				} else if (next_index == -1) {
					next_dir = 1;
					next_index = 0;
				}
				break;
			default:
				break;
		}
		delay = 0;
	}
	
}

void cMenu::render() {

	glClear(GL_DEPTH_BUFFER_BIT);

   	glUseProgram(programID);

   	// Send our transformation to the currently bound shader, 
   	// in the "MVP" unifor
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
							glm::vec3(0,0,1), // Camera is at (0,0,1), in World Space
							glm::vec3(0,0,0), // and looks at the origin
							glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);	
	glm::mat4 MVP = Projection * View * glm::mat4(1);
   	glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &MVP[0][0]);

   	glActiveTexture(GL_TEXTURE0);

   	if (state == MENU_STATE_LOADING) {
   		glBindTexture(GL_TEXTURE_2D, loading_tex);
   	} else if (state == MENU_STATE_MENU) {
   		glBindTexture(GL_TEXTURE_2D, title_tex[title_index]);
   	} else {
   		glBindTexture(GL_TEXTURE_2D, back_tex);	
   	}

   	glUniform1i(textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, full_window_vertexbuffer);

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

	if (state == MENU_STATE_DEATH || state == MENU_STATE_NEXT_LEVEL || state == MENU_STATE_WIN) {
		glClear(GL_DEPTH_BUFFER_BIT);

	   	if (state == MENU_STATE_DEATH) {
	   		glBindTexture(GL_TEXTURE_2D, death_tex[death_index]);
	   	} else if (state == MENU_STATE_NEXT_LEVEL) {
	   		glBindTexture(GL_TEXTURE_2D, next_tex[next_index]);	
	   	} else {
	   		glBindTexture(GL_TEXTURE_2D, win_tex);	
	   	}

	   	glUniform1i(textureID, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, semi_window_vertexbuffer);

		glVertexAttribPointer(
			0,           // attribute. No particular reason for 0, but must match the layout in the shader.
			3,           // size
			GL_FLOAT,    // type
			GL_FALSE,    // normalized?
			0,           // stride
			(void*)0     // array buffer offset
		);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableVertexAttribArray(0); 
	}


	glDisableVertexAttribArray(1);
}

void cMenu::initGL() {
	GLfloat vertices[] = {
		0.65,0.42,0,
		0.65,-0.42,0,
		-0.65,-0.42,0,
		-0.65,0.42,0
	};
	
	glGenBuffers(1, &full_window_vertexbuffer);                                                                                                         
	glBindBuffer(GL_ARRAY_BUFFER, full_window_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) , vertices, GL_STATIC_DRAW);

	GLfloat vertices2[] = {
		0.65,0.42,-0.5,
		0.65,-0.42,-0.5,
		-0.65,-0.42,-0.5,
		-0.65,0.42,-0.5
	};

	glGenBuffers(1, &semi_window_vertexbuffer);                                                                                                         
	glBindBuffer(GL_ARRAY_BUFFER, semi_window_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2) , vertices2, GL_STATIC_DRAW);

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

	loading_tex = loadTex(TEX_LOADING_PATH);	
}

void cMenu::loadAssets() {
	back_tex = loadTex(TEX_WHITE_BACK_PATH);
	win_tex = loadTex(TEX_WIN_PATH);

	title_tex[0] = loadTex(TEX_TITLE_1_PATH);
	title_tex[1] = loadTex(TEX_TITLE_2_PATH);
	title_tex[2] = loadTex(TEX_TITLE_3_PATH);
	title_tex[3] = loadTex(TEX_TITLE_4_PATH);
	title_tex[4] = loadTex(TEX_TITLE_5_PATH);
	death_tex[0] = loadTex(TEX_DEATH_1_PATH);
	death_tex[1] = loadTex(TEX_DEATH_2_PATH);
	death_tex[2] = loadTex(TEX_DEATH_3_PATH);
	death_tex[3] = loadTex(TEX_DEATH_4_PATH);
	death_tex[4] = loadTex(TEX_DEATH_5_PATH);
	next_tex[0] = loadTex(TEX_NEXT_1_PATH);
	next_tex[1] = loadTex(TEX_NEXT_2_PATH);
	next_tex[2] = loadTex(TEX_NEXT_3_PATH);
	next_tex[3] = loadTex(TEX_NEXT_4_PATH);
	next_tex[4] = loadTex(TEX_NEXT_5_PATH);	
}

int cMenu::getState() {
	return state;
}

void cMenu::setState(int st) {
	state = st;
}

int cMenu::getDelay() {
	return delay;
}

void cMenu::setDelay(int d) {
	delay = d;
}