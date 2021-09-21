#ifndef VECTOR2_H
#define VECTOR2_H

namespace Maths
{
	class Vector2
	{
	public:
		Vector2(float x = 0, float y = 0);
		~Vector2() = default;

		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator*(const float scalar) const;
		Vector2 operator*(const Vector2& other) const;
		bool operator==(const Vector2& other) const;

		const float dot(const Vector2& rhs) const;
		const float length() const;
		const float lengthSquared() const;
		const Vector2 normalized() const;
		const float angle(const Vector2& other) const;

		const float getX() const;
		const float getY() const;

	private:
		float _x;
		float _y;
	};
}
#endif // VECTOR2_H


