#include "Camera.h"
#include "../Maths/Matrix4.h"
#include "../Maths/Vector4.h"
#include <iostream>

Drawables::Camera::Camera(const Maths::Vector3& position, const Maths::Vector3& viewDir, const Maths::Vector3& up, const float aspectRation, const float heightAngle):
	_position{position}, _direction{viewDir}, _up{up}, _aspectRatio{aspectRation}, _heightAngle{heightAngle}, _right{}
{
	_right = _up.cross(_direction);
}

const float Drawables::Camera::getHeightAngle() const
{
	return _heightAngle;
}

const float Drawables::Camera::getAspectRatio() const
{
	return _aspectRatio;
}

void Drawables::Camera::setAspectRatio(const float aspectRatio)
{
	_aspectRatio = aspectRatio;
}

const Maths::Vector3 Drawables::Camera::getPosition() const
{
	return _position;
}

const Maths::Vector3 Drawables::Camera::getDirection() const
{
	return _direction;
}

const Maths::Vector3 Drawables::Camera::getUp() const
{
	return _up;
}

const Maths::Vector3 Drawables::Camera::getRight() const
{
	return _right;
}

void Drawables::Camera::move(const Maths::Vector3& displacement)
{
	Maths::Vector3 temp = _position + displacement;
	_position = temp;
}

void Drawables::Camera::rotateX(const float angle)
{
	// Using Rodrigues' Rotation Formula to rotate about the right axis
	Maths::Matrix4 W = { { 0, -_right.getZ(), _right.getY(), 0},
						{_right.getZ(), 0, -_right.getX(), 0},
						{-_right.getY(), _right.getX(), 0, 0},
						{0, 0, 0, 1} };

	Maths::Matrix4 identity{};
	Maths::Matrix4 rotationMatrix = identity + (W * sin(angle)) + (W * W * (2 * sin(angle / 2.0f) * sin(angle / 2.0f)));

	Maths::Vector4 tempDir = _direction.toDir();
	tempDir = rotationMatrix * tempDir;

	Maths::Vector4 tempUp = _up.toDir();
	tempUp = rotationMatrix * tempUp;

	_direction = { tempDir.getX(), tempDir.getY(), tempDir.getZ() };
	_up = { tempUp.getX(), tempUp.getY(), tempUp.getZ() };

	_right = _up.cross(_direction);

}

void Drawables::Camera::rotateY(const float angle)
{
	Maths::Matrix4 rotationMatrix = { {cosf(angle), 0.0f, sinf(angle), 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f },
		{-sinf(angle), 0.0f, cosf(angle), 0.0f },
		{0.0f, 0.0f, 0.0f, 1.0f }
	};

	Maths::Vector4 tempDir = _direction.toDir();
	tempDir = rotationMatrix * tempDir;

	Maths::Vector4 tempRight = _right.toDir();
	tempRight = rotationMatrix * tempRight;

	_direction = { tempDir.getX(), tempDir.getY(), tempDir.getZ() };
	_right = { tempRight.getX(), tempRight.getY(), tempRight.getZ() };

	_up = _direction.cross(_right);
}
