#pragma once

#include "globals.hpp"
#include "cEntity.hpp"

#define OBJECT_ROTATION 0.9
#define CD_REDUCTION_NORMAL 0.22
#define CD_REDUCTION_CLOCK	0.05

class cScene : cEntity {

	public:
		float rot;

		cScene();
		cScene(glm::vec3 p, glm::vec3 r, glm::vec3 s, float a, cData * d);
		~cScene();

		void loadLevel(int id);
		void loadLevelCooldowns(int id);
		void loadLevelObjects(int id);
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
		bool dead();
		bool win();
		bool slowed();
		bool hit();

		float getReduction();
		void setReduction(float r);

	private:
		std::vector< std::vector<int> > map;
		std::vector< std::vector<float> > map_cds;
		std::vector< std::vector<int> > objmap;
		int map_width, map_height;
		float playerx, playerz;
		float actual_reduction;
};
