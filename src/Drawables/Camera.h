#ifndef CAMERA_H
#define CAMERA_H
#include "../Maths/Vector3.h"

namespace Drawables
{
	class Camera
	{
	public:
		Camera(const Maths::Vector3& position = { 0, 0, 20 }, const Maths::Vector3& viewDir = { 0, 0, -1 }, const Maths::Vector3& up = { 0, 1, 0 }, const float aspectRation = 1.0f, const float heightAngle = 45.0f);
		~Camera() = default;

		const float getHeightAngle() const;
		const float getAspectRatio() const;
		void setAspectRatio(const float aspectRatio);
		const Maths::Vector3 getPosition() const;
		const Maths::Vector3 getDirection() const;
		const Maths::Vector3 getUp() const;
		const Maths::Vector3 getRight() const;
		void move(const Maths::Vector3& displacement);
		void rotateX(const float angle);
		void rotateY(const float angle);


	private:
		float _heightAngle;
		float _aspectRatio;
		Maths::Vector3 _position;
		Maths::Vector3 _direction;
		Maths::Vector3 _up;
		Maths::Vector3 _right;
	};
}

#endif // !CAMERA_H

