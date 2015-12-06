// Entity abstrasct class

#include "include/cEntity.hpp"

cEntity::cEntity() {}

cEntity::cEntity(glm::vec3 p, glm::vec3 r, glm::vec3 s, float a, cData * d) {
	position = p;
	rotation = r;
	scale = s;
	angle = a;
	data = d;
}

cEntity::~cEntity() {} 

void cEntity::update(float dt) {}
void cEntity::render() {}