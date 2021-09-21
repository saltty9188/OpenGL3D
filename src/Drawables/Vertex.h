#ifndef VERTEX_H
#define VERTEX_H
#include "../Maths/Vector3.h"
#include "../Maths/Vector2.h"
namespace Drawables
{
	struct Vertex
	{
		Maths::Vector3 position = {};
		Maths::Vector3 normal = {};
		Maths::Vector2 texCoord = {};
		Maths::Vector3 colour = {};
	};
}

#endif // !VERTEX_H
