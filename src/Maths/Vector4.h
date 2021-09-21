#ifndef VECTOR4_H
#define VECTOR4_H

namespace Maths
{
	class Vector4
	{
	public:
		Vector4(float x = 0, float y = 0, float z = 0, float w = 0);
		~Vector4() = default;

		Vector4 operator+(const Vector4& other) const;
		Vector4 operator-(const Vector4& other) const;
		Vector4 operator*(const float scalar) const;
		Vector4 operator*(const Vector4& other) const;
		bool operator==(const Vector4& other) const;

		const float dot(const Vector4& rhs) const;
		const float length() const;
		const float lengthSquared() const;
		const Vector4 normalized() const;
		const float angle(const Vector4& other) const;
		

		const float getX() const;
		const float getY() const;
		const float getZ() const;
		const float getW() const;

	private:
		float _x;
		float _y;
		float _z;
		float _w;
	};
}
#endif // VECTOR4_H


