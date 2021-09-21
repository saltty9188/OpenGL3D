#include "Triangle.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace Drawables;

Drawables::Triangle::Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Material& material):
	Shape{material}, _v1{v1}, _v2{v2}, _v3{v3}, _vertData{}
{
}

int Triangle::i{ 0 };

void Drawables::Triangle::init()
{
	_vertData = { _v1.position.getX(), _v1.position.getY(), _v1.position.getZ(), _v1.colour.getX(), _v1.colour.getY(), _v1.colour.getZ(), 1.0f,
						_v1.normal.getX(), _v1.normal.getY(), _v1.normal.getZ(), _v1.texCoord.getX(), _v1.texCoord.getY(),
						_v2.position.getX(), _v2.position.getY(), _v2.position.getZ(), _v2.colour.getX(), _v2.colour.getY(), _v2.colour.getZ(), 1.0f,
						_v2.normal.getX(), _v2.normal.getY(), _v2.normal.getZ(), _v2.texCoord.getX(), _v2.texCoord.getY(),
						_v3.position.getX(), _v3.position.getY(), _v3.position.getZ(), _v3.colour.getX(), _v3.colour.getY(), _v3.colour.getZ(), 1.0f,
						_v3.normal.getX(), _v3.normal.getY(), _v3.normal.getZ(), _v3.texCoord.getX(), _v3.texCoord.getY() };

	glGenVertexArrays(1, &_vao);
	unsigned int buffer;
	glGenBuffers(1, &buffer);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), _vertData.data(), GL_STATIC_DRAW);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (const void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (const void*)(7 * sizeof(float)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (const void*)(10 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	//std::cout << "Triangle " << i++ << " positions: " << std::endl;
	//std::cout << "(" << _v1.position.getX() << ", " << _v1.position.getY() << ", " << _v1.position.getZ() << ")" << std::endl;
	//std::cout << "(" << _v2.position.getX() << ", " << _v2.position.getY() << ", " << _v2.position.getZ() << ")" << std::endl;
	//std::cout << "(" << _v3.position.getX() << ", " << _v3.position.getY() << ", " << _v3.position.getZ() << ")" << std::endl;
}

void Drawables::Triangle::draw()
{
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
