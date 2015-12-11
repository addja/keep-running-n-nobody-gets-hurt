#pragma once

#include "globals.hpp"
#include "cTexture.hpp"
#include "cModel.hpp"

class cData {
	
	public:
		glm::vec3 cameraP;
		int front;
		float rotating_angle;

		cData();
		~cData();

		void loadTexture(int i, std::string filename);
		void loadDDS(int i, char * filename);
		GLuint getTextureID(int i);

		void loadModel(int i, std::string filename);
		void drawModel(int i, GLuint texture, glm::vec3 p, glm::vec3 r, glm::vec3 s, float a);

	private:
		GLuint texture[N_TEXTURES];
		cModel models[N_MODELS];	
};
