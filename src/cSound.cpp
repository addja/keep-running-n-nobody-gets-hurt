#include "include/cSound.hpp"

cSound::cSound(void) {}

cSound::~cSound(void) {}

bool cSound::load(const std::string filename) {
	bool res = buffer.loadFromFile(filename);
	sound.setBuffer(buffer);

	return res;
}

void cSound::play() {
	if (sound.getStatus() != sf::SoundSource::Playing) sound.play();
}

void cSound::stop() {
	if (sound.getStatus() != sf::SoundSource::Stopped) sound.stop();
}

