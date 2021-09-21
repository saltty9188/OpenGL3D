#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Maths/Vector3.h"
#include "Texture.h"
#include <memory>
namespace Drawables
{
	struct Material
	{
		 int index;

		 Maths::Vector3 ambient;

		 Maths::Vector3 diffuse;

		 Maths::Vector3 specular;

		 Maths::Vector3 emissive;

		 float specularExponent;

		 float transparency;

		 float refractiveIndex;

		 std::shared_ptr<Texture> diffuseMap;

		 bool operator==(const Material& other) const;
	};
}
#endif // !MATERIAL_H

