#pragma once

#include "globals.hpp"
#include "cGraphics.hpp"
#include "cTexture.hpp"

class cMenu {

	public:

			cMenu();
			~cMenu();

			void keyPressed(char c);
			void render();
			
			bool gameSelected();

	private:
			int button;
			bool gameOn;
			GLuint vertexbuffer;
			GLuint uvbuffer;
			GLuint programID;
			GLuint textureID;
			GLuint mvp_handle;

			void initGL();
};
