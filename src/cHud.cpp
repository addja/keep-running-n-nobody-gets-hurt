// menu class

#include "include/cHud.hpp"

cHud::cHud() {
	initGL();
	timer_origin = 0;
	coins = 0;
}

cHud::~cHud() {
	glDeleteBuffers(1, &vertexbuffer);                                                                                             
	glDeleteBuffers(1, &back_vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &back_uvbuffer);
	glDeleteProgram(programID);
	glDeleteProgram(programID_back);
	glDeleteTextures(1, &textureID);
	glDeleteTextures(1, &text_tex);
	glDeleteTextures(1, &back_tex);
}

void cHud::update(float dt) {
	timer_origin += dt;	
}

void cHud::render() {
	glClear(GL_DEPTH_BUFFER_BIT);

	glUseProgram(programID_back);

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
							glm::vec3(0,0,1), // Camera is at (0,0,1), in World Space
							glm::vec3(0,0,0), // and looks at the origin
							glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);	
	glm::mat4 MVP = Projection * View * glm::mat4(1);
   	glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &MVP[0][0]);

   	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, back_tex);	
   	glUniform1i(textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, back_vertexbuffer);

	glVertexAttribPointer(
		0,           // attribute. No particular reason for 0, but must match the layout in the shader.
		3,           // size
		GL_FLOAT,    // type
		GL_FALSE,    // normalized?
		0,           // stride
		(void*)0     // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, back_uvbuffer);
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

	char text[256];
	sprintf(text,"%.2fs", timer_origin);
	printText(20,WNDW_HEIGHT - 60,50,text);

	sprintf(text,"%d coins", coins);
	printText(20,WNDW_HEIGHT - 110,50,text);	
}

void cHud::printText(int x, int y, int size, char * text) {
	glClear(GL_DEPTH_BUFFER_BIT);

   	glUseProgram(programID);

   	unsigned int length = strlen(text);
   	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
   	for ( unsigned int i=0 ; i<length ; i++ ){
		
		glm::vec2 vertex_up_left    = glm::vec2( x+i*(size/2-size/6)    , y+size );
		glm::vec2 vertex_up_right   = glm::vec2( x+i*(size/2-size/6)+size, y+size );
		glm::vec2 vertex_down_right = glm::vec2( x+i*(size/2-size/6)+size, y      );
		glm::vec2 vertex_down_left  = glm::vec2( x+i*(size/2-size/6)     , y      );

		vertices.push_back(vertex_up_left   );
		vertices.push_back(vertex_down_left );
		vertices.push_back(vertex_up_right  );

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = text[i];
		float uv_x = (character%16)/16.0f;
		float uv_y = (character/16)/16.0f;

		glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
		glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
		glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
		UVs.push_back(uv_up_left   );
		UVs.push_back(uv_down_left );
		UVs.push_back(uv_up_right  );

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

   	glActiveTexture(GL_TEXTURE0);
   	glBindTexture(GL_TEXTURE_2D, text_tex);
   	glUniform1i(textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void cHud::initGL() {
	glGenBuffers(1, &vertexbuffer);	
	glGenBuffers(1, &uvbuffer);  

	GLfloat vertices[] = {
		0.65,0.42,0,
		0.65,-0.42,0,
		-0.65,-0.42,0,
		-0.65,0.42,0
	};

	glGenBuffers(1, &back_vertexbuffer);                                                                                                         
	glBindBuffer(GL_ARRAY_BUFFER, back_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) , vertices, GL_STATIC_DRAW);

	GLfloat uv[] = {
		1,0,
		1,1,
		0,1,
		0,0
	};
	
	glGenBuffers(1, &back_uvbuffer);                                                                                                         
	glBindBuffer(GL_ARRAY_BUFFER, back_uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv) , uv, GL_STATIC_DRAW);                                                                                                       

	programID = loadShaders("src/shaders/hud.vert", "src/shaders/hud.frag");
	programID_back = loadShaders("src/shaders/menu.vert", "src/shaders/menu.frag");

	textureID  = glGetUniformLocation(programID, "myTextureSampler");
	textureID2  = glGetUniformLocation(programID_back, "myTextureSampler");
	mvp_handle = glGetUniformLocation(programID_back, "MVP");
}

void cHud::loadAssets() {
	text_tex = loadTex(TEX_TEXT_PATH);
	back_tex = loadTex(TEX_HUD_PATH);
}

float cHud::getTimerOrigin() {
	return timer_origin;
}

void cHud::setTimerOrigin(float t) {
	timer_origin = t;
}

int cHud::getCoins() {
	return coins;
}

void cHud::setCoins(int c) {
	coins = c;
}

void cHud::increaseCoins() {
	++coins;
}