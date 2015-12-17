// Game class

#include "include/cGame.hpp"

cGame::cGame() {
	setState(STATE_LOADING);
}

cGame::~cGame() {
}

void cGame::update(float dt) {
	if (state == STATE_LOADING || state == STATE_WIN) {
		// nothing
	} else if (state == STATE_MENU || state == STATE_NEXT_LEVEL || state == STATE_DEATH) {
		menu.update();
	} else if (state == STATE_SWAP) {
		if (data.rotating_angle >= PI + PI/4) {
			if (data.front == 1) data.front = -1;
			else data.front = 1;

			scene.updatePlayerPosition(player.getPosition());
			player.setPlayerStep(PLAYER_STEP_NORMAL);
			player.setAnimationDelay(ANIMATION_DELAY_NORMAL);
			setState(STATE_RUNNING);
			data.rotating_angle = PI/4;
		} else {
			data.rotating_angle += 0.4;
			player.update(dt);
			scene.updatePlayerPosition(player.getPosition());

			if (scene.itemCollected()) {
				std::cout << "item collected!\n";
			}
	//		else if (scene.playerHit()) {
	//			TODO
	//		}

			if (scene.dead()) {
				std::cout << "DEAD!\n";
				setState(STATE_DEATH);
				return;
			} else if (scene.win()) {
				std::cout << "WIN!\n";
				if (current_level < MAX_LEVEL) setState(STATE_NEXT_LEVEL);
				else setState(STATE_WIN);
				return;
			}

			data.cameraP = player.getPosition();
		}
	} else {
		glm::vec3 tmp;
		tmp = player.getPosition();
		player.update(dt);
		scene.updatePlayerPosition(player.getPosition());

		if (scene.illegalMov()) {
			player.setPosition(tmp);
		}
		else if (scene.itemCollected()) {
			std::cout << "item collected!\n";
		}
//		else if (scene.playerHit()) {
//			TODO
//		}
 		else if (scene.swapTile()) {
			setState(STATE_SWAP);
			player.setPlayerStep(PLAYER_STEP_SWAP);
			player.setAnimationDelay(ANIMATION_DELAY_SWAP);
		}

		if (scene.dead()) {
			std::cout << "DEAD!\n";
			setState(STATE_DEATH);
			return;
		} else if (scene.win()) {
			std::cout << "WIN!\n";
			if (current_level < MAX_LEVEL) setState(STATE_NEXT_LEVEL);
			else setState(STATE_WIN);
			return;
		}

		data.cameraP = player.getPosition();
	
		scene.update(dt);
	}
}

void cGame::render() {

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (state) {
		case STATE_LOADING:
			menu.render();
			break;
		case STATE_MENU:
			menu.render();
			break;
		case STATE_DEATH:
			scene.render();
			player.render();
			menu.render();
			break;
		case STATE_NEXT_LEVEL:
			scene.render();
			player.render();
			menu.render();
			break;
		case STATE_WIN:
			// credits
			menu.render();
			break;
		case STATE_SWAP:
			scene.render();
			player.render();
			break;
		case STATE_RUNNING:
			// Draw scene
			scene.render();

			// Draw model
			player.render();	
		default:
			break;
	}
}


void cGame::keyPressed(char c) {
	glm::vec3 tmp;

	switch (state) {
		case STATE_MENU:
			switch (c) {
				case '1':
					initializeLevel(1);
					break;
				case '2':
					initializeLevel(2);
					break;
				case '3':
					initializeLevel(3);
					break;
				case 'E':
					setState(STATE_QUIT);
					break;
				case 'S':
					initializeLevel(1);
					break;
				default:
					break;
			}
			break;
		case STATE_DEATH:
			switch (c) {
				case 'E':
					setState(STATE_MENU);
					break;
				case 'R':
					retryLevel();
					break;
				default:
					break;
			}
			break;
		case STATE_WIN:
			switch (c) {
				case 'E':
					setState(STATE_MENU);
					break;
				default:
					break;
			}
			break;
		case STATE_NEXT_LEVEL:
			switch (c) {
				case 'E':
					setState(STATE_MENU);
					break;
				case 'N':
					initializeLevel(current_level+1);
					break;
				case 'R':
					retryLevel();
					break;
				default:
					break;
			}
			break;
		case STATE_RUNNING:
			switch (c) {
				case 'D':
					tmp = player.getPosition();
					player.lookRight();
					scene.updatePlayerPosition(player.getPosition());
					if (scene.illegalMov()) {
						player.setPosition(tmp);
					}
					else if (scene.itemCollected()) {
						std::cout << "item collected!\n";
					}
					//	else if (scene.playerHit()) {
					//		TODO
					//	}
					else if (scene.swapTile()) {
						setState(STATE_SWAP);
						player.setPlayerStep(PLAYER_STEP_SWAP);
						player.setAnimationDelay(ANIMATION_DELAY_SWAP);
					}

					if (scene.dead()) {
						std::cout << "DEAD!\n";
						setState(STATE_DEATH);
						return;
					} else if (scene.win()) {
						std::cout << "WIN!\n";
						if (current_level < MAX_LEVEL) setState(STATE_NEXT_LEVEL);
						else setState(STATE_WIN);
						return;
					}
					break;
				case 'A':
					tmp = player.getPosition();
					player.lookLeft();
					scene.updatePlayerPosition(player.getPosition());
					if (scene.illegalMov()) {
						player.setPosition(tmp);
					}
					else if (scene.itemCollected()) {
						std::cout << "item collected!\n";
					}
					//	else if (scene.playerHit()) {
					//		TODO
					//	}
					else if (scene.swapTile()) {
						setState(STATE_SWAP);
						player.setPlayerStep(PLAYER_STEP_SWAP);
						player.setAnimationDelay(ANIMATION_DELAY_SWAP);
					}

					if (scene.dead()) {
						std::cout << "DEAD!\n";
						setState(STATE_DEATH);
						return;
					} else if (scene.win()) {
						std::cout << "WIN!\n";
						if (current_level < MAX_LEVEL) setState(STATE_NEXT_LEVEL);
						else setState(STATE_WIN);
						return;
					}
					break;
			}
			break;
		default:
			break;
	}
	
}

void cGame::loadAssets() {
	data.loadTexture(TEX_SOIL,TEX_SOIL_PATH);
	data.loadTexture(TEX_STONE,TEX_STONE_PATH);
	data.loadTexture(TEX_GRASS,TEX_GRASS_PATH);
	data.loadTexture(TEX_COL,TEX_COL_PATH);
	data.loadTexture(TEX_GRASSIE,TEX_GRASSIE_PATH);
	data.loadTexture(TEX_CHAR,TEX_CHAR_PATH);
	data.loadTexture(TEX_TREE_BODY,TEX_TREE_BODY_PATH);
	data.loadTexture(TEX_AUTUMN_LEAVES,TEX_AUTUMN_LEAVES_PATH);
	data.loadTexture(TEX_TREE_LEAVES,TEX_TREE_LEAVES_PATH);
	data.loadTexture(TEX_STONE1,TEX_STONE1_PATH);
	data.loadTexture(TEX_STONE2,TEX_STONE2_PATH);
	data.loadTexture(TEX_STONE3,TEX_STONE3_PATH);
	data.loadTexture(TEX_STONE4,TEX_STONE4_PATH);
	data.loadTexture(TEX_STONE5,TEX_STONE5_PATH);
	data.loadTexture(TEX_STOP_SIGN,TEX_STOP_SIGN_PATH);
	data.loadTexture(TEX_METAL,TEX_METAL_PATH);
	data.loadTexture(TEX_COIN,TEX_COIN_PATH);
	data.loadTexture(TEX_CLOCK,TEX_CLOCK_PATH);
	data.loadModel(MODEL_CHAR1,MODEL_CHAR1_PATH);
	data.loadModel(MODEL_CHAR2,MODEL_CHAR2_PATH);
	data.loadModel(MODEL_CHAR3,MODEL_CHAR3_PATH);
	data.loadModel(MODEL_CHAR4,MODEL_CHAR4_PATH);
	data.loadModel(MODEL_CHAR5,MODEL_CHAR5_PATH);
	data.loadModel(MODEL_CHAR6,MODEL_CHAR6_PATH);
	data.loadModel(MODEL_CHAR7,MODEL_CHAR7_PATH);
	data.loadModel(MODEL_CHAR8,MODEL_CHAR8_PATH);
	data.loadModel(MODEL_CHAR9,MODEL_CHAR9_PATH);
	data.loadModel(MODEL_CHAR10,MODEL_CHAR10_PATH);
	data.loadModel(MODEL_CHAR11,MODEL_CHAR11_PATH);
	data.loadModel(MODEL_CHAR12,MODEL_CHAR12_PATH);
	data.loadModel(MODEL_CUBE,MODEL_CUBE_PATH);
	data.loadModel(MODEL_COL,MODEL_COL_PATH);
	data.loadModel(MODEL_GRASSIE,MODEL_GRASSIE_PATH);
	data.loadModel(MODEL_AUTUMN_BODY,MODEL_AUTUMN_BODY_PATH);
	data.loadModel(MODEL_AUTUMN_LEAVES,MODEL_AUTUMN_LEAVES_PATH);
	data.loadModel(MODEL_TREE_BODY,MODEL_TREE_BODY_PATH);
	data.loadModel(MODEL_TREE_LEAVES,MODEL_TREE_LEAVES_PATH);
	data.loadModel(MODEL_STONE1,MODEL_STONE1_PATH);
	data.loadModel(MODEL_STONE2,MODEL_STONE2_PATH);
	data.loadModel(MODEL_STONE3,MODEL_STONE3_PATH);
	data.loadModel(MODEL_STONE4,MODEL_STONE4_PATH);
	data.loadModel(MODEL_STONE5,MODEL_STONE5_PATH);
	data.loadModel(MODEL_STOP_SIGN,MODEL_STOP_SIGN_PATH);
	data.loadModel(MODEL_STOP_BODY,MODEL_STOP_BODY_PATH);
	data.loadModel(MODEL_COIN,MODEL_COIN_PATH);
	data.loadModel(MODEL_CLOCK,MODEL_CLOCK_PATH);

	menu.loadAssets();

	setState(STATE_MENU);
}

void cGame::initializeLevel(int level) {
	// Scaled to 1, so we move it up 0.5 (half its bounding box) so it is above the y = 0, which is the ground
	current_level = level;
	player = cPlayer(glm::vec3(32.0,0.5,-2.0), glm::vec3(0,1,0), glm::vec3(1), PI, &data);
	player.setActualModel(MODEL_CHAR1);
	player.setPlayerStep(PLAYER_STEP_NORMAL);
	player.setAnimationDelay(ANIMATION_DELAY_NORMAL);
	player.setDelay(0);
	scene = cScene(glm::vec3(0,0,0), glm::vec3(0,1,0), glm::vec3(1), 0, &data);
	scene.loadLevel(level);
	scene.loadLevelCooldowns(level);
	scene.setPlayerPosition(glm::vec3(32.0,0.5,-2.0));
	data.front = 1;
	data.rotating_angle = PI/4;
	data.cameraP = player.getPosition();
	setState(STATE_RUNNING);
}

void cGame::retryLevel() {
	player = cPlayer(glm::vec3(32.0,0.5,-2.0), glm::vec3(0,1,0), glm::vec3(1), PI, &data);
	player.setActualModel(MODEL_CHAR1);
	player.setPlayerStep(PLAYER_STEP_NORMAL);
	player.setAnimationDelay(ANIMATION_DELAY_NORMAL);
	player.setDelay(0);
	scene.loadLevelCooldowns(current_level);
	scene.setPlayerPosition(glm::vec3(32.0,0.5,-2.0));
	data.front = 1;
	data.rotating_angle = PI/4;
	data.cameraP = player.getPosition();
	setState(STATE_RUNNING);
}

int cGame::getState() {
	return state;
}

void cGame::setState(int st) {
	state = st;
	menu.setState(st);
}