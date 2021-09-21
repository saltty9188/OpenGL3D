#ifndef LIGHT_H
#define LIGHT_H
#include "../Maths/Vector3.h"
namespace Lighting
{
	struct Light
	{
		Maths::Vector3 colour;

		Maths::Vector3 position;

		Light(Maths::Vector3 colour, Maths::Vector3 position);
		virtual ~Light() = default;
	};
}
#endif // !LIGHT_H


