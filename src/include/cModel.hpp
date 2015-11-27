#pragma once

#include "globals.hpp"

class cModel {
	
	public:
		std::vector < std::vector < glm::vec3 > > vertices;
		std::vector < std::vector < glm::vec2 > > uvs;
		std::vector < std::vector < glm::vec3 > > normals;
		
		cModel();
		~cModel();
	
		void loadModel(std::string filename);

	private:

};
