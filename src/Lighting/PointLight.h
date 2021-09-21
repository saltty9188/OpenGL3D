#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "Light.h"
namespace Lighting
{
	struct PointLight : public Light
	{
		float constantAttenuation;

		float linearAttenuation;

		float quadraticAttenuation;

		PointLight(Maths::Vector3 colour, Maths::Vector3 position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation);
		~PointLight() = default;
	};
}
#endif // !POINT_LIGHT_H
