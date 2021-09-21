#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H
#include "Light.h"
namespace Lighting
{
	struct SpotLight : public Light
	{
		Maths::Vector3 direction;

		float constantAttenuation;

		float linearAttenuation;

		float quadraticAttenuation;

		float cutOffAngle;

		float dropOffRate;
	};
}
#endif // !SPOT_LIGHT_H
