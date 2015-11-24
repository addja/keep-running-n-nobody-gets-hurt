#pragma once

#include "globals.hpp"
#include "cTexture.hpp"

class cData {
	
	public:
		cData();
		~cData();

		void loadTexture(int i, std::string filename);
		GLuint getTextureID(int i);

	private:
		GLuint texture[N_TEXTURES];

};
