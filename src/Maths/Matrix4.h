#ifndef MATRIX4_H
#define MATRIX4_H
#include <array>
#include "Vector4.h"

namespace Maths
{
	class Matrix4
	{
	public:
		/*
		Creates an identity Matrix
		*/
		Matrix4();
		Matrix4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3);
		Matrix4(std::array<std::array<float, 4>, 4> vals);
		~Matrix4() = default;

		const Matrix4 operator+(const Matrix4& other) const;
		const Matrix4 operator-(const Matrix4& other) const;
		const Matrix4 operator*(const Matrix4& rhs) const;
		const Vector4 operator*(const Vector4& rhs) const;
		const Matrix4 operator*(const float scalar) const;

		const float get(int row, int column) const;
		const Matrix4 transpose() const;
		const float determinant() const;
		const Matrix4 invert() const;
		//const Ray transform(Ray ray) const;
		const float* toOpenGL() const;
	private:
		
		std::array<std::array<float, 4>, 4> _vals;
		float _glArray[16];
	};
}

#endif // MATRIX4_H