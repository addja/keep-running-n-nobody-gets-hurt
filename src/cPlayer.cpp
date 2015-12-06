// Player class

#include "include/cPlayer.hpp"

cPlayer::cPlayer() {}
cPlayer::cPlayer(glm::vec3 p, glm::vec3 r, glm::vec3 s, float a, cData * d) : cEntity(p, r, s, a, d) {}

cPlayer::~cPlayer() {} 

void cPlayer::update(float dt) {
	moveForward();
}

void cPlayer::render() {
	// Draw model
	data->drawModel(MODEL_CHAR,data->getTextureID(TEX_CHAR),position,rotation,scale,angle);
}

void cPlayer::moveForward() {
	position = glm::vec3(position.x + glm::sin(angle) * PLAYER_STEP, position.y, position.z + glm::cos(angle) * PLAYER_STEP);
}

void cPlayer::moveBackward() {

}

void cPlayer::lookRight() {
	if (angle - PI/2 < 0) angle = 2*PI;
	else angle -= PI/2;
	//std::cout << angle << std::endl;
	//position = glm::vec3(position.x + glm::sin(angle) * 1.5, position.y, position.z + glm::cos(angle) * 1.5);
}
void cPlayer::lookLeft() {
	if (angle + PI/2 > 2*PI) angle = 0;
	else angle += PI/2;
	//std::cout << angle << std::endl;
	//position = glm::vec3(position.x + glm::sin(angle) * 1, position.y, position.z + glm::cos(angle) * 1.5);
}

glm::vec3 cPlayer::getPosition() {
	return position;
}

void cPlayer::setPosition(glm::vec3 p) {
	position = p;
}