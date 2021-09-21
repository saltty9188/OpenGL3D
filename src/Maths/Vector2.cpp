#include "Vector2.h"
#include <cmath>

using namespace Maths;

Vector2::Vector2(float x, float y) : _x{ x }, _y{ y }
{
}

const float Vector2::getX() const
{
	return _x;
}

const float Vector2::getY() const
{
	return _y;
}


Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(_x + other._x, _y + other._y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(_x - other._x, _y - other._y);
}

Vector2 Vector2::operator*(const float scalar) const
{
	return Vector2(_x * scalar, _y * scalar);
}

Vector2 Vector2::operator*(const Vector2& other) const
{
	return Vector2(_x * other._x, _y * other._y);
}

bool Vector2::operator==(const Vector2& other) const
{
	return _x == other._x && _y == other._y;
}

const float Vector2::dot(const Vector2& rhs) const
{
	return _x * rhs._x + _y * rhs._y;
}

const float Vector2::length() const
{
	return sqrt(_x * _x + _y * _y);
}

const float Vector2::lengthSquared() const
{
	return _x * _x + _y * _y;
}

const Vector2 Vector2::normalized() const
{
	return *this * (1 / length());
}

const float Vector2::angle(const Vector2& other) const
{
	Vector2 v1{ this->normalized() };
	Vector2 v2{ other.normalized() };
	return acos(v1.dot(v2));
}
