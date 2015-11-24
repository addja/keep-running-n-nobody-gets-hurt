// class to handle textures

#include "include/cTexture.hpp"

GLuint loadTex(std::string filename) {
	sf::Image img_data;
	if (!img_data.loadFromFile(filename))  {
			    std::cout << "Could not load " << filename << std::endl;
	}

	GLuint texture_handle;
	glGenTextures(1, &texture_handle);

	glBindTexture(GL_TEXTURE_2D, texture_handle);

	glTexImage2D(
					GL_TEXTURE_2D, 0, GL_RGBA,
					img_data.getSize().x, img_data.getSize().y,
					0,
					GL_RGBA, 
					GL_UNSIGNED_BYTE, 
					img_data.getPixelsPtr()
				);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// this generates the mipmaps on run time, 
	// performace can be increased 20% by preprocessing this outside the code
	//glGenerateMipmap(GL_TEXTURE_2D);

	return texture_handle;
}
