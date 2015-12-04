#pragma once

#include "globals.hpp"
#include "cData.hpp"

class cGame {
	
	public:
		cGame();
		~cGame();
	
		void update(float dt);
		void render();		

	private:
		cData data;

		void initOpenGL();
		void initGame();

};
