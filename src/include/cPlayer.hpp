#pragma once

#include "globals.hpp"
#include "cEntity.hpp"

#define PLAYER_STEP 0.2f

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

		glm::vec3 getPosition();
		void setPosition(glm::vec3 position);
};