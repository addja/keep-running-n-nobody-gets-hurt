// Model class

#include "include/cModel.hpp"

cModel::cModel() {
}

cModel::~cModel() {}

void cModel::loadModel(std::string filename) {
	// std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	// std::vector< glm::vec3 > temp_vertices;
	// std::vector< glm::vec2 > temp_uvs;
	// std::vector< glm::vec3 > temp_normals;

	// FILE * file = fopen(filename.c_str(), "r");
	// if( file == NULL ) {
	// 	std::cout << "Impossible to open the file!" << std::endl;
	// 	return;
	// }
	// int i = 0;
	// char lineHeader[128];
	// // read the first word of the line
	// int res = fscanf(file, "%s", lineHeader);
	// while(1) {	 
	// 	if (res == EOF)
	// 		break; // EOF = End Of File. Quit the loop.
	// 	else {
	// 		while ( lineHeader == std::string("v") ) {
	// 			glm::vec3 vertex;
	// 			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
	// 			temp_vertices.push_back(vertex);
	// 			res = fscanf(file, "%s", lineHeader);
	// 			i++;
	// 		} while( lineHeader == std::string("vt") ) {
	// 			glm::vec2 uv;
	// 			fscanf(file, "%f %f\n", &uv.x, &uv.y );
	// 			temp_uvs.push_back(uv);
	// 			res = fscanf(file, "%s", lineHeader);
	// 			i++;
	// 		} while ( lineHeader == std::string("vn") ) {
	// 			glm::vec3 normal;
	// 			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
	// 			temp_normals.push_back(normal);
	// 			res = fscanf(file, "%s", lineHeader);
	// 			i++;
	// 		} 
	// 		if (lineHeader == std::string("usemtl")) {
	// 			res = fscanf(file, "%s", lineHeader); 
	// 			res = fscanf(file, "%s", lineHeader);
	// 		}
	// 		while ( lineHeader == std::string("f") ) {
	// 			std::string vertex1, vertex2, vertex3;
	// 			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
	// 			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3] );
	// 			if (matches != 12) {
	// 			    printf("File can't be read by our simple parser : ( Try exporting with other options\n");
	// 			    return;
	// 			}
	// 			vertexIndices.push_back(vertexIndex[0]);
	// 			vertexIndices.push_back(vertexIndex[1]);
	// 			vertexIndices.push_back(vertexIndex[2]);
	// 			vertexIndices.push_back(vertexIndex[3]);
	// 			uvIndices    .push_back(uvIndex[0]);
	// 			uvIndices    .push_back(uvIndex[1]);
	// 			uvIndices    .push_back(uvIndex[2]);
	// 			uvIndices    .push_back(uvIndex[3]);
	// 			normalIndices.push_back(normalIndex[0]);
	// 			normalIndices.push_back(normalIndex[1]);
	// 			normalIndices.push_back(normalIndex[2]);
	// 			normalIndices.push_back(normalIndex[3]);
	// 			res = fscanf(file, "%s", lineHeader);
	// 			if (lineHeader == std::string("usemtl")) {
	// 				res = fscanf(file, "%s", lineHeader); 
	// 				res = fscanf(file, "%s", lineHeader);
	// 			}
	// 			i++;
	// 		}
	// 	}
	// }
	// std::cout << "ok we are ready " << i << std::endl;
}
