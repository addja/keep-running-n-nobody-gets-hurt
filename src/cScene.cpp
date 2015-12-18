// Scene class

#include "include/cScene.hpp"

cScene::cScene() {}
cScene::cScene(glm::vec3 p, glm::vec3 r, glm::vec3 s, float a, cData * d) : cEntity(p, r, s, a, d) {}

cScene::~cScene() {} 

void cScene::loadLevel(int id) {
	char filename[30];
	// Level
	sprintf(filename, "assets/levels/level%d.txt", id);

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
		int matches;	 
		if (res == EOF) {
			break; // EOF = End Of File. Quit the loop.
		} else if ( lineHeader == std::string("w") ) {
			matches = fscanf(file, "%d\n", &map_width );
			if (matches != 1) std::cout << "Problem reading" << std::endl;
			v = std::vector<int>(map_width);
		} else if ( lineHeader == std::string("h") ) {
			matches = fscanf(file, "%d\n", &map_height );
			if (matches != 1) std::cout << "Problem reading" << std::endl;
			map = std::vector< std::vector<int> >();
		} else if ( lineHeader == std::string("m") ) {
			int tile;
			while (i < map_width - 1) {
				matches = fscanf(file, "%d, ", &tile );
				if (matches != 1) std::cout << "Problem reading" << std::endl;
				v[i] = tile;
				i++;
			}
			matches = fscanf(file, "%d\n", &tile );
			if (matches != 1) std::cout << "Problem reading" << std::endl;
			v[i] = tile;
			map.push_back(v);
			i = 0;
		}
		res = fscanf(file, "%s", lineHeader);
	}
}

void cScene::loadLevelCooldowns(int id) {
	char filename[30];
	// Level cooldowns
	sprintf(filename, "assets/levels/level%dcds.txt", id);

	FILE * file = fopen(filename, "r");
	std::cout << filename << std::endl;
	if( file == NULL ) {
		std::cout << "Impossible to open the level file!" << std::endl;
		return;
	}

	std::vector<float> v2;
	int i = 0;
	// read the first word of the line
	char lineHeader[128];
	int res = fscanf(file, "%s", lineHeader);
	while(1) {
		int matches;	 
		if (res == EOF) {
			break; // EOF = End Of File. Quit the loop.
		} else if ( lineHeader == std::string("w") ) {
			matches = fscanf(file, "%d\n", &map_width );
			if (matches != 1) std::cout << "Problem reading" << std::endl;
			v2 = std::vector<float>(map_width);
		} else if ( lineHeader == std::string("h") ) {
			matches = fscanf(file, "%d\n", &map_height );
			if (matches != 1) std::cout << "Problem reading" << std::endl;
			map_cds = std::vector< std::vector<float> >();
		} else if ( lineHeader == std::string("m") ) {
			float tile;
			while (i < map_width - 1) {
				matches = fscanf(file, "%f, ", &tile );
				if (matches != 1) std::cout << "Problem reading: " << i << std::endl;
				v2[i] = tile;
				i++;
			}
			matches = fscanf(file, "%f\n", &tile );
			if (matches != 1) std::cout << "Problem reading" << std::endl;
			v2[i] = tile;
			map_cds.push_back(v2);
			i = 0;
		}
		res = fscanf(file, "%s", lineHeader);
	}

	rot = 0;
}

void cScene::loadLevelObjects(int id) {
	char filename[30];
	// Level cooldowns
	sprintf(filename, "assets/levels/level%dobjs.txt", id);

	FILE * file = fopen(filename, "r");
	std::cout << filename << std::endl;
	if( file == NULL ) {
		std::cout << "Impossible to open the level file!" << std::endl;
		return;
	}

	std::vector<int> v2;
	int i = 0;
	// read the first word of the line
	char lineHeader[128];
	int res = fscanf(file, "%s", lineHeader);
	while(1) {
		int matches;	 
		if (res == EOF) {
			break; // EOF = End Of File. Quit the loop.
		} else if ( lineHeader == std::string("w") ) {
			matches = fscanf(file, "%d\n", &map_width );
			if (matches != 1) std::cout << "Problem reading" << std::endl;
			v2 = std::vector<int>(map_width);
		} else if ( lineHeader == std::string("h") ) {
			matches = fscanf(file, "%d\n", &map_height );
			if (matches != 1) std::cout << "Problem reading" << std::endl;
			objmap = std::vector< std::vector<int> >();
		} else if ( lineHeader == std::string("m") ) {
			int tile;
			while (i < map_width - 1) {
				matches = fscanf(file, "%d, ", &tile );
				if (matches != 1) std::cout << "Problem reading: " << i << std::endl;
				v2[i] = tile;
				i++;
			}
			matches = fscanf(file, "%d\n", &tile );
			if (matches != 1) std::cout << "Problem reading" << std::endl;
			v2[i] = tile;
			objmap.push_back(v2);
			i = 0;
		}
		res = fscanf(file, "%s", lineHeader);
	}
}

void cScene::update(float dt) {
	rot += dt*OBJECT_ROTATION;
  	if (rot > 2*PI) rot -= 2*PI;
	// A dream: destroying the map
	for (int i = 0; i < (int)map_cds.size(); i++) {
		for (int j = 0; j < (int)map_cds[0].size(); j++) {
			map_cds[i][j] -= actual_reduction;
		}
	}
}

void cScene::render() {
	// Draw model
	if (data->front == 1) {
		for (int i = 0; i < (int)map.size(); i++) {
			int k = (int)map.size() - 1 - i;
			for (int j = 0; j <= i; j++) {
				drawTile(j, k);
				if (objmap[j][k] != 0) drawObject(j, k);
				k++;
			}
		}

		for (int i = 1; i < (int)map.size(); i++) {
			int k = 0;
			for (int j = i; j < (int)map.size(); j++) {
				drawTile(j, k);
				if (objmap[j][k] != 0) drawObject(j, k);
				k++;
			}
		}
	} else {
		for (int i = 0; i < (int)map.size(); i++) {
			int j = (int)map.size() - 1;
			for (int k = i; k >= 0; k--) {
				drawTile(j, k);
				if (objmap[j][k] != 0) drawObject(j, k);
				j--;
			}
		}

		for (int i = 1; i < (int)map.size(); i++) {
			int k = (int)map.size() - 1;
			for (int j = (int)map.size() - 1 - i; j >= 0; j--) {
				drawTile(j, k);
				if (objmap[j][k] != 0) drawObject(j, k);
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
	float new_y = 0;
	if (map_cds[j][k] < 0) new_y = map_cds[j][k];
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
			drawColumn(j, k, 1, data->getTextureID(TEX_STONE3));
			//drawLittleBlock(j, k, 7, glm::vec3(0.45), data->getTextureID(TEX_SOIL));
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
			if (data->front == 1) data->drawModel(MODEL_GRASSIE, data->getTextureID(TEX_GRASS), position + glm::vec3(TILE_SIZE*j,new_y,-k*TILE_SIZE), rotation, scale, angle);
			else data->drawModel(MODEL_GRASSIE, data->getTextureID(TEX_GRASS), position + glm::vec3(TILE_SIZE*j,new_y,-k*TILE_SIZE), rotation, scale, angle + PI);
			break;
		case 8: // High columns
			data->drawModel(MODEL_COL, data->getTextureID(TEX_COL), position + glm::vec3(TILE_SIZE*j,new_y-0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 9: // Normal tree
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			if (data->front == 1) {
				data->drawModel(MODEL_TREE_BODY, data->getTextureID(TEX_TREE_BODY), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
				data->drawModel(MODEL_TREE_LEAVES, data->getTextureID(TEX_TREE_LEAVES), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
			} else {
				data->drawModel(MODEL_TREE_BODY, data->getTextureID(TEX_TREE_BODY), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle + PI);
				data->drawModel(MODEL_TREE_LEAVES, data->getTextureID(TEX_TREE_LEAVES), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle + PI);
			}
			break;
		case 10: // Autumn tree
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			if (data->front == 1) {
				data->drawModel(MODEL_AUTUMN_BODY, data->getTextureID(TEX_TREE_BODY), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
				data->drawModel(MODEL_AUTUMN_LEAVES, data->getTextureID(TEX_AUTUMN_LEAVES), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
			} else {
				data->drawModel(MODEL_AUTUMN_BODY, data->getTextureID(TEX_TREE_BODY), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle + PI);
				data->drawModel(MODEL_AUTUMN_LEAVES, data->getTextureID(TEX_AUTUMN_LEAVES), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle + PI);
			}
			break;
		case 11: // Stone 1
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STONE1, data->getTextureID(TEX_STONE1), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 12: // Stone 2
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STONE2, data->getTextureID(TEX_STONE2), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 13: // Stone 3
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STONE3, data->getTextureID(TEX_STONE3), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 14: // Stone 4
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STONE4, data->getTextureID(TEX_STONE4), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 15: // Stone 5
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STONE5, data->getTextureID(TEX_STONE5), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 16: // Stop sign
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			data->drawModel(MODEL_STOP_SIGN, data->getTextureID(TEX_STOP_SIGN), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
			data->drawModel(MODEL_STOP_BODY, data->getTextureID(TEX_METAL), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
			break;
		case 17: // Stone
			drawColumn(j, k, 0, data->getTextureID(TEX_STONE));
			break;
		case 18: // Level win soil
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			break;
		case 19: // Metal
			drawColumn(j, k, 0, data->getTextureID(TEX_METAL));
			break;
		case 20: // Brick
			drawColumn(j, k, 0, data->getTextureID(TEX_COL));
			break;
		case 21: // Evil stick
			if (map_cds[j][k] > 0) {
				if ((rot > PI/2 && rot < PI) || (rot > PI + PI/2 && rot < 2*PI)) {
					drawColumn(j, k, 0, data->getTextureID(TEX_METAL));
					data->drawModel(MODEL_PYR, data->getTextureID(TEX_METAL), position + glm::vec3(TILE_SIZE*j, new_y+1.5,-k*TILE_SIZE), rotation, scale, angle);
				}
				data->drawModel(MODEL_PYR, data->getTextureID(TEX_METAL), position + glm::vec3(TILE_SIZE*j, new_y+0.5,-k*TILE_SIZE), rotation, scale, angle);
			}
			break;
		case 22: // Swap soil
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			break;
		case 23: // Wall
			drawColumn(j, k, 3, data->getTextureID(TEX_COL));
			break;
		default:
			break;
	}
}

void cScene::drawLittleBlock(int j, int k, int n, glm::vec3 s, GLuint texture) {
	float new_y = 0;
	if (map_cds[j][k] < 0) new_y = map_cds[j][k];
	data->drawModel(MODEL_CUBE, texture, position + glm::vec3(j*TILE_SIZE, new_y - 0.5 + n,-k*TILE_SIZE), rotation, scale * s, angle);
}

void cScene::drawColumn(int j, int k, int n, GLuint texture) {
	float new_y = 0;
	if (map_cds[j][k] < 0) new_y = map_cds[j][k];
	for (int i = 0; i <= n; i++){
		data->drawModel(MODEL_CUBE, texture, position + glm::vec3(TILE_SIZE*j, new_y - 0.5 + i,-k*TILE_SIZE), rotation, scale, angle);
	}
}

void cScene::updatePlayerPosition(glm::vec3 dp) {
	playerx = dp.x/TILE_SIZE;
	playerz = dp.z/TILE_SIZE;
}

void cScene::setPlayerPosition(glm::vec3 p) {
	playerx = p.x/TILE_SIZE;
	playerz = p.z/TILE_SIZE;
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
	return i == 5 || i == 2 || i == 3 || i == 8 || i == 0 || i == 6 || i == 8 || 
		   i == 9 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 15 ||
		   i == 16; // TODO: improve this
}

bool cScene::swapTile() {
	if (map[(int)playerx][-(int)playerz] == 4 ||
		map[(int)playerx +1][-(int)playerz] == 4 ||
		map[(int)playerx][-(int)playerz +1] == 4 ||
		map[(int)playerx +1][-(int)playerz +1] == 4) {
		return true;
	} else if (map[(int)playerx][-(int)playerz] == 22 ||
		map[(int)playerx +1][-(int)playerz] == 22 ||
		map[(int)playerx][-(int)playerz +1] == 22 ||
		map[(int)playerx +1][-(int)playerz +1] == 22) {
		return true;
	}
	return false;
}

int cScene::itemCollected() {
	int x = objmap[(int)playerx][-(int)playerz];
	if (x != 0) {
		objmap[(int)playerx][-(int)playerz] = 0;	
		return x;
	}
	x = objmap[(int)playerx +1][-(int)playerz];
	if (x != 0) {
			objmap[(int)playerx +1][-(int)playerz] = 0;
			return x;
	}
	x = objmap[(int)playerx][-(int)playerz +1];
	if (x != 0) {
			objmap[(int)playerx][-(int)playerz +1] = 0;
			return x;
	}
	x = objmap[(int)playerx +1][-(int)playerz +1];
	if (x != 0) {
			objmap[(int)playerx +1][-(int)playerz +1] = 0;
			return x;
	}
	return 0;
}

bool cScene::dead() {
	if (map_cds[(int)playerx][-(int)playerz] < 0 ||
		map_cds[(int)playerx +1][-(int)playerz] < 0 ||
		map_cds[(int)playerx][-(int)playerz +1] < 0 ||
		map_cds[(int)playerx +1][-(int)playerz +1] < 0) {
		return true;
	}
	return false;
}

bool cScene::win() {
	if ((map[(int)playerx][-(int)playerz] == 18) ||
		(map[(int)playerx +1][-(int)playerz] == 18) ||
		(map[(int)playerx][-(int)playerz +1] == 18) ||
		(map[(int)playerx +1][-(int)playerz +1] == 18)) {
		return true;
	}
	return false;
}

bool cScene::slowed() {
	if ((map[(int)playerx][-(int)playerz] == 7) ||
		(map[(int)playerx +1][-(int)playerz] == 7) ||
		(map[(int)playerx][-(int)playerz +1] == 7) ||
		(map[(int)playerx +1][-(int)playerz +1] == 7)) {
		return true;
	}
	return false;
}

bool cScene::hit() {
	if ((rot > PI/2 && rot < PI) || (rot > PI + PI/2 && rot < 2*PI)) {
		if ((map[(int)playerx][-(int)playerz] == 21) ||
			(map[(int)playerx +1][-(int)playerz] == 21) ||
			(map[(int)playerx][-(int)playerz +1] == 21) ||
			(map[(int)playerx +1][-(int)playerz +1] == 21)) {
			return true;
		}
	}
	return false;
}

void cScene::drawObject(int j, int k) {
	float new_y = 0;
	if (map_cds[j][k] < 0) new_y = map_cds[j][k];
	switch (objmap[j][k]) {
		case 1: // coin
			data->drawModel(MODEL_COIN, data->getTextureID(TEX_COIN), position + glm::vec3(TILE_SIZE*j,new_y + 2.5,-k*TILE_SIZE), rotation, scale, angle+rot);
			break;
		case 2: // clock
			data->drawModel(MODEL_CLOCK, data->getTextureID(TEX_CLOCK), position + glm::vec3(TILE_SIZE*j,new_y + 2.5,-k*TILE_SIZE), rotation, scale, angle+rot);
			break;
		default:
			break;
	}
}

float cScene::getReduction() {
	return actual_reduction;
}

void cScene::setReduction(float r) {
	actual_reduction = r;
}
