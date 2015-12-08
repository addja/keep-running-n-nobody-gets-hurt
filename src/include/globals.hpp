// C++ libraries
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// openGL
#include <GL/glew.h>

// SFML libraries
#include <SFML/Graphics.hpp> 
#include <SFML/OpenGL.hpp>

// math library
#define GLM_FORCE_RADIANS 1
#define PI				  3.141592653589793238462643383279502884197169399375105820974944592307816406286f
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// Global vars
#define WNDW_WIDTH		1024
#define WNDW_HEIGHT		720

#define GAME_TITLE		"game"

#define TEX_TITLE_PATH			"assets/title.png"
#define N_TEXTURES			15
#define TEX_SOIL			0
#define TEX_STONE			1
#define TEX_GRASS			2
#define TEX_CHAR			3
#define TEX_COL				4
#define TEX_GRASSIE 		5
#define TEX_TREE_BODY 		6
#define TEX_TREE_LEAVES		7
#define TEX_AUTUMN_LEAVES 	8
#define TEX_STONE1		 	9
#define TEX_STONE2		 	10
#define TEX_STONE3		 	11
#define TEX_STONE4		 	12
#define TEX_STONE5		 	13
#define TEX_STOP_SIGN	 	14
#define TEX_SOIL_PATH			"assets/soil.jpg"
#define TEX_STONE_PATH			"assets/stone.jpg"
#define TEX_GRASS_PATH			"assets/grass.png"
#define TEX_CHAR_PATH 			"assets/tex_char.jpg"
#define TEX_COL_PATH 			"assets/column.jpg"
#define TEX_GRASSIE_PATH	 	"assets/grass.png"
#define TEX_TREE_BODY_PATH 		"assets/tree_body.jpg"
#define TEX_TREE_LEAVES_PATH	"assets/tree_leaf.png"
#define TEX_AUTUMN_LEAVES_PATH 	"assets/autumn_leaf.png"
#define TEX_STONE1_PATH 		"assets/stone1.jpg"
#define TEX_STONE2_PATH 		"assets/stone2.jpg"
#define TEX_STONE3_PATH 		"assets/stone3.jpg"
#define TEX_STONE4_PATH 		"assets/stone4.jpg"
#define TEX_STONE5_PATH 		"assets/stone5.jpg"
#define TEX_STOP_SIGN_PATH 		"assets/metal.jpg"

#define N_MODELS			25
#define MODEL_CHAR1			0
#define MODEL_CHAR2			1
#define MODEL_CHAR3			2
#define MODEL_CHAR4			3
#define MODEL_CHAR5			4
#define MODEL_CHAR6			5
#define MODEL_CHAR7			6
#define MODEL_CHAR8			7
#define MODEL_CHAR9			8
#define MODEL_CHAR10		9
#define MODEL_CHAR11		10
#define MODEL_CHAR12		11
#define MODEL_CUBE 			12
#define MODEL_COL 			13
#define MODEL_GRASSIE		14
#define MODEL_TREE_BODY		15
#define MODEL_TREE_LEAVES	16
#define MODEL_AUTUMN_BODY	17
#define MODEL_AUTUMN_LEAVES	18
#define MODEL_STONE1		19
#define MODEL_STONE2		20
#define MODEL_STONE3		21
#define MODEL_STONE4		22
#define MODEL_STONE5		23
#define MODEL_STOP_SIGN		24
#define MODEL_CHAR1_PATH 			"assets/rex1.obj"
#define MODEL_CHAR2_PATH 			"assets/rex2.obj"
#define MODEL_CHAR3_PATH 			"assets/rex3.obj"
#define MODEL_CHAR4_PATH 			"assets/rex4.obj"
#define MODEL_CHAR5_PATH 			"assets/rex5.obj"
#define MODEL_CHAR6_PATH 			"assets/rex6.obj"
#define MODEL_CHAR7_PATH 			"assets/rex7.obj"
#define MODEL_CHAR8_PATH 			"assets/rex8.obj"
#define MODEL_CHAR9_PATH 			"assets/rex9.obj"
#define MODEL_CHAR10_PATH			"assets/rex10.obj"
#define MODEL_CHAR11_PATH 			"assets/rex11.obj"
#define MODEL_CHAR12_PATH 			"assets/rex12.obj"
#define MODEL_CUBE_PATH 			"assets/cube.obj"
#define MODEL_COL_PATH 				"assets/column.obj"
#define MODEL_GRASSIE_PATH			"assets/grassie.obj"
#define MODEL_TREE_BODY_PATH		"assets/Tree_body.obj"
#define MODEL_TREE_LEAVES_PATH		"assets/Tree_leaves.obj"
#define MODEL_AUTUMN_BODY_PATH		"assets/Autumn_body.obj"
#define MODEL_AUTUMN_LEAVES_PATH	"assets/Autumn_leaves.obj"
#define MODEL_STONE1_PATH 			"assets/stone1.obj"
#define MODEL_STONE2_PATH 			"assets/stone2.obj"
#define MODEL_STONE3_PATH 			"assets/stone3.obj"
#define MODEL_STONE4_PATH 			"assets/stone4.obj"
#define MODEL_STONE5_PATH 			"assets/stone5.obj"
#define MODEL_STOP_SIGN_PATH		"assets/StopSign.obj"

#define DEBUG_MODE		0	// 0 off | 1 on
#define TILE_SIZE		2
