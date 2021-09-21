#include "Vector4.h"
#include <cmath>

using namespace Maths;

Vector4::Vector4(float x, float y, float z, float w) : _x{ x }, _y{ y }, _z{ z }, _w{w}
{
}

const float Vector4::getX() const
{
	return _x;
}

const float Vector4::getY() const
{
	return _y;
}

const float Vector4::getZ() const
{
	return _z;
}

const float Vector4::getW() const
{
	return _w;
}

Vector4 Vector4::operator+(const Vector4& other) const
{
	return Vector4(_x + other._x, _y + other._y, _z + other._z, _w + other._w);
}

Vector4 Vector4::operator-(const Vector4& other) const
{
	return Vector4(_x - other._x, _y - other._y, _z - other._z, _w - other._w);
}

Vector4 Vector4::operator*(const float scalar) const
{
	return Vector4(_x * scalar, _y * scalar, _z * scalar, _w * scalar);
}

Vector4 Vector4::operator*(const Vector4& other) const
{
	return Vector4(_x * other._x, _y * other._y, _z * other._z, _w * other._w);
}

bool Vector4::operator==(const Vector4& other) const
{
	return _x == other._x && _y == other._y && _z == other._z && _w == other._w;
}


const float Vector4::dot(const Vector4& rhs) const
{
	return _x * rhs._x + _y * rhs._y + _z * rhs._z + _w * rhs._w;
}

const float Vector4::length() const
{
	return sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
}

const float Vector4::lengthSquared() const
{
	return _x * _x + _y * _y + _z * _z + _w * _w;
}

const Vector4 Vector4::normalized() const
{
	return *this * (1 / length());
}

const float Vector4::angle(const Vector4& other) const
{
	Vector4 v1{ this->normalized() };
	Vector4 v2{ other.normalized() };
	return acos(v1.dot(v2));
}
