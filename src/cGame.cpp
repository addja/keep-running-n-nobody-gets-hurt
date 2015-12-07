// Game class

#include "include/cGame.hpp"

cGame::cGame() {
	initOpenGL();
	initGame();
	// Scaled to 1, so we move it up 0.5 (half its bounding box) so it is above the y = 0, which is the soil
	player = cPlayer(glm::vec3(4.0,0.5,-4.0), glm::vec3(0,1,0), glm::vec3(1), PI, &data);
	player.setActualModel(MODEL_CHAR1);
	player.setDelay(0);
	scene = cScene(glm::vec3(0,0,0), glm::vec3(0,1,0), glm::vec3(1), 0, &data);
	scene.loadLevel(0);
	scene.setPlayerPosition(glm::vec3(2,1,0));
}

cGame::~cGame() {
}

void cGame::update(float dt) {
	glm::vec3 tmp, tmp2;
	tmp = player.getPosition();
	player.update(dt);
	scene.updatePlayerPosition(player.getPosition() - tmp);
	if (scene.getTile(player.getPosition()) == 4) {
		std::cout << "SWAP TILE" << std::endl;				
	} else if (scene.getTile(player.getPosition()) == 3) {
		std::cout << "DOOR TILE -> PORTAL" << std::endl;	
	} else if (scene.getTile(player.getPosition()) == 0 || scene.getTile(player.getPosition()) == 2 ||
				scene.getTile(player.getPosition()) == 5 || scene.getTile(player.getPosition()) == 6 ||
				player.getPosition().x/2 < 0 || player.getPosition().x/2 >= scene.getHeight() || 
				player.getPosition().z/2 > 0 || player.getPosition().z/2 <= -scene.getWidth()) {
		//tmp2 = player.getPosition();
		//player.setPosition(tmp);
		//scene.updatePlayerPosition(tmp - tmp2);
		//std::cout << "CANNOT MOVE, BRO  " << tmp2.x << " " << tmp.z << std::endl;
	}
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
glm::vec3 tmp2;

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
			} else if (scene.getTile(player.getPosition()) == 0 || scene.getTile(player.getPosition()) == 2 ||
						scene.getTile(player.getPosition()) == 5 || scene.getTile(player.getPosition()) == 6 ||
						player.getPosition().x/2 < 0 || player.getPosition().x/2 >= scene.getHeight() || 
						player.getPosition().z/2 > 0 || player.getPosition().z/2 <= -scene.getWidth()) {
				tmp2 = player.getPosition();
				player.setPosition(tmp);
				scene.updatePlayerPosition(tmp - tmp2);
				//std::cout << "CANNOT MOVE, BRO  " << tmp2.x << " " << tmp.z << std::endl;
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
	data.loadTexture(TEX_SOIL,TEX_SOIL_PATH);
	data.loadTexture(TEX_STONE,TEX_STONE_PATH);
	data.loadTexture(TEX_GRASS,TEX_GRASS_PATH);
	data.loadTexture(TEX_COL,TEX_COL_PATH);
	data.loadTexture(TEX_GRASSIE,TEX_GRASSIE_PATH);
	data.loadTexture(TEX_CHAR,TEX_CHAR_PATH);
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
}