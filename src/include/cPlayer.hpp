#pragma once

#include "globals.hpp"
#include "cEntity.hpp"

#define PLAYER_STEP_NORMAL 		0.5f
#define PLAYER_STEP_SLOWED 		0.2f
#define PLAYER_STEP_SWAP   		0.45f
#define ANIMATION_DELAY_NORMAL	1
#define ANIMATION_DELAY_SLOWED  2
#define ANIMATION_DELAY_SWAP	3

class cPlayer : cEntity {

	public:
		cPlayer();
		cPlayer(glm::vec3 p, glm::vec3 r, glm::vec3 s, float a, cData * d);
		~cPlayer();

		void update(float dt);
		void render();

		void moveForward();
		void moveBackward();
		void lookRight();
		void lookLeft();

		void animation();

		glm::vec3 getPosition();
		void setPosition(glm::vec3 position);

		int getActualModel();
		void setActualModel(int model);

		int getDelay();
		void setDelay(int delay);

		float getPlayerStep();
		void setPlayerStep(float step);

		int getAnimationDelay();
		void setAnimationDelay(int delay);

	private:
		int actual_model;
		float actual_step;
		int actual_animation_delay;
		int delay;
};