#include "Geometry.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace Drawables;

Drawables::Geometry::Geometry():
	_texID{ 0 }, _vao{ 0 }, verts{}, normals{}, texCoords{}, tris{}, materials{}
{
}

void Drawables::Geometry::init()
{
	for (auto& tri : tris) 
	{
		tri.init();
	}
}

void Drawables::Geometry::draw()
{
	for (auto& tri : tris)
	{
		tri.draw();
	}
}

void Drawables::Geometry::setTextureID(int textureID)
{
	_texID = textureID;
}

const int Drawables::Geometry::getTextureID() const
{
	return _texID;
}

std::shared_ptr<Drawables::Geometry> Drawables::Geometry::loadOBJ(const std::string& filePath)
{
	std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>();
	std::string line{};
	std::ifstream objFile{ filePath };

	std::shared_ptr<Material> activeMat = std::make_shared<Material>();
	while (std::getline(objFile, line))
	{
		std::istringstream sstream{ line };
		std::string part{};

		std::string type{};

		sstream >> type;
		if (type == "mtllib") 
		{
			sstream >> part;
			geometry->materials = loadMaterials(part);
		}
		else if (type == "v") 
		{
			sstream >> part;
			float x = convertToFloat(part);
			sstream >> part;
			float y = convertToFloat(part);
			sstream >> part;
			float z = convertToFloat(part);
			geometry->verts.push_back({x, y, z});
		}
		else if (type == "vt") 
		{
			sstream >> part;
			float x = convertToFloat(part);
			sstream >> part;
			float y = convertToFloat(part);
			//Flip V co-ordinates
			y = 1.0f - y;
			geometry->texCoords.push_back({ x, y});
		}
		else if (type == "vn") 
		{
			sstream >> part;
			float x = convertToFloat(part);
			sstream >> part;
			float y = convertToFloat(part);
			sstream >> part;
			float z = convertToFloat(part);
			geometry->normals.push_back({ x, y, z });
		}
		else if (type == "f") 
		{
			// new face;
			std::string v1Parts{};
			sstream >> v1Parts;
			std::string v2Parts{};
			sstream >> v2Parts;
			std::string v3Parts{};
			sstream >> v3Parts;

			std::istringstream getVert1{ v1Parts };
			std::getline(getVert1, part, '/');
			int vIndex = convertToInt(part);
			std::getline(getVert1, part, '/');
			int tIndex = convertToInt(part);;
			std::getline(getVert1, part, '/');
			int nIndex = convertToInt(part);

			//obj files start at 1 so offset by 1
			vIndex--;
			tIndex--;
			nIndex--;
			
			Vertex v1{};
			v1.position = geometry->verts.at(vIndex);
			v1.texCoord = geometry->texCoords.at(tIndex);
			v1.normal = geometry->normals.at(nIndex);
			v1.colour = activeMat->diffuse;

			std::istringstream getVert2{ v2Parts };
			std::getline(getVert2, part, '/');
			vIndex = convertToInt(part);
			std::getline(getVert2, part, '/');
			tIndex = convertToInt(part);;
			std::getline(getVert2, part, '/');
			nIndex = convertToInt(part);

			//obj files start at 1 so offset by 1
			vIndex--;
			tIndex--;
			nIndex--;

			Vertex v2{};
			v2.position = geometry->verts.at(vIndex);
			v2.texCoord = geometry->texCoords.at(tIndex);
			v2.normal = geometry->normals.at(nIndex);
			v2.colour = activeMat->diffuse;

			std::istringstream getVert3{ v3Parts };
			std::getline(getVert3, part, '/');
			vIndex = convertToInt(part);
			std::getline(getVert3, part, '/');
			tIndex = convertToInt(part);;
			std::getline(getVert3, part, '/');
			nIndex = convertToInt(part);

			//obj files start at 1 so offset by 1
			vIndex--;
			tIndex--;
			nIndex--;

			Vertex v3{};
			v3.position = geometry->verts.at(vIndex);
			v3.texCoord = geometry->texCoords.at(tIndex);
			v3.normal = geometry->normals.at(nIndex);
			v3.colour = activeMat->diffuse;

			geometry->tris.push_back({v1, v2, v3, *activeMat});
		}
		else if (type == "usemtl") 
		{
			sstream >> part;
			activeMat = geometry->materials[part];
		}
	}

	objFile.close();
	return geometry;
}

std::map<std::string, std::shared_ptr<Material>> Drawables::Geometry::loadMaterials(const std::string& mtlFile)
{
	std::map<std::string, std::shared_ptr<Material>> loadedMaterials{};
	std::string line{};
	std::ifstream file{ mtlFile};

	std::shared_ptr<Material> activeMat = std::make_shared<Material>();
	while (std::getline(file, line))
	{
		std::istringstream sstream{ line };
		std::string part{};

		std::string type{};

		sstream >> type;
		if (type == "newmtl") 
		{
			sstream >> part;
			activeMat = std::make_shared<Material>();
			loadedMaterials.insert({part, activeMat});
		}
		else if (type == "Kd") 
		{
			sstream >> part;
			float x = convertToFloat(part);
			sstream >> part;
			float y = convertToFloat(part);
			sstream >> part;
			float z = convertToFloat(part);

			activeMat->diffuse = {x, y, z};
		}
		else if (type == "Ka")
		{
			sstream >> part;
			float x = convertToFloat(part);
			sstream >> part;
			float y = convertToFloat(part);
			sstream >> part;
			float z = convertToFloat(part);

			activeMat->ambient = { x, y, z };
		}
		else if (type == "Ks") 
		{
			sstream >> part;
			float x = convertToFloat(part);
			sstream >> part;
			float y = convertToFloat(part);
			sstream >> part;
			float z = convertToFloat(part);

			activeMat->specular = { x, y, z };
		}
		else if (type == "Ni") 
		{
			sstream >> part;
			float val = convertToFloat(part);
			activeMat->refractiveIndex = val;
		}
		else if (type == "Ns") 
		{
			sstream >> part;
			float val = convertToFloat(part);
			activeMat->specularExponent = val;
		}
		else if (type == "Tr") 
		{
			sstream >> part;
			float val = convertToFloat(part);
			activeMat->transparency = val;
		}
	}
	file.close();
	return loadedMaterials;
}

int Drawables::Geometry::convertToInt(const std::string& part)
{
	try
	{
		int result = std::stoi(part);
		return result;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Cannot read " << part << " as an int." << std::endl;
		return -1;
	}
}

float Drawables::Geometry::convertToFloat(const std::string& part)
{
	try
	{
		float result = std::stof(part);
		return result;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Cannot read " << part << " as a float." << std::endl;
		return -1;
	}
}
