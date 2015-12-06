// Game class

#include "include/cGame.hpp"

cGame::cGame() {
	initOpenGL();
	initGame();
	// Scaled to 1, so we move it up 0.5 (half its bounding box) so it is above the y = 0, which is the soil
	player = cPlayer(glm::vec3(2.0,0.5,-2.0), glm::vec3(0,1,0), glm::vec3(1), PI, &data);
	scene = cScene(glm::vec3(0,0,0), glm::vec3(0,1,0), glm::vec3(1), 0, &data);
	scene.loadLevel(1);
	scene.setPlayerPosition(glm::vec3(1,0,0));
}

cGame::~cGame() {
}

void cGame::update(float dt) {
	// glm::vec3 tmp = player.getPosition();
	// player.update(dt);
	// scene.updatePlayerPosition(player.getPosition() - tmp);
	data.cameraP = player.getPosition();
	// scene.update();
}

void cGame::render() {

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw scene
	scene.render();

	// Draw model
	player.render();	
}

glm::vec3 tmp;

void cGame::keyPressed(char c) {
	switch (c) {
		case 'W':
			tmp = player.getPosition();
			player.moveForward();
			scene.updatePlayerPosition(player.getPosition() - tmp);
			if (scene.getTile(player.getPosition()) == 4) {
				std::cout << "SWAP TILE" << std::endl;				
			} else if (scene.getTile(player.getPosition()) == 3) {
				std::cout << "DOOR TILE -> PORTAL" << std::endl;	
			}
			break;
		case 'S':
			// DEPRECATED: NO MOVING DOWN FOR OUR BOY.
			break;
		case 'D':
			tmp = player.getPosition();
			player.lookRight();
			scene.updatePlayerPosition(player.getPosition() - tmp);
			if (scene.getTile(player.getPosition()) == 4) {
				std::cout << "SWAP TILE" << std::endl;
				data.front = 1;
			}
			break;
		case 'A':
			tmp = player.getPosition();
			player.lookLeft();
			scene.updatePlayerPosition(player.getPosition() - tmp);
			if (scene.getTile(player.getPosition()) == 4) {
				std::cout << "SWAP TILE" << std::endl;
				data.front = -1;
			}
			break;
	}
}

void cGame::initOpenGL() {

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}

	// Clear color screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//glEnable (GL_NORMALIZE);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.1f, 1.0f);	

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	printf("iniOpenGL done correctly\n");
}

void cGame::initGame() {
	//data = cData();
	data.loadTexture(TEX_SOIL,TEX_SOIL_PATH);
	data.loadTexture(TEX_STONE,TEX_STONE_PATH);
	data.loadTexture(TEX_GRASS,TEX_GRASS_PATH);
	data.loadTexture(TEX_CHAR,TEX_CHAR_PATH);
	data.loadModel(MODEL_CHAR,MODEL_CHAR_PATH);
	data.loadModel(MODEL_CUBE,MODEL_CUBE_PATH);
}