// C++ libraries
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>

// openGL
#include <GL/glew.h>

// SFML libraries
#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
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

#define GAME_TITLE		"KEEP RUNNING"

#define N_TEXTURES			18
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
#define TEX_COIN		 	15
#define TEX_CLOCK		 	16
#define TEX_METAL			17
#define TEX_SOIL_PATH			"assets/textures/soil.jpg"
#define TEX_STONE_PATH			"assets/textures/stone.jpg"
#define TEX_GRASS_PATH			"assets/textures/grass.png"
#define TEX_CHAR_PATH 			"assets/textures/tex_char.jpg"
#define TEX_COL_PATH 			"assets/textures/column.jpg"
#define TEX_GRASSIE_PATH	 	"assets/textures/grass.png"
#define TEX_TREE_BODY_PATH 		"assets/textures/tree_body.jpg"
#define TEX_TREE_LEAVES_PATH	"assets/textures/tree_leaf.png"
#define TEX_AUTUMN_LEAVES_PATH 	"assets/textures/autumn_leaf.png"
#define TEX_STONE1_PATH 		"assets/textures/stone1.jpg"
#define TEX_STONE2_PATH 		"assets/textures/stone2.jpg"
#define TEX_STONE3_PATH 		"assets/textures/stone3.jpg"
#define TEX_STONE4_PATH 		"assets/textures/stone4.jpg"
#define TEX_STONE5_PATH 		"assets/textures/stone5.jpg"
#define TEX_STOP_SIGN_PATH 		"assets/textures/StopSignFront.jpg"
#define TEX_COIN_PATH 			"assets/textures/coin-texture.jpg"
#define TEX_CLOCK_PATH 			"assets/textures/clock.jpg"
#define TEX_METAL_PATH			"assets/textures/metal.jpg"

#define TEX_LOADING_PATH		"assets/menus/logo.jpg"
#define TEX_TITLE_1_PATH		"assets/menus/title_1.jpg"
#define TEX_TITLE_2_PATH		"assets/menus/title_2.jpg"
#define TEX_TITLE_3_PATH		"assets/menus/title_3.jpg"
#define TEX_TITLE_4_PATH		"assets/menus/title_4.jpg"
#define TEX_TITLE_5_PATH		"assets/menus/title_5.jpg"
#define TEX_DEATH_1_PATH		"assets/menus/death_1.png"
#define TEX_DEATH_2_PATH		"assets/menus/death_2.png"
#define TEX_DEATH_3_PATH		"assets/menus/death_3.png"
#define TEX_DEATH_4_PATH		"assets/menus/death_4.png"
#define TEX_DEATH_5_PATH		"assets/menus/death_5.png"
#define TEX_NEXT_1_PATH			"assets/menus/next_1.png"
#define TEX_NEXT_2_PATH			"assets/menus/next_2.png"
#define TEX_NEXT_3_PATH			"assets/menus/next_3.png"
#define TEX_NEXT_4_PATH			"assets/menus/next_4.png"
#define TEX_NEXT_5_PATH			"assets/menus/next_5.png"
#define TEX_WHITE_BACK_PATH		"assets/menus/semi-white.png"
#define TEX_WIN_PATH			"assets/menus/you_win.png"
#define	TEX_TEXT_PATH			"assets/textures/font.png"

#define N_MODELS			28
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
#define MODEL_STOP_BODY		24
#define MODEL_STOP_SIGN		25
#define MODEL_COIN			26
#define MODEL_CLOCK			27
#define MODEL_CHAR1_PATH 			"assets/models/rex1.obj"
#define MODEL_CHAR2_PATH 			"assets/models/rex2.obj"
#define MODEL_CHAR3_PATH 			"assets/models/rex3.obj"
#define MODEL_CHAR4_PATH 			"assets/models/rex4.obj"
#define MODEL_CHAR5_PATH 			"assets/models/rex5.obj"
#define MODEL_CHAR6_PATH 			"assets/models/rex6.obj"
#define MODEL_CHAR7_PATH 			"assets/models/rex7.obj"
#define MODEL_CHAR8_PATH 			"assets/models/rex8.obj"
#define MODEL_CHAR9_PATH 			"assets/models/rex9.obj"
#define MODEL_CHAR10_PATH			"assets/models/rex10.obj"
#define MODEL_CHAR11_PATH 			"assets/models/rex11.obj"
#define MODEL_CHAR12_PATH 			"assets/models/rex12.obj"
#define MODEL_CUBE_PATH 			"assets/models/cube.obj"
#define MODEL_COL_PATH 				"assets/models/column.obj"
#define MODEL_GRASSIE_PATH			"assets/models/grassie.obj"
#define MODEL_TREE_BODY_PATH		"assets/models/Tree_body.obj"
#define MODEL_TREE_LEAVES_PATH		"assets/models/Tree_leaves.obj"
#define MODEL_AUTUMN_BODY_PATH		"assets/models/Autumn_body.obj"
#define MODEL_AUTUMN_LEAVES_PATH	"assets/models/Autumn_leaves.obj"
#define MODEL_STONE1_PATH 			"assets/models/stone1.obj"
#define MODEL_STONE2_PATH 			"assets/models/stone2.obj"
#define MODEL_STONE3_PATH 			"assets/models/stone3.obj"
#define MODEL_STONE4_PATH 			"assets/models/stone4.obj"
#define MODEL_STONE5_PATH 			"assets/models/stone5.obj"
#define MODEL_STOP_SIGN_PATH		"assets/models/Stop_sign.obj"
#define MODEL_STOP_BODY_PATH		"assets/models/Stop_body.obj"
#define MODEL_COIN_PATH				"assets/models/coin.obj"
#define MODEL_CLOCK_PATH			"assets/models/clock.obj"

// Sounds array size
#define NUM_SOUNDS			7

// Sounds identifiers
#define SOUND_COIN			0
#define SOUND_YAY 			1
#define SOUND_SWOOSH		2
#define SOUND_GRASS			3
#define SOUND_RUN			4
#define SOUND_RUN_OK		5
#define SOUND_LAUGH			6

// Sounds paths
#define SOUND_COIN_PATH		"assets/sounds/coin.ogg"
#define SOUND_YAY_PATH		"assets/sounds/yay.ogg"
#define SOUND_SWOOSH_PATH	"assets/sounds/swoosh.ogg"
#define SOUND_GRASS_PATH	"assets/sounds/grass.ogg"
#define SOUND_RUN_PATH		"assets/sounds/run.ogg"
#define SOUND_RUN_OK_PATH	"assets/sounds/run_ok.ogg"
#define SOUND_LAUGH_PATH	"assets/sounds/laugh.ogg"

// Musics array size
#define NUM_MUSICS			8

// Musics identifiers
#define MUSIC_LEVEL0		0
#define MUSIC_LEVEL1		1
#define MUSIC_LEVEL2		2
#define MUSIC_LEVEL3		3
#define MUSIC_DEATH			4
#define MUSIC_NEXT			5
#define MUSIC_WIN			6
#define MUSIC_MENU			7

// Musics path
#define MUSIC_MENU_PATH		"assets/music/conversion.ogg"
#define MUSIC_DEATH_PATH	"assets/music/sans.ogg"
#define MUSIC_NEXT_PATH		"assets/music/hey.ogg"
#define MUSIC_WIN_PATH		"assets/music/huha.ogg"
#define MUSIC_LEVEL0_PATH	"assets/music/tale.ogg"
#define MUSIC_LEVEL1_PATH	"assets/music/spear.ogg"
#define MUSIC_LEVEL2_PATH	"assets/music/glamour.ogg"
#define MUSIC_LEVEL3_PATH	"assets/music/core.ogg"

#define DEBUG_MODE		0	// 0 off | 1 on
#define TILE_SIZE		2
