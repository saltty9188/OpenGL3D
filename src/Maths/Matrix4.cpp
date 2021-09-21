#include "Matrix4.h"
#include <iostream>

using namespace Maths;

Matrix4::Matrix4(): _vals{}, _glArray{}
{
	_vals[0][0] = 1;
	_vals[1][1] = 1;
	_vals[2][2] = 1;
	_vals[3][3] = 1;

	int index = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_glArray[index++] = _vals[j][i];
		}
	}
}

Matrix4::Matrix4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3): _vals{}, _glArray{}
{
	_vals[0][0] = row0.getX();
	_vals[0][1] = row0.getY();
	_vals[0][2] = row0.getZ();
	_vals[0][3] = row0.getW();

	_vals[1][0] = row1.getX();
	_vals[1][1] = row1.getY();
	_vals[1][2] = row1.getZ();
	_vals[1][3] = row1.getW();

	_vals[2][0] = row2.getX();
	_vals[2][1] = row2.getY();
	_vals[2][2] = row2.getZ();
	_vals[2][3] = row2.getW();

	_vals[3][0] = row3.getX();
	_vals[3][1] = row3.getY();
	_vals[3][2] = row3.getZ();
	_vals[3][3] = row3.getW();

	int index = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_glArray[index++] = _vals[j][i];
		}
	}
}

Matrix4::Matrix4(std::array<std::array<float, 4>, 4> vals): _vals{vals}, _glArray{}
{
	int index = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_glArray[index++] = _vals[j][i];
		}
	}
}

const Matrix4 Matrix4::operator+(const Matrix4& other) const
{
	std::array<std::array<float, 4>, 4 > newVals{};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			newVals[i][j] = _vals[i][j] + other._vals[i][j];
		}
	}

	return Matrix4(newVals);
}

const Matrix4 Matrix4::operator-(const Matrix4& other) const
{
	std::array<std::array<float, 4>, 4 > newVals{};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			newVals[i][j] = _vals[i][j] - other._vals[i][j];
		}
	}

	return Matrix4(newVals);
}

const Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
	std::array<std::array<float, 4>, 4 > newVals{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				newVals[i][j] += _vals[i][k] * rhs._vals[k][j];
			}
		}
	}

	return Matrix4(newVals);
}

const Vector4 Matrix4::operator*(const Vector4& rhs) const
{
	return Vector4(_vals[0][0] * rhs.getX() + _vals[0][1] * rhs.getY() + _vals[0][2] * rhs.getZ() + _vals[0][3] * rhs.getW(),
				   _vals[1][0] * rhs.getX() + _vals[1][1] * rhs.getY() + _vals[1][2] * rhs.getZ() + _vals[1][3] * rhs.getW(),
				   _vals[2][0] * rhs.getX() + _vals[2][1] * rhs.getY() + _vals[2][2] * rhs.getZ() + _vals[2][3] * rhs.getW(),
				   _vals[3][0] * rhs.getX() + _vals[3][1] * rhs.getY() + _vals[3][2] * rhs.getZ() + _vals[3][3] * rhs.getW());

}

const Matrix4 Matrix4::operator*(const float scalar) const
{
	std::array<std::array<float, 4>, 4 > newVals{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			newVals[i][j] = _vals[i][j] * scalar;
		}
	}

	return Matrix4(newVals);
}

const float Matrix4::get(int row, int column) const
{
	return _vals[row][column];
}

const Matrix4 Matrix4::transpose() const
{
	std::array<std::array<float, 4>, 4 > newVals{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			newVals[i][j] = _vals[j][i];
		}
	}

	return { newVals };
}

const float Matrix4::determinant() const
{
	return ((_vals[0][0] * _vals[1][1] - _vals[0][1] * _vals[1][0]) * (_vals[2][2] * _vals[3][3] - _vals[2][3] * _vals[3][2])
		  - (_vals[0][0] * _vals[1][2] - _vals[0][2] * _vals[1][0]) * (_vals[2][1] * _vals[3][3] - _vals[2][3] * _vals[3][1])
		  + (_vals[0][0] * _vals[1][3] - _vals[0][3] * _vals[1][0]) * (_vals[2][1] * _vals[3][2] - _vals[2][2] * _vals[3][1])
		  + (_vals[0][1] * _vals[1][2] - _vals[0][2] * _vals[1][1]) * (_vals[2][0] * _vals[3][3] - _vals[2][3] * _vals[3][0])
		  - (_vals[0][1] * _vals[1][3] - _vals[0][3] * _vals[1][1]) * (_vals[2][0] * _vals[3][2] - _vals[2][2] * _vals[3][0])
		  + (_vals[0][2] * _vals[1][3] - _vals[0][3] * _vals[1][2]) * (_vals[2][0] * _vals[3][1] - _vals[2][1] * _vals[3][0]));
}

const Matrix4 Matrix4::invert() const
{
	std::array<std::array<float, 4>, 4 > newVals{};
	
	newVals[0][0] = get(1, 2)* get(2, 3)* get(3, 1) - get(1, 3) * get(2, 2) * get(3, 1) + get(1, 3) * get(2, 1) * get(3, 2) - get(1, 1) * get(2, 3) * get(3, 2) - get(1, 2) * get(2, 1) * get(3, 3) + get(1, 1) * get(2, 2) * get(3, 3);
	newVals[0][1] = get(0, 3)* get(2, 2)* get(3, 1) - get(0, 2) * get(2, 3) * get(3, 1) - get(0, 3) * get(2, 1) * get(3, 2) + get(0, 1) * get(2, 3) * get(3, 2) + get(0, 2) * get(2, 1) * get(3, 3) - get(0, 1) * get(2, 2) * get(3, 3);
	newVals[0][2] = get(0, 2)* get(1, 3)* get(3, 1) - get(0, 3) * get(1, 2) * get(3, 1) + get(0, 3) * get(1, 1) * get(3, 2) - get(0, 1) * get(1, 3) * get(3, 2) - get(0, 2) * get(1, 1) * get(3, 3) + get(0, 1) * get(1, 2) * get(3, 3);
	newVals[0][3] = get(0, 3)* get(1, 2)* get(2, 1) - get(0, 2) * get(1, 3) * get(2, 1) - get(0, 3) * get(1, 1) * get(2, 2) + get(0, 1) * get(1, 3) * get(2, 2) + get(0, 2) * get(1, 1) * get(2, 3) - get(0, 1) * get(1, 2) * get(2, 3);
	
	newVals[1][0] = get(1, 3)* get(2, 2)* get(3, 0) - get(1, 2) * get(2, 3) * get(3, 0) - get(1, 3) * get(2, 0) * get(3, 2) + get(1, 0) * get(2, 3) * get(3, 2) + get(1, 2) * get(2, 0) * get(3, 3) - get(1, 0) * get(2, 2) * get(3, 3);
	newVals[1][1] = get(0, 2)* get(2, 3)* get(3, 0) - get(0, 3) * get(2, 2) * get(3, 0) + get(0, 3) * get(2, 0) * get(3, 2) - get(0, 0) * get(2, 3) * get(3, 2) - get(0, 2) * get(2, 0) * get(3, 3) + get(0, 0) * get(2, 2) * get(3, 3);
	newVals[1][2] = get(0, 3)* get(1, 2)* get(3, 0) - get(0, 2) * get(1, 3) * get(3, 0) - get(0, 3) * get(1, 0) * get(3, 2) + get(0, 0) * get(1, 3) * get(3, 2) + get(0, 2) * get(1, 0) * get(3, 3) - get(0, 0) * get(1, 2) * get(3, 3);
	newVals[1][3] = get(0, 2)* get(1, 3)* get(2, 0) - get(0, 3) * get(1, 2) * get(2, 0) + get(0, 3) * get(1, 0) * get(2, 2) - get(0, 0) * get(1, 3) * get(2, 2) - get(0, 2) * get(1, 0) * get(2, 3) + get(0, 0) * get(1, 2) * get(2, 3);
	
	newVals[2][0] = get(1, 1)* get(2, 3)* get(3, 0) - get(1, 3) * get(2, 1) * get(3, 0) + get(1, 3) * get(2, 0) * get(3, 1) - get(1, 0) * get(2, 3) * get(3, 1) - get(1, 1) * get(2, 0) * get(3, 3) + get(1, 0) * get(2, 1) * get(3, 3);
	newVals[2][1] = get(0, 3)* get(2, 1)* get(3, 0) - get(0, 1) * get(2, 3) * get(3, 0) - get(0, 3) * get(2, 0) * get(3, 1) + get(0, 0) * get(2, 3) * get(3, 1) + get(0, 1) * get(2, 0) * get(3, 3) - get(0, 0) * get(2, 1) * get(3, 3);
	newVals[2][2] = get(0, 1)* get(1, 3)* get(3, 0) - get(0, 3) * get(1, 1) * get(3, 0) + get(0, 3) * get(1, 0) * get(3, 1) - get(0, 0) * get(1, 3) * get(3, 1) - get(0, 1) * get(1, 0) * get(3, 3) + get(0, 0) * get(1, 1) * get(3, 3);
	newVals[2][3] = get(0, 3)* get(1, 1)* get(2, 0) - get(0, 1) * get(1, 3) * get(2, 0) - get(0, 3) * get(1, 0) * get(2, 1) + get(0, 0) * get(1, 3) * get(2, 1) + get(0, 1) * get(1, 0) * get(2, 3) - get(0, 0) * get(1, 1) * get(2, 3);
	
	newVals[3][0] = get(1, 2)* get(2, 1)* get(3, 0) - get(1, 1) * get(2, 2) * get(3, 0) - get(1, 2) * get(2, 0) * get(3, 1) + get(1, 0) * get(2, 2) * get(3, 1) + get(1, 1) * get(2, 0) * get(3, 2) - get(1, 0) * get(2, 1) * get(3, 2);
	newVals[3][1] = get(0, 1)* get(2, 2)* get(3, 0) - get(0, 2) * get(2, 1) * get(3, 0) + get(0, 2) * get(2, 0) * get(3, 1) - get(0, 0) * get(2, 2) * get(3, 1) - get(0, 1) * get(2, 0) * get(3, 2) + get(0, 0) * get(2, 1) * get(3, 2);
	newVals[3][2] = get(0, 2)* get(1, 1)* get(3, 0) - get(0, 1) * get(1, 2) * get(3, 0) - get(0, 2) * get(1, 0) * get(3, 1) + get(0, 0) * get(1, 2) * get(3, 1) + get(0, 1) * get(1, 0) * get(3, 2) - get(0, 0) * get(1, 1) * get(3, 2);
	newVals[3][3] = get(0, 1)* get(1, 2)* get(2, 0) - get(0, 2) * get(1, 1) * get(2, 0) + get(0, 2) * get(1, 0) * get(2, 1) - get(0, 0) * get(1, 2) * get(2, 1) - get(0, 1) * get(1, 0) * get(2, 2) + get(0, 0) * get(1, 1) * get(2, 2);

	float det = 1.0f / determinant();
	Matrix4 m{ newVals };

	return m * det;
}

const float* Matrix4::toOpenGL() const
{
	return _glArray;
}
