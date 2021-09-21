#ifndef SHAPE_H
#define SHAPE_H
#include "Vertex.h"
#include "Material.h"
#include "../Maths/Matrix4.h"
namespace Drawables
{
	class Shape
	{
	public:
		Shape(const Material& material);
		virtual ~Shape() = default;
		virtual void init() = 0;
		virtual void draw() = 0;

		Maths::Matrix4 transform;
		Material material;
	};
}
#endif // !SHAPE_H


