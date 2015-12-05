// Game class

#include "include/cGame.hpp"

cGame::cGame() {
	initOpenGL();
	initGame();
}

cGame::~cGame() {
}

void cGame::update(float dt) {

}

void cGame::render() {

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw model
	//data.drawModel(MODEL_CHAR);
	data.drawModel(MODEL_CUBE);
}

void cGame::initOpenGL() {

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}

	// Clear color screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);	

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	printf("iniOpenGL done correctly\n");
}

void cGame::initGame() {
	//data = cData();
	data.loadTexture(TEX_CUBE,TEX_CUBE_PATH);
	data.loadTexture(TEX_CHAR,TEX_CHAR_PATH);
	data.loadModel(MODEL_CHAR,MODEL_CHAR_PATH, data.getTextureID(TEX_CHAR));
	data.loadModel(MODEL_CUBE,MODEL_CUBE_PATH, data.getTextureID(TEX_CUBE));
}