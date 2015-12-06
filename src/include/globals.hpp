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

#define N_MODELS		2
#define MODEL_CHAR		0
#define MODEL_CUBE 		1
#define MODEL_CHAR_PATH "assets/char.obj"
#define MODEL_CUBE_PATH "assets/cube.obj"
