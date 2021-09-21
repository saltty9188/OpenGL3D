#define _USE_MATH_DEFINES
#include "Sphere.h"
#include <cmath>

Drawables::Sphere::Sphere(const float radius, const Material& mat):
	Shape(mat), _radius{radius}, _tris{}
{
}

void Drawables::Sphere::init()
{
	int sectorCount = 32;
	int stackCount = 32;

	// sector is a "row" of a sphere
	float sectorStep = (float)(2 * M_PI / sectorCount);
	// stack is a "column" of a sphere
	float stackStep = (float)(M_PI / stackCount);

	for (int i = 0; i < stackCount; i++)
	{
		// Go from top to bottom PI/2 to -PI/2
		//For each stack get this one and the next one to form triangles
		float stackAngle = (float)(M_PI / 2 - i * stackStep);
		float xz1 = _radius * cosf(stackAngle);
		float y1 = _radius * sinf(stackAngle);

		stackAngle = M_PI / 2 - (i + 1) * stackStep;
		float xz2 = _radius * cosf(stackAngle);
		float y2 = _radius * sinf(stackAngle);

		for (int j = 0; j < sectorCount; j++) 
		{
			// Step from left to right 0 to 2PI
			float sectorAngle1 = j * sectorStep;
			float sectorAngle2 = (j + 1) * sectorStep;
			Vertex v1{};
			v1.colour = material.diffuse;
			Vertex v2{};
			v2.colour = material.diffuse;
			Vertex v3{};
			v3.colour = material.diffuse;
			Vertex v4{};
			v4.colour = material.diffuse;

			// Top and bottom sectors only have one triangle per stack
			if (i == 0) 
			{
				v1.position = { 0, _radius, 0 };
				v1.normal = { 0, 1, 0 };
				v1.texCoord = {};

				float x2 = xz2 * cosf(sectorAngle1);
				float z2 = xz2 * sinf(sectorAngle1);
				v2.position = { x2, y2, z2 };
				v2.normal = v2.position * (1 / _radius);
				v2.texCoord = {};

				float x3 = xz2 * cosf(sectorAngle2);
				float z3 = xz2 * sinf(sectorAngle2);
				v3.position = { x3, y2, z3 };
				v3.normal = v3.position * (1 / _radius);
				v3.texCoord = {};

				_tris.push_back({ v1, v3, v2, material });
			}
			else if (i == stackCount - 1)
			{
				float x1 = xz1 * cosf(sectorAngle1);
				float z1 = xz1 * sinf(sectorAngle1);
				v1.position = { x1, y1, z1 };
				v1.normal = v1.position * (1 / _radius);
				v1.texCoord = {};

				float x2 = xz1 * cosf(sectorAngle2);
				float z2 = xz1 * sinf(sectorAngle2);
				v2.position = { x2, y1, z2 };
				v2.normal = v2.position * (1 / _radius);
				v2.texCoord = {};

				v3.position = { 0, -_radius, 0 };
				v3.normal = { 0, -1, 0 };
				v3.texCoord = {};

				_tris.push_back({ v1, v3, v2, material });
			}
			else 
			{
				float x1 = xz1 * cosf(sectorAngle1);
				float z1 = xz1 * sinf(sectorAngle1);
				v1.position = { x1, y1, z1 };
				v1.normal = v1.position * (1 / _radius);
				v1.texCoord = {};

				float x2 = xz1 * cosf(sectorAngle2);
				float z2 = xz1 * sinf(sectorAngle2);
				v2.position = { x2, y1, z2 };
				v2.normal = v2.position * (1 / _radius);
				v2.texCoord = {};

				float x3 = xz2 * cosf(sectorAngle1);
				float z3 = xz2 * sinf(sectorAngle1);
				v3.position = { x3, y2, z3 };
				v3.normal = v3.position * (1 / _radius);
				v3.texCoord = {};

				float x4 = xz2 * cosf(sectorAngle2);
				float z4 = xz2 * sinf(sectorAngle2);
				v4.position = { x4, y2, z4 };
				v4.normal = v4.position * (1 / _radius);
				v4.texCoord = {};

				_tris.push_back({ v2, v3, v1, material });
				_tris.push_back({ v2, v4, v3, material });
			}
		}
	}

	for (auto& tri : _tris)
	{
		tri.init();
	}
}

void Drawables::Sphere::draw()
{
	for (auto& tri : _tris)
	{
		tri.draw();
	}
}
