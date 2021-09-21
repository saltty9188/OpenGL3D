#ifndef VECTOR3_H
#define VECTOR3_H
#include "Vector4.h"

namespace Maths
{
	class Vector3
	{
	public:
		Vector3(float x = 0, float y = 0, float z = 0);
		~Vector3() = default;

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		Vector3 operator*(const float scalar) const;
		Vector3 operator*(const Vector3& other) const;
		bool operator==(const Vector3& other) const;

		const Vector3 cross(const Vector3& rhs) const;
		const float dot(const Vector3& rhs) const;
		const float length() const;
		const float lengthSquared() const;
		const Vector3 normalized() const;
		const float angle(const Vector3& other) const;
		const Vector4 toDir() const;
		const Vector4 toPos() const;

		const float getX() const;
		const float getY() const;
		const float getZ() const;

	private:
		float _x;
		float _y;
		float _z;
	};
}
#endif // VECTOR3_H


