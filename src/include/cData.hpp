#pragma once

#include "globals.hpp"
#include "cTexture.hpp"
#include "cModel.hpp"

class cData {
	
	public:
		cData();
		~cData();

		void loadTexture(int i, std::string filename);
		GLuint getTextureID(int i);

		void loadModel(int i, std::string filename);

	private:
		GLuint texture[N_TEXTURES];
		cModel models[N_MODELS];	
};
