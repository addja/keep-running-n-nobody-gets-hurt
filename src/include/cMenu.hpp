#pragma once

#include "globals.hpp"
#include "cGraphics.hpp"
#include "cTexture.hpp"

// States inherited from Game
#define MENU_STATE_LOADING		0
#define MENU_STATE_RUNNING		1
#define MENU_STATE_MENU	 		2
#define MENU_STATE_DEATH		3
#define	MENU_STATE_NEXT_LEVEL	4
#define	MENU_STATE_WIN			5
#define MENU_STATE_SWAP			6
#define MENU_STATE_QUIT			7

#define MENU_ANIMATION_LENGTH	5
#define MENU_ANIMATION_DELAY	5

class cMenu {

	public:
			cMenu();
			~cMenu();

			void update();
			void render();

			void loadAssets();

			int getState();
			void setState(int state);

			int getDelay();
			void setDelay(int delay);

	private:
			int state, delay;
			int title_index, death_index, next_index;
			int title_dir, death_dir, next_dir;

			GLuint full_window_vertexbuffer;
			GLuint semi_window_vertexbuffer;

			GLuint uvbuffer;
			GLuint programID;
			GLuint textureID;
			GLuint mvp_handle;

			GLuint loading_tex;
			GLuint title_tex[MENU_ANIMATION_LENGTH];
			GLuint death_tex[MENU_ANIMATION_LENGTH];
			GLuint next_tex[MENU_ANIMATION_LENGTH];
			GLuint back_tex;
			GLuint win_tex;

			void initGL();
};
