#include "Material.h"

bool Drawables::Material::operator==(const Material& other) const
{
	return index == other.index && diffuse == other.diffuse && specular == other.specular 
		&& emissive == other.emissive && specularExponent == other.specularExponent && transparency == other.transparency 
		&& refractiveIndex == other.refractiveIndex && diffuseMap == other.diffuseMap;
}
