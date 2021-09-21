#define _USE_MATH_DEFINES
#include "Cylinder.h"
#include <cmath>

Drawables::Cylinder::Cylinder(const float _radius, const float _height, const Material& mat) :
	Shape(mat), _radius{ _radius }, _height{ _height }, _tris{}
{
}

void Drawables::Cylinder::init()
{
	int faceCount = 32;

	// Make faces
	for (int i = 0; i < faceCount; i++)
	{
		float angle1 = i * 2 * M_PI / faceCount;
		float angle2 = (i + 1) * 2 * M_PI / faceCount;

		Maths::Vector2 p1{ _radius * cosf(angle1), _radius * sinf(angle1) };
		Maths::Vector2 p2{ _radius * cosf(angle2), _radius * sinf(angle2) };

		generateCirclePiece(_tris, p2, p1, false);
		generateCirclePiece(_tris, p2, p1, true);
	}

	// make sides
	for (int i = 0; i < faceCount; i++) {
		float angle1 = i * 2.0f * M_PI / faceCount;
		float angle2 = (i + 1.0f) * 2.0f * M_PI / faceCount;

		Maths::Vector2 p1{ _radius * (float)cosf(angle1), _radius * (float)sinf(angle1) };
		Maths::Vector2 p2{ _radius * (float)cosf(angle2), _radius * (float)sinf(angle2) };

		generateSide(_tris, p2, p1);
	}

	for (auto& tri : _tris)
	{
		tri.init();
	}
}

void Drawables::Cylinder::draw()
{
	for (auto& tri : _tris)
	{
		tri.draw();
	}
}

void Drawables::Cylinder::generateCirclePiece(std::vector<Triangle>& tris, const Maths::Vector2& p1, const Maths::Vector2& p2, const bool top)
{
	float y = (top ? _height / 2.0f : -_height / 2.0f);
	Maths::Vector3 normal = (top ? Maths::Vector3{ 0, 1, 0 } : Maths::Vector3{ 0, -1, 0 });

	Vertex v1{};
	Vertex v2{};
	Vertex v3{};

	v1.position = { p2.getX(), y, p2.getY() };
	v2.position = { 0, y, 0 };
	v3.position = { p1.getX(), y, p1.getY() };

	v1.normal = normal;
	v2.normal = normal;
	v3.normal = normal;

	v1.colour = material.diffuse;
	v2.colour = material.diffuse;
	v3.colour = material.diffuse;

	v1.texCoord = {};
	v2.texCoord = {};
	v3.texCoord = {};

	tris.push_back({ v1, v2, v3, material });
}

void Drawables::Cylinder::generateSide(std::vector<Triangle>& tris, const Maths::Vector2& p1, const Maths::Vector2& p2)
{
	Vertex v1{};
	Vertex v2{};
	Vertex v3{};
	Vertex v4{};

	v1.position = { p2.getX(), _height / 2, p2.getY() };
	v2.position = { p1.getX(), _height / 2, p1.getY() };
	v3.position = { p1.getX(), -_height / 2, p1.getY() };
	v4.position = { p2.getX(), -_height / 2, p2.getY() };

	v1.normal = Maths::Vector3{ p2.getX(), 0, p2.getY() } * (1 / _radius);
	v2.normal = Maths::Vector3{ p1.getX(), 0, p1.getY() } * (1 / _radius);
	v3.normal = Maths::Vector3{ p1.getX(), 0, p1.getY() } * (1 / _radius);
	v4.normal = Maths::Vector3{ p2.getX(), 0, p2.getY() } * (1 / _radius);

	v1.colour = material.diffuse;
	v2.colour = material.diffuse;
	v3.colour = material.diffuse;
	v4.colour = material.diffuse;

	tris.push_back({ v1, v2, v3, material });
	tris.push_back({ v1, v3, v4, material });
}
