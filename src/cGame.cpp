// Game class

#include "include/cGame.hpp"

cGame::cGame() {
	initOpenGL();
	initGame();
	// Scaled to 1, so we move it up 0.5 (half its bounding box) so it is above the y = 0, which is the ground
	player = cPlayer(glm::vec3(2.0,0.5,-2.0), glm::vec3(0,1,0), glm::vec3(1), PI, &data);
	player.setActualModel(MODEL_CHAR1);
	player.setDelay(0);
	scene = cScene(glm::vec3(0,0,0), glm::vec3(0,1,0), glm::vec3(1), 0, &data);
	scene.loadLevel(1);
	scene.setPlayerPosition(glm::vec3(2,1,0));
}

cGame::~cGame() {
}

void cGame::update(float dt) {
	glm::vec3 tmp;
	tmp = player.getPosition();
	player.update(dt);
	scene.updatePlayerPosition(player.getPosition());

	if (scene.illegalMov()) {
		player.setPosition(tmp);
	}
//	else if (scene.itemCollected()) {
//		TODO
//	}
//	else if (scene.playerHit()) {
//		TODO
//	}
 	else if (scene.swapTile()) {
		if (data.front == 1) data.front = -1;
		else data.front = 1;

		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		player.moveForward();
		scene.updatePlayerPosition(player.getPosition());
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


void cGame::keyPressed(char c) {
	glm::vec3 tmp;
	switch (c) {
		case 'W':
			tmp = player.getPosition();
			player.moveForward();
			scene.updatePlayerPosition(player.getPosition());
			if (scene.illegalMov()) {
				player.setPosition(tmp);
			}
			//	else if (scene.itemCollected()) {
			//		TODO
			//	}
			//	else if (scene.playerHit()) {
			//		TODO
			//	}
			//  else if (scene.swapTile()) {
			//		TODO
			//	}
			break;
		case 'S':
			// DEPRECATED: NO MOVING DOWN FOR OUR BOY.
			break;
		case 'D':
			tmp = player.getPosition();
			player.lookRight();
			scene.updatePlayerPosition(player.getPosition());
			if (scene.illegalMov()) {
				player.setPosition(tmp);
			}
			//	else if (scene.itemCollected()) {
			//		TODO
			//	}
			//	else if (scene.playerHit()) {
			//		TODO
			//	}
			//  else if (scene.swapTile()) {
			//		TODO
			//	}
			break;
		case 'A':
			tmp = player.getPosition();
			player.lookLeft();
			scene.updatePlayerPosition(player.getPosition());
			if (scene.illegalMov()) {
				player.setPosition(tmp);
			}
			//	else if (scene.itemCollected()) {
			//		TODO
			//	}
			//	else if (scene.playerHit()) {
			//		TODO
			//	}
			//  else if (scene.swapTile()) {
			//		TODO
			//	}
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
	data.loadTexture(TEX_TREE_BODY,TEX_TREE_BODY_PATH);
	data.loadTexture(TEX_AUTUMN_LEAVES,TEX_AUTUMN_LEAVES_PATH);
	data.loadTexture(TEX_TREE_LEAVES,TEX_TREE_LEAVES_PATH);
	data.loadTexture(TEX_STONE1,TEX_STONE1_PATH);
	data.loadTexture(TEX_STONE2,TEX_STONE2_PATH);
	data.loadTexture(TEX_STONE3,TEX_STONE3_PATH);
	data.loadTexture(TEX_STONE4,TEX_STONE4_PATH);
	data.loadTexture(TEX_STONE5,TEX_STONE5_PATH);
	data.loadTexture(TEX_STOP_SIGN,TEX_STOP_SIGN_PATH);
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
}

