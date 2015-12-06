#pragma once

#include "globals.hpp"
#include "cData.hpp"
#include "cPlayer.hpp"
#include "cScene.hpp"

class cGame {
	
	public:
		cGame();
		~cGame();
	
		void keyPressed(char c);
		void update(float dt);
		void render();		

	private:
		cData data;
		cScene scene;
		cPlayer player;
		
		void initOpenGL();
		void initGame();
};
