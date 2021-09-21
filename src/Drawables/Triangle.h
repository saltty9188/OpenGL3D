#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"
#include "Vertex.h"
#include <array>
namespace Drawables
{
	class Triangle : public Shape
	{
	public:
		Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Material& material);
		~Triangle() = default;

		virtual void init() override;
		virtual void draw() override;

		static int i;

	private:
		Vertex _v1;
		Vertex _v2;
		Vertex _v3;
		std::array<float, 36> _vertData;

		unsigned int _vao;
	};
}
#endif // !TRIANGLE_H
