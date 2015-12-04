// intermediate with complex media data

#include "include/cData.hpp"

cData::cData() {}

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

void cData::loadModel(int i, std::string filename, GLuint texture) {
	models[i].loadModel(filename, texture);
}

void cData::drawModel(int i) {
	models[i].render();
}
