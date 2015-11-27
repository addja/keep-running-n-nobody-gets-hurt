// intermediate with complex media data

#include "include/cData.hpp"

cData::cData() {}

cData::~cData() {}

void cData::loadTexture(int i, std::string filename) {
	texture[i] = loadTex(filename);
}

GLuint cData::getTextureID(int i) {
	return texture[i];
}

void cData::loadModel(int i, std::string filename) {
	models[i].loadModel(filename);
}


