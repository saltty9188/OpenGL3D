#include "Vector3.h"
#include <cmath>

using namespace Maths;

Vector3::Vector3(float x, float y, float z): _x{x}, _y{y}, _z{z}
{
}

const float Vector3::getX() const
{
	return _x;
}

const float Vector3::getY() const
{
	return _y;
}

const float Vector3::getZ() const
{
	return _z;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(_x + other._x, _y + other._y, _z + other._z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(_x - other._x, _y - other._y, _z - other._z);
}

Vector3 Vector3::operator*(const float scalar) const
{
	return Vector3(_x * scalar, _y * scalar, _z * scalar);
}

Vector3 Vector3::operator*(const Vector3& other) const
{
	return Vector3(_x * other._x, _y * other._y, _z * other._z);
}

bool Vector3::operator==(const Vector3& other) const
{
	return _x == other._x && _y == other._y && _z == other._z;
}

const Vector3 Vector3::cross(const Vector3& rhs) const
{
	return Vector3{_y * rhs._z - rhs._y * _z,
				   _z * rhs._x - rhs._z * _x,
				   _x * rhs._y - rhs._x * _y};
}

const float Vector3::dot(const Vector3& rhs) const
{
	return _x * rhs._x + _y * rhs._y + _z * rhs._z;
}

const float Vector3::length() const
{
	return sqrt(_x*_x+_y*_y+_z*_z);
}

const float Vector3::lengthSquared() const
{
	return _x * _x + _y * _y + _z * _z;
}

const Vector3 Vector3::normalized() const
{
	return *this * (1 / length());
}

const float Vector3::angle(const Vector3& other) const
{
	Vector3 v1{ this->normalized() };
	Vector3 v2{ other.normalized() };
	return acos(v1.dot(v2));
}

const Vector4 Maths::Vector3::toDir() const
{
	return {_x, _y, _z, 0};
}

const Vector4 Maths::Vector3::toPos() const
{
	return { _x, _y, _z, 1 };
}
