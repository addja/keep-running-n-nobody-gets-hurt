// Model class

#include "include/cModel.hpp"

cModel::cModel() {}

cModel::~cModel() {
	// Cleanup VBO and shader
 	glDeleteBuffers(1, &vertexbuffer_quads);
	glDeleteBuffers(1, &uvbuffer_quads);
	glDeleteBuffers(1, &normalbuffer_quads);
	glDeleteBuffers(1, &vertexbuffer_triangles);
	glDeleteBuffers(1, &uvbuffer_triangles);
	glDeleteBuffers(1, &normalbuffer_triangles);
	glDeleteProgram(programID);
	glDeleteTextures(1, &textureID);
}

void cModel::loadModel(std::string filename) {
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices, vertexIndices_triangles, uvIndices_triangles, normalIndices_triangles;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(filename.c_str(), "r");
	std::cout << filename.c_str() << std::endl;
	if( file == NULL ) {
		std::cout << "Impossible to open the file!" << std::endl;
		return;
	}

	char lineHeader[128];
	// read the first word of the line
	int res = fscanf(file, "%s", lineHeader);
	while(1) {	 
		if (res == EOF) {
			break; // EOF = End Of File. Quit the loop.
		} else if ( lineHeader == std::string("v") ) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		} else if( lineHeader == std::string("vt") ) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		} else if ( lineHeader == std::string("vn") ) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		} else if ( lineHeader == std::string("f") ) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3] );

			if (matches != 12 && matches != 9) {
			    printf("File can't be read by our simple parser : ( Try exporting with other options, %d\n", matches);
			    return;
			}
			if (matches == 12) {
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				vertexIndices.push_back(vertexIndex[3]);
				uvIndices    .push_back(uvIndex[0]);
				uvIndices    .push_back(uvIndex[1]);
				uvIndices    .push_back(uvIndex[2]);
				uvIndices    .push_back(uvIndex[3]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
				normalIndices.push_back(normalIndex[3]);
			} else {
				vertexIndices_triangles.push_back(vertexIndex[0]);
				vertexIndices_triangles.push_back(vertexIndex[1]);
				vertexIndices_triangles.push_back(vertexIndex[2]);
				uvIndices_triangles    .push_back(uvIndex[0]);
				uvIndices_triangles    .push_back(uvIndex[1]);
				uvIndices_triangles    .push_back(uvIndex[2]);
				normalIndices_triangles.push_back(normalIndex[0]);
				normalIndices_triangles.push_back(normalIndex[1]);
				normalIndices_triangles.push_back(normalIndex[2]);
			}
			
		}
		res = fscanf(file, "%s", lineHeader);
	}

	for( unsigned int i=0; i<vertexIndices.size(); i++ ){
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		vertices_quads.push_back(vertex);
	}

	for( unsigned int i=0; i<uvIndices.size(); i++ ){
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		uvs_quads.push_back(uv);
	}

	for( unsigned int i=0; i<normalIndices.size(); i++ ){
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		normals_quads.push_back(normal);
	}

	for( unsigned int i=0; i<vertexIndices_triangles.size(); i++ ){
		unsigned int vertexIndex = vertexIndices_triangles[i];
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		vertices_triangles.push_back(vertex);
	}

	for( unsigned int i=0; i<uvIndices_triangles.size(); i++ ){
		unsigned int uvIndex = uvIndices_triangles[i];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		uvs_triangles.push_back(uv);
	}

	for( unsigned int i=0; i<normalIndices_triangles.size(); i++ ){
		unsigned int normalIndex = normalIndices_triangles[i];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		normals_triangles.push_back(normal);
	}

	initGL();

	printf("loadModel done correctly\n");
}

void cModel::initGL() {
	glGenBuffers(1, &vertexbuffer_quads);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_quads);
	glBufferData(GL_ARRAY_BUFFER, vertices_quads.size() * sizeof(glm::vec3), &vertices_quads[0], GL_STATIC_DRAW);

	glGenBuffers(1, &vertexbuffer_triangles);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_triangles);
	glBufferData(GL_ARRAY_BUFFER, vertices_triangles.size() * sizeof(glm::vec3), &vertices_triangles[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer_quads);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_quads);
	glBufferData(GL_ARRAY_BUFFER, uvs_quads.size() * sizeof(glm::vec2), &uvs_quads[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer_triangles);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_triangles);
	glBufferData(GL_ARRAY_BUFFER, uvs_triangles.size() * sizeof(glm::vec2), &uvs_triangles[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer_quads);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_quads);
	glBufferData(GL_ARRAY_BUFFER, normals_quads.size() * sizeof(glm::vec3), &normals_quads[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer_triangles);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_triangles);
	glBufferData(GL_ARRAY_BUFFER, normals_triangles.size() * sizeof(glm::vec3), &normals_triangles[0], GL_STATIC_DRAW);
	
	programID = loadShaders("src/shaders/model.vert", "src/shaders/model.frag");
	
	mvp_handle = glGetUniformLocation(programID, "MVP");
	ViewMatrix_handle = glGetUniformLocation(programID, "V");
	ModelMatrix_handle = glGetUniformLocation(programID, "M");
	textureID  = glGetUniformLocation(programID, "myTextureSampler");
	LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	calcBBox();
}

void cModel::render(GLuint texture, glm::vec3 p, glm::vec3 r, glm::vec3 s, float angle, glm::vec3 cameraP, int front) {

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	 glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) WNDW_WIDTH / (float)WNDW_HEIGHT, 0.1f, 1.0f);
	
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	glm::vec3 cameraPos = cameraP + glm::vec3(front, 1, front) * glm::vec3(25,25,25);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
	               cameraPos, // Camera is at (4,3,3), in World Space
	               cameraP, // and looks at the origin
	               glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	               );
	
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::translate(p) * glm::scale(s) * glm::rotate(angle, r);

	// for (int j = 0; j < 4; j++) {
	// 	for (int jj = 0; jj < 4; jj++) {
	// 		std::cout << Projection[j][jj] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout << "----------------------------------------\n";

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Use shader
	glUseProgram(programID);
	
	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(ModelMatrix_handle, 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(ViewMatrix_handle, 1, GL_FALSE, &View[0][0]);
	glUniform3f(LightID, cameraPos.x, cameraPos.y + 15, cameraPos.z);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(textureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_quads);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_quads);
	glVertexAttribPointer(
	     1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
	     2,                                // size
	     GL_FLOAT,	                       // type
	     GL_FALSE,                         // normalized?
	     0,                                // stride
	     (void*)0                          // array buffer offset
	);	
	
	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_quads);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glDrawArrays(GL_QUADS, 0, vertices_quads.size());
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_triangles);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_triangles);
	glVertexAttribPointer(
	     1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
	     2,                                // size
	     GL_FLOAT,	                       // type
	     GL_FALSE,                         // normalized?
	     0,                                // stride
	     (void*)0                          // array buffer offset
	);	

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer_triangles);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	
	glDrawArrays(GL_TRIANGLES, 0, vertices_triangles.size());
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	if (DEBUG_MODE) renderBBox();
}

void cModel::calcBBox() {
	if (vertices_quads.size() == 0) {
		maxx = minx = vertices_triangles[0][0];
		maxy = miny = vertices_triangles[0][1];
		maxz = minz = vertices_triangles[0][2];
	}
	else {
		maxx = minx = vertices_quads[0][0];
		maxy = miny = vertices_quads[0][1];
		maxz = minz = vertices_quads[0][2];
	}	
	for (int i = 0; i < (int)vertices_quads.size(); i++) {
		if (vertices_quads[i][0] < minx) minx = vertices_quads[i][0];
		else if (vertices_quads[i][0] > maxx) maxx = vertices_quads[i][0];
		if (vertices_quads[i][1] < miny) miny = vertices_quads[i][1];
		else if (vertices_quads[i][1] > maxy) maxy = vertices_quads[i][1];
		if (vertices_quads[i][2] < minz) minz = vertices_quads[i][2];
		else if (vertices_quads[i][2] > maxz) maxz = vertices_quads[i][2];
	}
	for (int i = 0; i < (int)vertices_triangles.size(); i++) {
		if (vertices_triangles[i][0] < minx) minx = vertices_triangles[i][0];
		else if (vertices_triangles[i][0] > maxx) maxx = vertices_triangles[i][0];
		if (vertices_triangles[i][1] < miny) miny = vertices_triangles[i][1];
		else if (vertices_triangles[i][1] > maxy) maxy = vertices_triangles[i][1];
		if (vertices_triangles[i][2] < minz) minz = vertices_triangles[i][2];
		else if (vertices_triangles[i][2] > maxz) maxz = vertices_triangles[i][2];
	}
}

void cModel::renderBBox() {
	// not very efficient but useful and simple (just displayed on debug mode)
	glBegin(GL_LINE_STRIP);
		glVertex3f(maxx, maxy, maxz);
		glVertex3f(minx, maxy, maxz);
		glVertex3f(minx, maxy, minz);
		glVertex3f(maxx, maxy, minz);
		glVertex3f(maxx, maxy, maxz);
    glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex3f(maxx, miny, maxz);
		glVertex3f(minx, miny, maxz);
		glVertex3f(minx, miny, minz);
		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx, miny, maxz);
    glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex3f(maxx, miny, maxz);
		glVertex3f(maxx, maxy, maxz);
		glVertex3f(maxx, maxy, minz);
		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx, miny, maxz);
    glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex3f(minx, miny, maxz);
		glVertex3f(minx, maxy, maxz);
		glVertex3f(minx, maxy, minz);
		glVertex3f(minx, miny, minz);
		glVertex3f(minx, miny, maxz);
    glEnd();
}
