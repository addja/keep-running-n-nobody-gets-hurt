#include "include/cMusic.hpp"

cMusic::cMusic(void) {}

cMusic::~cMusic(void) {}

bool cMusic::load(const std::string filename) {
	if (music.openFromFile(filename)) return true;
	return false;
}

void cMusic::play() {
	music.setLoop(true);
	music.play();
}

void cMusic::stop() {
	music.stop();
}
