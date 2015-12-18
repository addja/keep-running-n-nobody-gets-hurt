#pragma once

#include "globals.hpp"

class cSound {
public:
	cSound(void);
	~cSound(void);

	bool load(const std::string filename);
	void play();
	void stop();

private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};
