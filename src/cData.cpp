// intermediate with complex media data

#include "include/cData.hpp"

cData::cData() {
	cameraP = glm::vec3(0,0,0);
	front = 1;
	rotating_angle = PI/4;
}

cData::~cData() {}

void cData::loadTexture(int i, std::string filename) {
	texture[i] = loadTex(filename);
}

void cData::loadDDS(int i, char * filename) {
	texture[i] = loadDDSTex(filename);
}

GLuint cData::getTextureID(int i) {
	return texture[i];
}

bool cData::loadSound(int s, const std::string filename) {
	if (sound[s].load(filename)) return true;
	return false;
}

bool cData::loadMusic(int m, const std::string filename) {
	if (music[m].load(filename)) return true;
	return false;
}

void cData::playSound(int s) {
	sound[s].play();
}

void cData::playMusic(int m) {
	music[m].play();
}

void cData::stopMusic(int m) {
	music[m].stop();
}

void cData::loadModel(int i, std::string filename) {
	models[i].loadModel(filename);
}

void cData::drawModel(int i, GLuint texture, glm::vec3 p, glm::vec3 r, glm::vec3 s, float a) {
	models[i].render(texture, p, r, s, a, cameraP, front, rotating_angle,blur);
}
