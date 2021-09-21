#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H
#include "Light.h"
namespace Lighting
{
	struct PointLight : public Light
	{
		Maths::Vector3 direction;
	};
}
#endif // !DIRECTIONAL_LIGHT_H
