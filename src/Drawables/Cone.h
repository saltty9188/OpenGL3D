#ifndef CONE_H
#define CONE_H
#include "Shape.h"
#include "Triangle.h"
#include <vector>

namespace Drawables
{
	class Cone : public Shape
	{
	public:
		Cone(const float radius, const float height, const Material& mat);
		~Cone() = default;

		virtual void init() override;
		virtual void draw() override;

	private:
		float _height;
		float _radius;
		std::vector<Triangle> _tris;

		void generateCirclePiece(std::vector<Triangle>& tris, const Maths::Vector2& p1, const Maths::Vector2& p2);
		void generateSide(std::vector<Triangle>& tris, const Maths::Vector2& p1, const Maths::Vector2& p2);
	};
}
#endif // !CONE_H
