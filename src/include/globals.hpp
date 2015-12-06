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

#define N_TEXTURES		4
#define TEX_SOIL		0
#define TEX_STONE		1
#define TEX_GRASS		2
#define TEX_CHAR		3
#define TEX_SOIL_PATH	"assets/soil.jpg"
#define TEX_STONE_PATH	"assets/stone.jpg"
#define TEX_GRASS_PATH	"assets/grass.png"
#define TEX_CHAR_PATH 	"assets/tex_char.jpg"

#define N_MODELS		13
#define MODEL_CHAR1		0
#define MODEL_CHAR2		1
#define MODEL_CHAR3		2
#define MODEL_CHAR4		3
#define MODEL_CHAR5		4
#define MODEL_CHAR6		5
#define MODEL_CHAR7		6
#define MODEL_CHAR8		7
#define MODEL_CHAR9		8
#define MODEL_CHAR10	9
#define MODEL_CHAR11	10
#define MODEL_CHAR12	11
#define MODEL_CUBE 		12
#define MODEL_CHAR1_PATH "assets/rex1.obj"
#define MODEL_CHAR2_PATH "assets/rex2.obj"
#define MODEL_CHAR3_PATH "assets/rex3.obj"
#define MODEL_CHAR4_PATH "assets/rex4.obj"
#define MODEL_CHAR5_PATH "assets/rex5.obj"
#define MODEL_CHAR6_PATH "assets/rex6.obj"
#define MODEL_CHAR7_PATH "assets/rex7.obj"
#define MODEL_CHAR8_PATH "assets/rex8.obj"
#define MODEL_CHAR9_PATH "assets/rex9.obj"
#define MODEL_CHAR10_PATH "assets/rex10.obj"
#define MODEL_CHAR11_PATH "assets/rex11.obj"
#define MODEL_CHAR12_PATH "assets/rex12.obj"
#define MODEL_CUBE_PATH "assets/cube.obj"
