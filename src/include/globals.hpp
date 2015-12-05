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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// Global vars
#define WNDW_WIDTH		1024
#define WNDW_HEIGHT		720

#define GAME_TITLE		"game"

#define N_TEXTURES		2
#define TEX_CUBE		0
#define TEX_CHAR		1
#define TEX_CUBE_PATH	"assets/cube_2.tga"
#define TEX_CHAR_PATH 	"assets/tex_char.jpg"

#define N_MODELS		2
#define MODEL_CHAR		0
#define MODEL_CUBE 		1
#define MODEL_CHAR_PATH "assets/char.obj"
#define MODEL_CUBE_PATH "assets/cube.obj"
