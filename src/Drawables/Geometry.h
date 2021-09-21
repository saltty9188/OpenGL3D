#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "Triangle.h"
#include "Material.h"
#include <vector>
#include <string>
#include <memory>
#include <map>

namespace Drawables
{
	class Geometry
	{
	public:
		std::vector<Maths::Vector3> verts;
		std::vector<Maths::Vector3> normals;
		std::vector<Maths::Vector2> texCoords;

		std::vector<Triangle> tris;

		std::map<std::string, std::shared_ptr<Material>> materials;

		Geometry();
		~Geometry() = default;

		void init();
		void draw();

		void setTextureID(int textureID);
		const int getTextureID() const;

		static std::shared_ptr<Geometry> loadOBJ(const std::string& filePath);
	private:
		int _texID;
		int _vao;
		static std::map<std::string, std::shared_ptr<Material>> loadMaterials(const std::string& mtlFile);
		static int convertToInt(const std::string& part);
		static float convertToFloat(const std::string& part);
	};
}

#endif // !GEOMETRY_H
