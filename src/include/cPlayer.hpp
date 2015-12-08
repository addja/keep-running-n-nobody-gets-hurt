#pragma once

#include "globals.hpp"
#include "cEntity.hpp"

#define PLAYER_STEP 0.4f
#define ANIMATION_DELAY	8

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

	private:
		int actual_model;
		int delay;
};