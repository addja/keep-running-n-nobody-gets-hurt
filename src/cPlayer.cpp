// Player class

#include "include/cPlayer.hpp"

cPlayer::cPlayer() {}
cPlayer::cPlayer(glm::vec3 p, glm::vec3 r, glm::vec3 s, float a, cData * d) : cEntity(p, r, s, a, d) {}

cPlayer::~cPlayer() {} 

void cPlayer::update(float dt) {
	moveForward();
	animation();
}

void cPlayer::render() {
	// Draw model
	data->drawModel(actual_model,data->getTextureID(TEX_CHAR),position,rotation,scale,angle);
}

void cPlayer::moveForward() {
	position = glm::vec3(position.x + glm::sin(angle) * actual_step, position.y, position.z + glm::cos(angle) * actual_step);
}

void cPlayer::moveBackward() {

}

void cPlayer::lookRight() {
	//if (angle - PI/2 < 0) angle = 2*PI;
	//else angle -= PI/2;
	angle -= PI/2;
	//std::cout << angle << std::endl;
	position = glm::vec3(position.x + glm::sin(angle) * actual_step, position.y, position.z + glm::cos(angle) * actual_step);
}
void cPlayer::lookLeft() {
	//if (angle + PI/2 > 2*PI) angle = 0;
	//else angle += PI/2;
	angle += PI/2;
	//std::cout << angle << std::endl;
	position = glm::vec3(position.x + glm::sin(angle) * actual_step, position.y, position.z + glm::cos(angle) * actual_step);
}

void cPlayer::animation() {
	if (delay < actual_animation_delay) {
		delay += 1;
	} else {
		++actual_model;
		if (actual_model > MODEL_CHAR12) actual_model = MODEL_CHAR1;
		delay = 0;
	}
}

glm::vec3 cPlayer::getPosition() {
	return position;
}

void cPlayer::setPosition(glm::vec3 p) {
	position = p;
}

int cPlayer::getActualModel() {
	return actual_model;
}

void cPlayer::setActualModel(int model) {
	actual_model = model;
}

int cPlayer::getDelay() {
	return delay;
}

void cPlayer::setDelay(int d) {
	delay = d;
}

float cPlayer::getPlayerStep() {
	return actual_step;
}

void cPlayer::setPlayerStep(float step) {
	actual_step = step;
}

int cPlayer::getAnimationDelay() {
	return actual_animation_delay;
}

void cPlayer::setAnimationDelay(int delay) {
	actual_animation_delay = delay;
}
