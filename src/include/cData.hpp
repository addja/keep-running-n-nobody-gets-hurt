#pragma once

#include "globals.hpp"
#include "cTexture.hpp"
#include "cModel.hpp"
#include "cSound.hpp"
#include "cMusic.hpp"

class cData {
	
	public:
		glm::vec3 cameraP;
		int front;
		float rotating_angle;
		bool blur;

		cData();
		~cData();

		void loadTexture(int i, std::string filename);
		void loadDDS(int i, char * filename);
		GLuint getTextureID(int i);

		bool loadSound(int sound, const std::string filename);
		bool loadMusic(int music, const std::string filename);

		void playSound(int sound);
		void playMusic(int music);
		void stopMusic(int music);

		void loadModel(int i, std::string filename);
		void drawModel(int i, GLuint texture, glm::vec3 p, glm::vec3 r, glm::vec3 s, float a);

	private:
		GLuint texture[N_TEXTURES];
		cModel models[N_MODELS];
		cSound sound[NUM_SOUNDS];
		cMusic music[NUM_MUSICS];	
};
