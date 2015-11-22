#pragma once

#include "globals.hpp"
#include "cGraphics.hpp"

class cGame {
	
	public:
		cGame();
		~cGame();
	
		void update(float dt);
		void render();		

	private:
		GLuint VertexArrayID;
		GLuint vertexbuffer; 
		GLuint programID;		// vertex and fragment shaders		

		void initOpenGL();
};
