#define _USE_MATH_DEFINES
#include "MatrixFactory.h"
#include "Vector4.h"
#include <cmath>

using namespace Maths;


const Matrix4 MatrixFactory::perspective(float fovY, float aspect, float zNear, float zFar)
{
	float f = (1.0f / tan((fovY * (M_PI / 180)) / 2.0f));
	float z1 = (zFar + zNear) / (zNear - zFar);
	float z2 = (2 * zFar * zNear) / (zNear - zFar);
	
	std::array<std::array<float, 4>, 4> vals{};
	vals[0][0] = f / aspect;
	vals[1][1] = f;
	vals[2][2] = z1;
	vals[2][3] = z2;
	vals[3][2] = -1;

	return Matrix4(vals);
}

const Matrix4 MatrixFactory::lookInDirection(Vector3 eye, Vector3 viewDir, Vector3 up)
{
	Vector3 viewUp = (up - (viewDir * (up.dot(viewDir)))).normalized();
	Vector3 viewSide = viewDir.cross(viewUp);
	Vector4 zeroes = { 0, 0, 0, 1 };

	Matrix4 rotation = { viewSide.toDir(), viewUp.toDir(), (viewDir * -1).toDir(), zeroes };

	Vector4 eyeInv = (rotation * (eye.toPos())) * -1;

	Matrix4 result = {
		{viewSide.getX(), viewSide.getY(), viewSide.getZ(), eyeInv.getX()},
		{viewUp.getX(), viewUp.getY(), viewUp.getZ(), eyeInv.getY()},
		{-viewDir.getX(), -viewDir.getY(), -viewDir.getZ(), eyeInv.getZ()},
		{0, 0, 0, 1}
	};
	return result;
}

const Matrix4 MatrixFactory::lookAt(Vector3 eye, Vector3 point, Vector3 up)
{
	Vector3 viewDir = (point - eye).normalized();

	return lookInDirection(eye, viewDir, up);
}

const Matrix4 MatrixFactory::translate(Vector3 translation)
{
	Matrix4 result = {
		{1, 0, 0, translation.getX()},
		{0, 1, 0, translation.getY()},
		{0, 0, 1, translation.getZ()},
		{0, 0, 0, 1}
	};
	return result;
}
