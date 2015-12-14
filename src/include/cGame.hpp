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
		bool swap_tile;
		bool win;
		bool death;
		float limit;
		
		void initOpenGL();
		void initGame();
		void restartGame();
};
