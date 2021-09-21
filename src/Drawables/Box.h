#ifndef BOX_H
#define BOX_H
#include "Shape.h"
#include "Triangle.h"
#include <vector>

namespace Drawables
{
	class Box :public Shape
	{
	public:
		Box(float width, float height, float depth, Material m);
		~Box() = default;

		virtual void init() override;
		virtual void draw() override;

	private:
		float _width;
		float _height;
		float _depth;
		std::vector<Triangle> _tris;
	};
}

#endif // !BOX_H
