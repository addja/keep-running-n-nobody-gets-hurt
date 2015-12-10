#pragma once

#include "globals.hpp"
#include "cEntity.hpp"

#define OBJECT_ROTATION 0.1

class cScene : cEntity {

	public:
		cScene();
		cScene(glm::vec3 p, glm::vec3 r, glm::vec3 s, float a, cData * d);
		~cScene();

		void loadLevel(int id);
		void update(float dt);
		void render();

		void drawHighlightTile(int j, int k);
		void drawTile(int j, int k);
		void drawObject(int j, int k);
		void drawLittleBlock(int j, int k, int n, glm::vec3 s, GLuint texture);
		void drawColumn(int j, int k, int n, GLuint texture);

		void updatePlayerPosition(glm::vec3 dp);
		void setPlayerPosition(glm::vec3 position);

		int getWidth();
		int getHeight();
		int getTile(glm::vec3 position);

		bool illegalMov();
		int itemCollected();
		bool playerHit();
		bool correctStep(int i);
		bool swapTile();

	private:
		std::vector< std::vector<int> > map;
		std::vector< std::vector<int> > objmap;
		int map_width, map_height;
		float playerx, playerz;
		float rot;
};
