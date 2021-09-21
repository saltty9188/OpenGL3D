#ifndef CYLINDER_H
#define CYLINDER_H
#include "Shape.h"
#include "Triangle.h"
#include <vector>

namespace Drawables
{
	class Cylinder : public Shape
	{
	public:
		Cylinder(const float radius, const float height, const Material& mat);
		~Cylinder() = default;

		virtual void init() override;
		virtual void draw() override;

	private:
		float _height;
		float _radius;
		std::vector<Triangle> _tris;

		void generateCirclePiece(std::vector<Triangle>&tris, const Maths::Vector2 & p1, const Maths::Vector2 & p2, const bool top);
		void generateSide(std::vector<Triangle>&tris, const Maths::Vector2 & p1, const Maths::Vector2 & p2);
	};
}

#endif // !CYLINDER_H
