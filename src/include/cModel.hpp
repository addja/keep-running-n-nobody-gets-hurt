#pragma once

#include "globals.hpp"
#include "cGraphics.hpp"

class cModel {
	
	public:
		GLuint vertexbuffer_quads; 
		GLuint uvbuffer_quads; 
		GLuint normalbuffer_quads;
		GLuint vertexbuffer_triangles;
		GLuint uvbuffer_triangles;
		GLuint normalbuffer_triangles;
		GLuint programID;
		GLuint programBlurID;	
		GLuint mvp_handle;
		GLuint ViewMatrix_handle;
		GLuint ModelMatrix_handle;
		GLuint LightID;	
		GLuint textureID;
		GLuint myTexture;

		float maxx, minx, maxy, miny, maxz, minz;

		std::vector < glm::vec3 > vertices_quads;
		std::vector < glm::vec2 > uvs_quads;
		std::vector < glm::vec3 > normals_quads;
		std::vector < glm::vec3 > vertices_triangles;
		std::vector < glm::vec2 > uvs_triangles;
		std::vector < glm::vec3 > normals_triangles;
		
		cModel();
		~cModel();
	
		void loadModel(std::string filename);
		void initGL();
		void render(GLuint texture, glm::vec3 p, glm::vec3 r, glm::vec3 s, float angle, glm::vec3 cameraP, int front, float rot, bool blur);

	private:
		void calcBBox();
		void renderBBox();
};
