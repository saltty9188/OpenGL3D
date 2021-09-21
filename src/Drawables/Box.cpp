#include "Box.h"

using namespace Drawables;

Drawables::Box::Box(float width, float height, float depth, Material m): Shape(m), _width{width}, _height{height}, _depth{depth}, _tris{}
{
}

void Drawables::Box::init()
{
	// Define the vertex points and their colours
	// Each vertex is repeated 3 times for unique normal information
	Vertex v1A{};
	v1A.position = { _width / 2, _height / 2, _depth / 2 };
	v1A.colour = material.diffuse;

	Vertex v1B{};
	v1B.position = v1A.position;
	v1B.colour = material.diffuse;

	Vertex v1D{};
	v1D.position = v1A.position;
	v1D.colour = material.diffuse;

	Vertex v2A{};
	v2A.position = { -_width / 2, _height / 2, _depth / 2 };
	v2A.colour = material.diffuse;

	Vertex v2D{};
	v2D.position = v2A.position;
	v2D.colour = material.diffuse;

	Vertex v2E{};
	v2E.position = v2A.position;
	v2E.colour = material.diffuse;

	Vertex v3A{};
	v3A.position = {-_width / 2, -_height / 2, _depth / 2};
	v3A.colour = material.diffuse;

	Vertex v3C{};
	v3C.position = v3A.position;
	v3C.colour = material.diffuse;

	Vertex v3E{};
	v3E.position = v3A.position;
	v3E.colour = material.diffuse;

	Vertex v4A{};
	v4A.position = {_width / 2, -_height / 2, _depth / 2};
	v4A.colour = material.diffuse;

	Vertex v4B{};
	v4B.position = v4A.position;
	v4B.colour = material.diffuse;

	Vertex v4C{};
	v4C.position = v4A.position;
	v4C.colour = material.diffuse;

	Vertex v5B{};
	v5B.position = {_width / 2, _height / 2, -_depth / 2};
	v5B.colour = material.diffuse;

	Vertex v5D{};
	v5D.position = v5B.position;
	v5D.colour = material.diffuse;

	Vertex v5F{};
	v5F.position = v5B.position;
	v5F.colour = material.diffuse;

	Vertex v6D{};
	v6D.position = {-_width / 2, _height / 2, -_depth / 2};
	v6D.colour = material.diffuse;

	Vertex v6E{};
	v6E.position = v6D.position;
	v6E.colour = material.diffuse;

	Vertex v6F{};
	v6F.position = v6D.position;
	v6F.colour = material.diffuse;

	Vertex v7C{};
	v7C.position = {-_width / 2, -_height / 2, -_depth / 2};
	v7C.colour = material.diffuse;

	Vertex v7E{};
	v7E.position = v7C.position;
	v7E.colour = material.diffuse;

	Vertex v7F{};
	v7F.position = v7C.position;
	v7F.colour = material.diffuse;

	Vertex v8B{};
	v8B.position = {_width / 2, -_height / 2, -_depth / 2};
	v8B.colour = material.diffuse;

	Vertex v8C{};
	v8C.position = v8B.position;
	v8C.colour = material.diffuse;

	Vertex v8F{};
	v8F.position = v8B.position;
	v8F.colour = material.diffuse;

	// calculate normals
	v1A.normal = (v2A.position - v1A.position).cross(v4A.position - v1A.position).normalized();
	v2A.normal = v1A.normal;
	v3A.normal = v1A.normal;
	v4A.normal = v1A.normal;

	v1B.normal = (v4B.position - v1B.position).cross(v5B.position - v1B.position).normalized();
	v4B.normal = v1B.normal;
	v5B.normal = v1B.normal;
	v8B.normal = v1B.normal;

	v3C.normal = (v7C.position - v3C.position).cross(v4C.position - v3C.position).normalized();
	v4C.normal = v3C.normal;
	v7C.normal = v3C.normal;
	v8C.normal = v3C.normal;

	v1D.normal = (v5D.position - v1D.position).cross(v2D.position - v1D.position).normalized();
	v2D.normal = v1D.normal;
	v5D.normal = v1D.normal;
	v6D.normal = v1D.normal;

	v2E.normal = (v6E.position - v2E.position).cross(v3E.position - v2E.position).normalized();
	v3E.normal = v2E.normal;
	v6E.normal = v2E.normal;
	v7E.normal = v2E.normal;

	v5F.normal = (v8F.position - v5F.position).cross(v6F.position - v5F.position).normalized();
	v6F.normal = v5F.normal;
	v7F.normal = v5F.normal;
	v8F.normal = v5F.normal;

	//Define texture co-ordinates per face
	v1A.texCoord = {1, 0};
	v2A.texCoord = {0, 0};
	v3A.texCoord = {0, 1};
	v4A.texCoord = {1, 1};

	v1B.texCoord = {0, 0};
	v4B.texCoord = {0, 1};
	v8B.texCoord = {1, 1};
	v5B.texCoord = {1, 0};

	v4C.texCoord = {1, 0};
	v3C.texCoord = {0, 0};
	v7C.texCoord = {0, 1};
	v8C.texCoord = {1, 1};

	v2D.texCoord = {0, 1};
	v1D.texCoord = {1, 1};
	v5D.texCoord = {1, 0};
	v6D.texCoord = {0, 0};

	v3E.texCoord = {1, 1};
	v2E.texCoord = {1, 0};
	v6E.texCoord = {0, 0};
	v7E.texCoord = {0, 1};

	v6F.texCoord = {1, 0};
	v5F.texCoord = {0, 0};
	v8F.texCoord = {0, 1};
	v7F.texCoord = {1, 1};

	// Make triangles from verts
	// Face A
	_tris.push_back({v1A, v2A, v3A, material});
	_tris.push_back({v1A, v3A, v4A, material});

	// Face B
	_tris.push_back({v1B, v4B, v8B, material});
	_tris.push_back({v1B, v8B, v5B, material});

	// face C
	_tris.push_back({v4C, v3C, v7C, material});
	_tris.push_back({v4C, v7C, v8C, material});

	// Face D
	_tris.push_back({v2D, v1D, v5D, material});
	_tris.push_back({v2D, v5D, v6D, material});

	// Face E
	_tris.push_back({v3E, v2E, v6E, material});
	_tris.push_back({v3E, v6E, v7E, material});

	// Face F
	_tris.push_back({v6F, v5F, v8F, material});
	_tris.push_back({v6F, v8F, v7F, material});

	for (auto& tri : _tris) {
		tri.init();
	}
}

void Drawables::Box::draw()
{
	for (auto& tri : _tris) {
		tri.draw();
	}
}
