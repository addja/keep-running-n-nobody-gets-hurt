// intermediate with complex media data

#include "include/cData.hpp"

cData::cData() {
	cameraP = glm::vec3(0,0,0);
	front = 1;
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

void cData::loadModel(int i, std::string filename) {
	models[i].loadModel(filename);
}

void cData::drawModel(int i, GLuint texture, glm::vec3 p, glm::vec3 r, glm::vec3 s, float a) {
	models[i].render(texture, p, r, s, a, cameraP, front);
}
