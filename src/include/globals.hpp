// C++ libraries
#include<iostream>
#include <fstream>
#include <string>

// openGL
#include <GL/glew.h>

// SFML libraries
#include <SFML/Graphics.hpp> 
#include <SFML/OpenGL.hpp>

// math library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// Global vars
#define WNDW_WIDTH		480
#define WNDW_HEIGHT		480

#define GAME_TITLE		"game"

#define N_TEXTURES		2
#define TEX_CUBE		0
#define TEX_CHAR		1
#define TEX_CUBE_PATH	"assets/cube.tga"
#define TEX_CHAR_PATH "assets/tex_char.jpg"

#define N_MODELS		1
#define MODEL_CHAR		0
#define MODEL_CHAR_PATH "assets/char.obj"
