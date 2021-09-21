#ifndef MATRIXFACTORY_H
#define MATRIXFACTORY_H
#include "Matrix4.h"
#include "Vector3.h"

namespace Maths
{
	class MatrixFactory
	{
	public:
		const static Matrix4 perspective(float fovY, float aspect, float zNear, float zFar);
		const static Matrix4 lookInDirection(Vector3 eye, Vector3 viewDir, Vector3 up);
		const static Matrix4 lookAt(Vector3 eye, Vector3 point, Vector3 up);
		const static Matrix4 translate(Vector3 translation);
	};
}

#endif // MATRIXFACTORY_H