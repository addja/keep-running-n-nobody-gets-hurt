#pragma once

#include "globals.hpp"
#include "cGraphics.hpp"
#include "cData.hpp"

class cGame {
	
	public:
		cGame();
		~cGame();
	
		void update(float dt);
		void render();		

	private:
		GLuint vertexArrayID;
		GLuint vertexbuffer; 
		GLuint uvbuffer; 
		GLuint programID;		// vertex and fragment shaders		
		GLuint mvp_handle;		// mvp glsl uniform identifier	
		GLuint textureID;

		cData data;

		void initOpenGL();
		void initGame();

};
