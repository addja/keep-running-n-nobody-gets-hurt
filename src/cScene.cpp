// Scene class

#include "include/cScene.hpp"

cScene::cScene() {}
cScene::cScene(glm::vec3 p, glm::vec3 r, glm::vec3 s, float a, cData * d) : cEntity(p, r, s, a, d) {}

cScene::~cScene() {} 

void cScene::loadLevel(int id) {
	char filename[30];
	sprintf(filename, "assets/level%d.txt", id);

	FILE * file = fopen(filename, "r");
	std::cout << filename << std::endl;
	if( file == NULL ) {
		std::cout << "Impossible to open the level file!" << std::endl;
		return;
	}

	std::vector<int> v;
	int i = 0;
	char lineHeader[128];
	// read the first word of the line
	int res = fscanf(file, "%s", lineHeader);
	while(1) {	 
		if (res == EOF) {
			break; // EOF = End Of File. Quit the loop.
		} else if ( lineHeader == std::string("w") ) {
			fscanf(file, "%d\n", &map_width );
			v = std::vector<int>(map_width);
		} else if ( lineHeader == std::string("h") ) {
			fscanf(file, "%d\n", &map_height );
		} else if ( lineHeader == std::string("m") ) {
			int tile;
			while (i < map_width - 1) {
				fscanf(file, "%d, ", &tile );
				v[i] = tile;
				i++;
			}
			fscanf(file, "%d\n", &tile );
			v[i] = tile;
			map.push_back(v);
			i = 0;
		}
		res = fscanf(file, "%s", lineHeader);
	}

//	std::cout << std::endl;
//	for (int i = 0; i < (int)map.size(); i++) {
//		for (int j = 0; j < (int)map[i].size(); j++) {
//			std::cout << map[i][j] << " ";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;
}

void cScene::update(float dt) {
	// A dream: destroying the map
}

void cScene::render() {
	// Draw model
	if (data->front == 1) {
		for (int i = 0; i < (int)map.size(); i++) {
			int k = (int)map.size() - 1 - i;
			for (int j = 0; j <= i; j++) {
				drawTile(j, k);
				k++;
			}
		}

		for (int i = 1; i < (int)map.size(); i++) {
			int k = 0;
			for (int j = i; j < (int)map.size(); j++) {
				drawTile(j, k);
				k++;
			}
		}
	} else {
		for (int i = 0; i < (int)map.size(); i++) {
			int j = (int)map.size() - 1;
			for (int k = i; k >= 0; k--) {
				drawTile(j, k);
				j--;
			}
		}

		for (int i = 1; i < (int)map.size(); i++) {
			int k = (int)map.size() - 1;
			for (int j = (int)map.size() - 1 - i; j >= 0; j--) {
				drawTile(j, k);
				k--;
			}
		}
	}


	if (DEBUG_MODE) {
		drawHighlightTile((int)playerx,-(int)playerz);
		drawHighlightTile((int)playerx +1,-(int)playerz);
		drawHighlightTile((int)playerx,-(int)playerz +1);
		drawHighlightTile((int)playerx +1,-(int)playerz +1);
	}
}

void cScene::drawHighlightTile(int j, int k) {
	drawColumn(j, k, 0, data->getTextureID(TEX_STONE));
}

void cScene::drawTile(int j, int k) {
	switch (map[j][k]) {
		case 0: break; // Empty block
		case 1: // Soil
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			//data->drawModel(MODEL_GRASSIE, data->getTextureID(TEX_GRASS), position + glm::vec3(TILE_SIZE*j,0.5,-k*TILE_SIZE), rotation, scale * glm::vec3(1, 0.5, 1), angle);
			break;
		case 2: // Wall
			drawColumn(j, k, 4, data->getTextureID(TEX_COL));
			//drawLittleBlock(j, k, 7, glm::vec3(0.45), data->getTextureID(TEX_SOIL));
			break;
		case 3: // Wall 2
			drawColumn(j, k, 5, data->getTextureID(TEX_COL));
			//drawLittleBlock(j, k, 7, glm::vec3(0.45), data->getTextureID(TEX_SOIL));
			break;
			break;
		case 4: // Swap soil
			drawColumn(j, k, 0, data->getTextureID(TEX_STONE));
			break;
		case 5: // Low columns			
			drawColumn(j, k, 2, data->getTextureID(TEX_COL));
			break;
		case 6: // Wall with a window
			drawColumn(j, k, 4, data->getTextureID(TEX_STONE));
			drawLittleBlock(j, k, 8, glm::vec3(1), data->getTextureID(TEX_STONE));
			drawLittleBlock(j, k, 9, glm::vec3(0.1), data->getTextureID(TEX_SOIL));
			break;
		case 7: // New grass
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			if (data->front == 1) data->drawModel(MODEL_GRASSIE, data->getTextureID(TEX_GRASS), position + glm::vec3(TILE_SIZE*j,0,-k*TILE_SIZE), rotation, scale, angle);
			else data->drawModel(MODEL_GRASSIE, data->getTextureID(TEX_GRASS), position + glm::vec3(TILE_SIZE*j,0,-k*TILE_SIZE), rotation, scale, angle + PI);
			break;
		case 8: // High columns
			data->drawModel(MODEL_COL, data->getTextureID(TEX_COL), position + glm::vec3(TILE_SIZE*j,-0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 9: // Normal tree
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			if (data->front == 1) {
				data->drawModel(MODEL_TREE_BODY, data->getTextureID(TEX_TREE_BODY), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle);
				data->drawModel(MODEL_TREE_LEAVES, data->getTextureID(TEX_TREE_LEAVES), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle);
			} else {
				data->drawModel(MODEL_TREE_BODY, data->getTextureID(TEX_TREE_BODY), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle + PI);
				data->drawModel(MODEL_TREE_LEAVES, data->getTextureID(TEX_TREE_LEAVES), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle + PI);
			}
			break;
		case 10: // Autumn tree
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			if (data->front == 1) {
				data->drawModel(MODEL_AUTUMN_BODY, data->getTextureID(TEX_TREE_BODY), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle);
				data->drawModel(MODEL_AUTUMN_LEAVES, data->getTextureID(TEX_AUTUMN_LEAVES), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle);
			} else {
				data->drawModel(MODEL_AUTUMN_BODY, data->getTextureID(TEX_TREE_BODY), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle + PI);
				data->drawModel(MODEL_AUTUMN_LEAVES, data->getTextureID(TEX_AUTUMN_LEAVES), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle + PI);
			}
			break;
		case 11: // Stone 1
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STONE1, data->getTextureID(TEX_STONE1), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 12: // Stone 2
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STONE2, data->getTextureID(TEX_STONE2), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 13: // Stone 3
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STONE3, data->getTextureID(TEX_STONE3), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 14: // Stone 4
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STONE4, data->getTextureID(TEX_STONE4), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 15: // Stone 5
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STONE5, data->getTextureID(TEX_STONE5), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 16: // Stop sign
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STOP_SIGN, data->getTextureID(TEX_STOP_SIGN), position + glm::vec3(TILE_SIZE*j, 0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		default:
			break;
	}
}

void cScene::drawLittleBlock(int j, int k, int n, glm::vec3 s, GLuint texture) {
	data->drawModel(MODEL_CUBE, texture, position + glm::vec3(j*TILE_SIZE, -0.5 + n,-k*TILE_SIZE), rotation, scale * s, angle);
}

void cScene::drawColumn(int j, int k, int n, GLuint texture) {
	for (int i = 0; i <= n; i++){
		data->drawModel(MODEL_CUBE, texture, position + glm::vec3(TILE_SIZE*j,-0.5 + i,-k*TILE_SIZE), rotation, scale, angle);
	}
}

void cScene::updatePlayerPosition(glm::vec3 dp) {
	playerx = dp.x/TILE_SIZE;
	playerz = dp.z/TILE_SIZE;
}

void cScene::setPlayerPosition(glm::vec3 p) {
	playerx = p.x;
	playerz = p.z;
}

int cScene::getWidth() {
	return map_width;
}

int cScene::getHeight() {
	return map_height;
}

int cScene::getTile(glm::vec3 p) {
	//std::cout << floor(playerx) << " " << ceil(playerz) + 0.5f << std::endl; 
	return map[ceil(playerx + 0.1f)][ceil(playerz) + 0.5f];
}

bool cScene::illegalMov() {
	if (playerx < 0 || playerx >= map_height-1 || // -+1 because the player fits two tiles and it's center is on the middle 
					playerz > 0 || playerz <= -map_width+1) {
		return true;
	}
	if (correctStep(map[(int)playerx][-(int)playerz]) ||
		correctStep(map[(int)playerx +1][-(int)playerz]) ||
		correctStep(map[(int)playerx][-(int)playerz +1]) ||
		correctStep(map[(int)playerx +1][-(int)playerz +1])) {
		return true;
	}
	return false;
}

bool cScene::correctStep(int i) {
	return i == 5 || i == 2 || i == 3 || i == 8; // TODO: improve this
}

bool cScene::swapTile() {
	if (map[(int)playerx][-(int)playerz] == 4 ||
		map[(int)playerx +1][-(int)playerz] == 4 ||
		map[(int)playerx][-(int)playerz +1] == 4 ||
		map[(int)playerx +1][-(int)playerz +1] == 4) {
		return true;
	}
	return false;
}
