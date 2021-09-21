#ifndef SPHERE_H
#define SPHERE_H
#include "Shape.h"
#include <vector>
#include "Triangle.h"
namespace Drawables
{
	class Sphere : public Shape
	{
	public:
		Sphere(const float radius, const Material& mat);
		~Sphere() = default;

		virtual void init() override;
		virtual void draw() override;

	private:
		float _radius;
		std::vector<Triangle> _tris;
	};
}
#endif // !SPHERE_H



