#pragma once

#include "globals.hpp"
#include "cData.hpp"
#include "cPlayer.hpp"
#include "cScene.hpp"
#include "cMenu.hpp"

#define STATE_LOADING		0
#define STATE_RUNNING		1
#define STATE_MENU	 		2
#define STATE_DEATH			3
#define	STATE_NEXT_LEVEL	4
#define	STATE_WIN			5
#define STATE_SWAP			6
#define STATE_QUIT			7

#define MAX_LEVEL			3

class cGame {
	
	public:
		cGame();
		~cGame();
	
		void keyPressed(char c);
		void update(float dt);
		void render();	

		void loadAssets();

		void initializeLevel(int level);
		void retryLevel();

		int getState();
		void setState(int state);

	private:
		cData data;
		cScene scene;
		cPlayer player;
		cMenu menu;
		int state;
		int current_level;
		int coins;
		bool clck;
};
