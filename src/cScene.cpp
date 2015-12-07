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
}

void cScene::drawTile(int j, int k) {
	switch (map[j][k]) {
		case 0: break; // Empty block
		case 1: // Soil
			drawColumn(j, k, 0, data->getTextureID(TEX_GRASS));
			break;
		case 2: // Wall
			drawColumn(j, k, 6, data->getTextureID(TEX_STONE));
			drawLittleBlock(j, k, 7, glm::vec3(0.45), data->getTextureID(TEX_SOIL));
			break;
		case 3: // Door
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			break;
		case 4: // Swap soil
			drawColumn(j, k, 0, data->getTextureID(TEX_SOIL));
			break;
		case 5: // Fire column
			drawColumn(j, k, 2, data->getTextureID(TEX_STONE));
			drawLittleBlock(j, k, 3, glm::vec3(0.45), data->getTextureID(TEX_SOIL));
			break;
		case 6: // Wall with a window
			drawColumn(j, k, 4, data->getTextureID(TEX_STONE));
			drawLittleBlock(j, k, 8, glm::vec3(1), data->getTextureID(TEX_STONE));
			drawLittleBlock(j, k, 9, glm::vec3(0.45), data->getTextureID(TEX_SOIL));
			break;
		default:
			break;
	}
}

void cScene::drawLittleBlock(int j, int k, int n, glm::vec3 s, GLuint texture) {
	data->drawModel(MODEL_CUBE, texture, position + glm::vec3(j*2 - data->front*(1 - s.x)/2,-0.5 + n,-k*2 - data->front*(1 - s.z)/2), rotation, scale * s, angle);
}

void cScene::drawColumn(int j, int k, int n, GLuint texture) {
	for (int i = 0; i <= n; i++){
		data->drawModel(MODEL_CUBE, texture, position + glm::vec3(j*2,-0.5 + i,-k*2), rotation, scale, angle);
	}
}

void cScene::updatePlayerPosition(glm::vec3 dp) {
	playerx += (floorf(dp.x * 100) / 100)/2;
	playerz -= (floorf(dp.z * 100) / 100)/2;
	if (playerx < 0) playerx = 0;
	else if (playerx > map_height - 1) playerx = map_height - 1;
	if (playerz < 0) playerz = 0;
	else if (playerz > map_width - 2) playerz = map_width - 2;
	//std::cout << playerx << " " << playerz << std::endl; 
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
