#pragma once

#include "globals.hpp"
#include "cData.hpp"

class cEntity {

	public:
		cEntity();
		explicit cEntity(glm::vec3 p, glm::vec3 r, glm::vec3 s, float a, cData * d);
		~cEntity();

		virtual void update(float dt);
		virtual void render();

		glm::vec3 position, rotation, scale;
		cData * data;
		float angle;

};