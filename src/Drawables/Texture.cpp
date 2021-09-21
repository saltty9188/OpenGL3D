#include "Texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace Drawables;


Texture::Texture(const std::string& fileName) : _filePath{ fileName }, _texID{0}, _loaded{ false }, _pixels{ nullptr }, _width{0}, _height{0}, _bitsPerPixel{0}
{
	if (fileName != "")
	{
		//stbi_set_flip_vertically_on_load(1);
		_pixels = stbi_load(fileName.c_str(), &_width, &_height, &_bitsPerPixel, 4);

		_loaded = sizeof(_pixels) > 0;
	}
		
}

Drawables::Texture::~Texture()
{
	glDeleteTextures(1, &_texID);
}

const bool Texture::operator==(const Texture& other) const
{
	return _texID == other._texID && _filePath == other._filePath && _width == other._width && _height == other._height && _bitsPerPixel == other._bitsPerPixel;
}

const bool Texture::isLoaded() const 
{
	return _loaded;
}


void Drawables::Texture::init()
{
	glGenTextures(1, &_texID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, 0);

	if (_pixels)
		stbi_image_free(_pixels);
}

void Texture::setActive()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texID);
}

const int Drawables::Texture::getWidth() const
{
	return _width;
}

const int Drawables::Texture::getHeight() const
{
	return _height;
}
