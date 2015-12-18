// Game class

#include "include/cGame.hpp"

cGame::cGame() {
	setState(STATE_LOADING);
}

cGame::~cGame() {
}

void cGame::update(float dt) {
	data.timer = dt;

	if (state == STATE_LOADING || state == STATE_WIN) {
		// nothing
	} else if (state == STATE_MENU || state == STATE_NEXT_LEVEL || state == STATE_DEATH) {
		menu.update();
	} else if (state == STATE_SWAP) {
		hud.update(dt);
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

			int item = scene.itemCollected();
			if (item != 0) {
				std::cout << "item collected!\n";
				data.playSound(SOUND_COIN);
				if (item == 1) hud.increaseCoins();
				else {
					clck = true;
					clck_delay = scene.rot;
					scene.setReduction(CD_REDUCTION_CLOCK);
				}
			}

			if (scene.dead()) {
				std::cout << "DEAD!\n";
				setState(STATE_DEATH);
				return;
			} else if (scene.hit()) {
				std::cout << "DEAD!\n";
				setState(STATE_DEATH);
			} else if (scene.win()) {
				std::cout << "WIN!\n";
				if (current_level < MAX_LEVEL) setState(STATE_NEXT_LEVEL);
				else setState(STATE_WIN);
				return;
			}

			data.cameraP = player.getPosition();
		}
	} else {
		hud.update(dt);

		glm::vec3 tmp;
		tmp = player.getPosition();
		player.update(dt);
		scene.updatePlayerPosition(player.getPosition());

		if (scene.illegalMov()) {
			player.setPosition(tmp);
		}
		
		int item = scene.itemCollected();
		if (item != 0) {
			std::cout << "item collected!\n";
			data.playSound(SOUND_COIN);
			if (item == 1) hud.increaseCoins();
			else {
				clck = true;
				clck_delay = scene.rot;
				scene.setReduction(CD_REDUCTION_CLOCK);
			}
		}

		if (scene.slowed()) {
			player.setPlayerStep(PLAYER_STEP_SLOWED);
			player.setAnimationDelay(ANIMATION_DELAY_SLOWED);
			data.playSound(SOUND_GRASS);
		} else {
			player.setPlayerStep(PLAYER_STEP_NORMAL);
			player.setAnimationDelay(ANIMATION_DELAY_NORMAL);
		}
 		
 		if (scene.swapTile()) {
			setState(STATE_SWAP);
			player.setPlayerStep(PLAYER_STEP_SWAP);
			player.setAnimationDelay(ANIMATION_DELAY_SWAP);
		}

		if (scene.dead()) {
			std::cout << "DEAD!\n";
			setState(STATE_DEATH);
			return;
		} else if (scene.hit()) {
			std::cout << "DEAD!\n";
			setState(STATE_DEATH);
		} else if (scene.win()) {
			std::cout << "WIN!\n";
			if (current_level < MAX_LEVEL) setState(STATE_NEXT_LEVEL);
			else setState(STATE_WIN);
			return;
		}

		if (scene.rot >= PI + PI/2 && current_level == MAX_LEVEL && state == STATE_RUNNING) data.playSound(SOUND_LAUGH);

		data.cameraP = player.getPosition();
	
		scene.update(dt);
	}

	if (clck) {
		player.setPlayerStep(PLAYER_STEP_CLOCK);
		player.setAnimationDelay(ANIMATION_DELAY_CLOCK);

		if (scene.rot - clck_delay > PI || scene.rot - clck_delay < -PI) {
			clck = false;
			clck_delay = 0;
			scene.setReduction(CD_REDUCTION_NORMAL);
			player.setPlayerStep(PLAYER_STEP_NORMAL);
			player.setAnimationDelay(ANIMATION_DELAY_NORMAL);
		}
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
			hud.render();
			menu.render();
			break;
		case STATE_NEXT_LEVEL:
			scene.render();
			player.render();
			hud.render();
			menu.render();
			break;
		case STATE_WIN:
			// credits
			menu.render();
			break;
		case STATE_SWAP:
			scene.render();
			player.render();
			hud.render();
			break;
		case STATE_RUNNING:
			// Draw scene
			scene.render();

			// Draw model
			player.render();

			// Draw hud
			hud.render();	
		default:
			break;
	}
}


void cGame::keyPressed(char c) {
	glm::vec3 tmp;
	int item;

	switch (state) {
		case STATE_MENU:
			switch (c) {
				case '0':
					initializeLevel(0);
					break;
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

					item = scene.itemCollected();
					if (item != 0) {
						std::cout << "item collected!\n";
						data.playSound(SOUND_COIN);
						if (item == 1) hud.increaseCoins();
						else {
							clck = true;
							clck_delay = scene.rot;
							scene.setReduction(CD_REDUCTION_CLOCK);
							player.setPlayerStep(PLAYER_STEP_CLOCK);
							player.setAnimationDelay(ANIMATION_DELAY_CLOCK);
						}
					}

					if (scene.slowed()) {
						player.setPlayerStep(PLAYER_STEP_SLOWED);
						player.setAnimationDelay(ANIMATION_DELAY_SLOWED);
						data.playSound(SOUND_GRASS);
					} else {
						player.setPlayerStep(PLAYER_STEP_NORMAL);
						player.setAnimationDelay(ANIMATION_DELAY_NORMAL);
					}
			 		
			 		if (scene.swapTile()) {
						setState(STATE_SWAP);
						player.setPlayerStep(PLAYER_STEP_SWAP);
						player.setAnimationDelay(ANIMATION_DELAY_SWAP);
					}

					if (scene.dead()) {
						std::cout << "DEAD!\n";
						setState(STATE_DEATH);
						return;
					} else if (scene.hit()) {
						std::cout << "DEAD!\n";
						setState(STATE_DEATH);
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

					item = scene.itemCollected();
					if (item != 0) {
						std::cout << "item collected!\n";
						data.playSound(SOUND_COIN);
						if (item == 1) hud.increaseCoins();
						else {
							clck = true;
							clck_delay = scene.rot;
							scene.setReduction(CD_REDUCTION_CLOCK);
							player.setPlayerStep(PLAYER_STEP_CLOCK);
							player.setAnimationDelay(ANIMATION_DELAY_CLOCK);
						}
					}
					//	else if (scene.playerHit()) {
					//		TODO
					//	}
					
					if (scene.slowed()) {
						player.setPlayerStep(PLAYER_STEP_SLOWED);
						player.setAnimationDelay(ANIMATION_DELAY_SLOWED);
						data.playSound(SOUND_GRASS);
					} else {
						player.setPlayerStep(PLAYER_STEP_NORMAL);
						player.setAnimationDelay(ANIMATION_DELAY_NORMAL);
					}
			 		
			 		if (scene.swapTile()) {
						setState(STATE_SWAP);
						player.setPlayerStep(PLAYER_STEP_SWAP);
						player.setAnimationDelay(ANIMATION_DELAY_SWAP);
					}

					if (scene.dead()) {
						std::cout << "DEAD!\n";
						setState(STATE_DEATH);
						return;
					} else if (scene.hit()) {
						std::cout << "DEAD!\n";
						setState(STATE_DEATH);
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
	// Textures for game
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

	// Models for game
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
	data.loadModel(MODEL_PYR,MODEL_PYR_PATH);

	// Textures for menu
	menu.loadAssets();

	// Textures for hud
	hud.loadAssets();

	// Sounds
	data.loadSound(SOUND_COIN,SOUND_COIN_PATH);
	data.loadSound(SOUND_YAY,SOUND_YAY_PATH);
	data.loadSound(SOUND_SWOOSH,SOUND_SWOOSH_PATH);
	data.loadSound(SOUND_GRASS,SOUND_GRASS_PATH);
	data.loadSound(SOUND_RUN,SOUND_RUN_PATH);
	data.loadSound(SOUND_RUN_OK,SOUND_RUN_OK_PATH);
	data.loadSound(SOUND_LAUGH,SOUND_LAUGH_PATH);

	// Music
	data.loadMusic(MUSIC_MENU,MUSIC_MENU_PATH);	
	data.loadMusic(MUSIC_DEATH,MUSIC_DEATH_PATH);
	data.loadMusic(MUSIC_NEXT,MUSIC_NEXT_PATH);	
	data.loadMusic(MUSIC_WIN,MUSIC_WIN_PATH);
	data.loadMusic(MUSIC_LEVEL0,MUSIC_LEVEL0_PATH);
	data.loadMusic(MUSIC_LEVEL1,MUSIC_LEVEL1_PATH);
	data.loadMusic(MUSIC_LEVEL2,MUSIC_LEVEL2_PATH);
	data.loadMusic(MUSIC_LEVEL3,MUSIC_LEVEL3_PATH);

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
	scene.loadLevelObjects(level);
	scene.setPlayerPosition(glm::vec3(32.0,0.5,-2.0));
	scene.setReduction(CD_REDUCTION_NORMAL);
	data.front = 1;
	data.rotating_angle = PI/4;
	data.cameraP = player.getPosition();
	data.blur = false;
	setState(STATE_RUNNING);
	clck = false;
	clck_delay = 0;
	hud.setTimerOrigin(data.timer);
	hud.setCoins(0);
}

void cGame::retryLevel() {
	player = cPlayer(glm::vec3(32.0,0.5,-2.0), glm::vec3(0,1,0), glm::vec3(1), PI, &data);
	player.setActualModel(MODEL_CHAR1);
	player.setPlayerStep(PLAYER_STEP_NORMAL);
	player.setAnimationDelay(ANIMATION_DELAY_NORMAL);
	player.setDelay(0);
	scene.loadLevelCooldowns(current_level);
	scene.loadLevelObjects(current_level);
	scene.setPlayerPosition(glm::vec3(32.0,0.5,-2.0));
	scene.setReduction(CD_REDUCTION_NORMAL);
	data.front = 1;
	data.rotating_angle = PI/4;
	data.cameraP = player.getPosition();
	data.blur = false;
	setState(STATE_RUNNING);
	clck = false;
	clck_delay = 0;
	hud.setTimerOrigin(data.timer);
	hud.setCoins(0);
}

int cGame::getState() {
	return state;
}

void cGame::setState(int st) {
	switch (state) {
		case STATE_MENU:
			data.stopMusic(MUSIC_MENU);
			break;
		case STATE_RUNNING:
			if (st != STATE_SWAP) {
				data.stopMusic(current_level);
				data.stopSound(SOUND_RUN);
				data.stopSound(SOUND_RUN_OK);
				data.stopSound(SOUND_LAUGH);
			}
			break;
		case STATE_DEATH:
			data.stopMusic(MUSIC_DEATH);
			data.blur = false;
			break;
		case STATE_NEXT_LEVEL:
			data.stopMusic(MUSIC_NEXT);
			data.blur = false;
			break;
		case STATE_WIN:
			data.stopMusic(MUSIC_WIN);
			break;
		default:
			break;
	}

	switch (st) {
		case STATE_MENU:
			data.playMusic(MUSIC_MENU);
			break;
		case STATE_RUNNING:
			if (state != STATE_SWAP) {
				data.playMusic(current_level);
				if (current_level == 0) data.playSound(SOUND_RUN);
				else data.playSound(SOUND_RUN_OK);
			}
			break;
		case STATE_DEATH:
			data.playMusic(MUSIC_DEATH);
			data.blur = true;
			break;
		case STATE_NEXT_LEVEL:
			data.playMusic(MUSIC_NEXT);
			data.blur = true;
			break;
		case STATE_WIN:
			data.playSound(SOUND_YAY);
			data.playMusic(MUSIC_WIN);
			break;
		case STATE_SWAP:
			data.playSound(SOUND_SWOOSH);
			break;
		default:
			break;
	}

	state = st;
	menu.setState(st);
}