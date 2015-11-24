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
		GLuint colorbuffer; 
		GLuint programID;		// vertex and fragment shaders		
		GLuint mvp_handle;		// mvp glsl uniform identifier	

		void initOpenGL();
};
