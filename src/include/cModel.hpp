#pragma once

#include "globals.hpp"
#include "cGraphics.hpp"

class cModel {
	
	public:
		GLuint vertexbuffer_quads; 
		GLuint uvbuffer_quads; 
		GLuint vertexbuffer_triangles;
		GLuint uvbuffer_triangles;
		GLuint programID;	
		GLuint mvp_handle;	
		GLuint textureID;
		GLuint myTexture;

		std::vector < glm::vec3 > vertices_quads;
		std::vector < glm::vec2 > uvs_quads;
		std::vector < glm::vec3 > normals_quads;
		std::vector < glm::vec3 > vertices_triangles;
		std::vector < glm::vec2 > uvs_triangles;
		std::vector < glm::vec3 > normals_triangles;
		
		cModel();
		~cModel();
	
		void loadModel(std::string filename, GLuint texture);
		void initGL();
		void render();

	private:

};
