#ifndef SCENE_H
#define SCENE_H
#include "Vertex.h"
#include "Material.h"
#include "Shape.h"
#include "Geometry.h"
#include "Camera.h"
#include "../Lighting/PointLight.h"
#include <Vector>
#include <string>
#include <fstream>
#include <memory>

namespace Drawables
{
	class Scene
	{
	public:
        Scene();
        ~Scene() = default;

        std::vector<std::shared_ptr<Shape>> shapes;
        std::vector<std::shared_ptr<Lighting::Light>> lights;

        void read(const std::string& scenePath);

        std::string vert;
        std::string frag;
        Maths::Vector3 ambient;
        Camera camera;
        
        std::vector<std::shared_ptr<Texture>> textures;
        std::vector<std::shared_ptr<Geometry>> objects;
       

	private:
         std::vector<Vertex> _vertices;
         int _vertexNum;
         std::vector<Material> _materials;
         int _materialNum;
         
         int _textureNum;
         
         Maths::Vector3 _background;
         int _lightNum;

         int lineNum;

         void parseShapes(const std::string& shape, std::string& line, std::ifstream& fileStream);
         void parseGeometry(const std::string& token, std::string& line, std::ifstream& fileStream);
         const int readInt(std::string& line) const;
         const float readFloat(std::string& line) const;
         const std::string readString(std::string& line) const;
         const Maths::Vector2 readVector2(std::string& line) const;
         const Maths::Vector3 readVector3(std::string& line) const;
         const Maths::Vector3 readColour(std::string& line) const;
         const bool readNextLine(std::string& line, std::ifstream& fileStream, const bool EOFExpected = false);
	};
}
#endif // !SCENE_H


