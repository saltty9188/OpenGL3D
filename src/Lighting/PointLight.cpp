#include "PointLight.h"

Lighting::PointLight::PointLight(Maths::Vector3 colour, Maths::Vector3 position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation):
	Light(colour, position), constantAttenuation{constantAttenuation}, linearAttenuation{linearAttenuation}, quadraticAttenuation{quadraticAttenuation}
{
}