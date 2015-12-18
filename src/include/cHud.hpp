#pragma once

#include "globals.hpp"
#include "cGraphics.hpp"
#include "cTexture.hpp"

class cHud {

	public:
			cHud();
			~cHud();

			void update(float dt);
			void render();

			void loadAssets();
			void printText(int x, int y, int size, char * text);

			float getTimerOrigin();
			void setTimerOrigin(float t);

			int getCoins();
			void setCoins(int c);
			void increaseCoins();

	private:
			float timer_origin, timer;
			int coins;

			GLuint vertexbuffer;
			GLuint back_vertexbuffer;

			GLuint uvbuffer;
			GLuint back_uvbuffer;

			GLuint programID;
			GLuint programID_back;
			GLuint textureID;
			GLuint textureID2;
			GLuint mvp_handle;

			GLuint text_tex;
			GLuint back_tex;

			void initGL();
};
