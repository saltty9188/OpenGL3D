#include "Scene.h"
#include "Triangle.h"
#include "../Maths/MatrixFactory.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include <iostream>
#include <sstream>
#include <algorithm>


using namespace Drawables;

Drawables::Scene::Scene() : _vertices{}, _vertexNum{ -1 }, _materials{}, _materialNum{ -1 }, textures{}, _textureNum{ -1 }, ambient{}, _background{}, camera{}, _lightNum{ -1 }, shapes{}, lights{}, lineNum{ 0 }
{
}

void Drawables::Scene::read(const std::string& scenePath)
{
    bool cameraRead = false;
    bool backgroundRead = false;
    bool ambientRead = false;
    bool shaderRead = false;
    bool lightNumRead = false;
    bool textureNumRead = false;
    bool materialNumRead = false;
    bool vertexNumRead = false;
    bool beginGroupRead = false;
    int currentTextureIndex = -1;
    int currentMaterialIndex = -1;
    int currentVertexIndex = -1;
    int currentLightIndex = -1;


    std::string line{};
    std::ifstream sceneFile{ scenePath };

    if (sceneFile.is_open())
    {
        while (readNextLine(line, sceneFile, true))
        {
            std::string command{};

            if (line.size() > 0 && line.at(0) == '#')
            {
                std::string word{};
                std::istringstream stream{ line };

                stream >> word;
                command = word.substr(1);

                //std::cout << command << std::endl;

                if (command == "camera")
                {
                    if (beginGroupRead || cameraRead)
                    {
                        std::cout << "ERROR: Camera already read." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        readNextLine(line, sceneFile);
                        std::cout << line << std::endl;
                        Maths::Vector3 pos = readVector3(line);
                        readNextLine(line, sceneFile);
                        Maths::Vector3 dir = readVector3(line);
                        readNextLine(line, sceneFile);
                        Maths::Vector3 up = readVector3(line);
                        readNextLine(line, sceneFile);
                        float heightAngle = readFloat(line);

                        Maths::Vector3 right = up.cross(dir).normalized();
                        up = dir.cross(right).normalized();


                        camera = { pos, dir.normalized(), up, 1.0f, heightAngle };
                        cameraRead = true;
                    }
                }
                else if (command == "background")
                {
                    if (beginGroupRead || backgroundRead)
                    {
                        std::cout << "ERROR: Background already read." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        std::getline(stream, word);
                        _background = readColour(word);    
                        backgroundRead = true;
                    }
                }
                else if (command == "ambient")
                {
                    if (beginGroupRead || ambientRead)
                    {
                        std::cout << "ERROR: Ambient already read." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        std::getline(stream, word);
                        ambient = readColour(word);
                        ambientRead = true;
                    }
                }
                else if (command == "shader")
                {
                    if (beginGroupRead || shaderRead)
                    {
                        std::cout << "ERROR: Shaders already read." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        readNextLine(line, sceneFile);
                        line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
                        line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
                        vert = line;

                        readNextLine(line, sceneFile);
                        line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
                        line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
                        frag = line;

                        shaderRead = true;
                    }
                }
                else if (command == "light_num")
                {
                    if (beginGroupRead || lightNumRead)
                    {
                        std::cout << "ERROR: Lightnum already read." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        std::getline(stream, word);
                        _lightNum = readInt(word);
                        lightNumRead = true;
                    }
                }
                else if (command == "texture_num")
                {
                    if (beginGroupRead || textureNumRead)
                    {
                        std::cout << "ERROR: Texturenum already read." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        std::getline(stream, word);
                        _textureNum = readInt(word);
                        textureNumRead = true;
                    }
                }
                else if (command == "material_num")
                {
                    if (beginGroupRead || materialNumRead)
                    {
                        std::cout << "ERROR: Materialnum already read." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        std::getline(stream, word);
                        _materialNum = readInt(word);
                        materialNumRead = true;
                    }
                }
                else if (command == "vertex_num")
                {
                    if (beginGroupRead || vertexNumRead)
                    {
                        std::cout << "ERROR: Vertexnum already read." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        std::getline(stream, word);
                        _vertexNum = readInt(word);
                        vertexNumRead = true;
                    }
                }
                else if (command == "texture")
                {
                    if (beginGroupRead || !textureNumRead)
                    {
                        std::cout << "ERROR: Cannot read texture now." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        currentTextureIndex++;
                        if (currentTextureIndex >= _textureNum)
                        {
                            std::cout << "ERROR: Cannot have more textures than specified by #texture_num" << std::endl;
                            sceneFile.close();
                            return;
                        }
                        else
                        {
                            std::getline(stream, word);
                            word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
                            word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
                            textures.push_back(std::make_shared<Texture>(word));
                        }
                    }
                }
                else if (command == "material")
                {
                    if (beginGroupRead || !materialNumRead)
                    {
                        std::cout << "ERROR: Cannot read material now." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        currentMaterialIndex++;
                        if (currentMaterialIndex >= _materialNum)
                        {
                            std::cout << "ERROR: Cannot have more materials than specified by #material_num" << std::endl;
                            sceneFile.close();
                            return;
                        }
                        else
                        {
                            Material m{};

                            m.index = currentMaterialIndex;
                            readNextLine(line, sceneFile);
                            m.ambient = readColour(line);
                            readNextLine(line, sceneFile);
                            m.diffuse = readColour(line);
                            readNextLine(line, sceneFile);
                            m.specular = readColour(line);
                            readNextLine(line, sceneFile);
                            m.emissive = readColour(line);
                            readNextLine(line, sceneFile);
                            
                            std::istringstream s2{ line };
                            s2 >> word;
                            m.specularExponent = readFloat(word);
                            s2 >> word;
                            m.transparency = readFloat(word);

                            readNextLine(line, sceneFile);
                            m.refractiveIndex = readFloat(line);
                            readNextLine(line, sceneFile);
                            int textureIndex = readInt(line);
                            if (textures.size())
                            {
                                m.diffuseMap = textures[textureIndex];
                            }
                            readNextLine(line, sceneFile);
                            _materials.push_back(m);
                        }
                    }
                }
                else if (command == "vertex")
                {
                    if (beginGroupRead || !vertexNumRead)
                    {
                        std::cout << "ERROR: Cannot read vertex now." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        currentVertexIndex++;
                        if (currentVertexIndex >= _vertexNum)
                        {
                            std::cout << "ERROR: Cannot have more vertices than specified by #vertex_num" << std::endl;
                            sceneFile.close();
                            return;
                        }
                        else
                        {
                            Vertex v{};
                            readNextLine(line, sceneFile);
                            v.position = readVector3(line);
                            readNextLine(line, sceneFile);
                            v.normal = readVector3(line).normalized();
                            readNextLine(line, sceneFile);
                            v.texCoord = readVector2(line);
                            readNextLine(line, sceneFile);
                            v.colour = readColour(line);
                            _vertices.push_back(v);
                        }
                    }
                }
                else if (command == "light_point")
                {
                    if (beginGroupRead || !lightNumRead)
                    {
                        std::cout << "ERROR: Cannot read light now." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        currentLightIndex++;
                        if (currentLightIndex >= _lightNum)
                        {
                            std::cout << "ERROR: Cannot have more lights than specified by #light_num" << std::endl;
                            sceneFile.close();
                            return;
                        }
                        else
                        {
                            readNextLine(line, sceneFile);
                            Maths::Vector3 colour = readColour(line);
                            readNextLine(line, sceneFile);
                            Maths::Vector3 location = readVector3(line);
                            readNextLine(line, sceneFile);
                            Maths::Vector3 attenuation = readVector3(line);

                            lights.push_back(std::make_shared<Lighting::PointLight>(colour, location, attenuation.getX(), attenuation.getY(), attenuation.getZ()));
                        }
                    }
                }
                else if (command == "light_dir")
                {
                    if (beginGroupRead || !lightNumRead)
                    {
                        std::cout << "ERROR: Cannot read light now." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        currentLightIndex++;
                        if (currentLightIndex >= _lightNum)
                        {
                            std::cout << "ERROR: Cannot have more lights than specified by #light_num" << std::endl;
                            sceneFile.close();
                            return;
                        }
                        else
                        {
                            readNextLine(line, sceneFile);
                            readNextLine(line, sceneFile);
                            readNextLine(line, sceneFile);
                        }
                    }
                }
                else if (command == "light_spot")
                {
                    if (beginGroupRead || !lightNumRead)
                    {
                        std::cout << "ERROR: Cannot read light now." << std::endl;
                        sceneFile.close();
                        return;
                    }
                    else
                    {
                        currentLightIndex++;
                        if (currentLightIndex >= _lightNum)
                        {
                            std::cout << "ERROR: Cannot have more lights than specified by #light_num" << std::endl;
                            sceneFile.close();
                            return;
                        }
                        else
                        {
                            readNextLine(line, sceneFile);
                            readNextLine(line, sceneFile);
                            readNextLine(line, sceneFile);
                        }
                    }
                }
                else
                {
                    beginGroupRead = true;
                    if (command == "geometry")
                    {
                        parseGeometry(command, line, sceneFile);
                    }
                    else
                    {
                        parseShapes(command, line, sceneFile);
                    }
                }
            }
            else if (line.size() == 0)
            {
                // skip this line
            }  
            else
            {
                std::cout << "ERROR: Command " << command << " does not begin with #.     " << lineNum << std::endl;
                sceneFile.close();
                return;
            }

        }

        sceneFile.close();
    }
}

void Drawables::Scene::parseShapes(const std::string& shape, std::string& line, std::ifstream& fileStream)
{
    std::istringstream sstream{ line };
    std::string token;

    // Get to mat index
    sstream >> token;
    sstream >> token;

    Material m{};
    int mIndex = readInt(token);
    if (mIndex >= 0)
    {
        m = _materials[mIndex];
    }

    readNextLine(line, fileStream);
    if (shape == "shape_triangle")
    {
        std::istringstream vstream{ line };
        std::string vert;
        vstream >> vert;
        int v1 = readInt(vert);
        vstream >> vert;
        int v2 = readInt(vert);
        vstream >> vert;
        int v3 = readInt(vert);
        if (v1 == v2 || v1 == v3 || v2 == v3)
        {
            std::cout << "VERTS ARE SAME" << std::endl;
            return;
        }

        //Triangle t{ _vertices[v1], _vertices[v2], _vertices[v3], m };
        std::shared_ptr<Shape> tri = std::make_shared<Triangle>(_vertices[v1], _vertices[v2], _vertices[v3], m);

        shapes.push_back(tri);
    }
    else if (shape == "shape_box")
    {

       // std::cout << line << std::endl;

        Maths::Vector3 tranlate = readVector3(line);
        Maths::Matrix4 translationMatrix = Maths::MatrixFactory::translate(tranlate);

        readNextLine(line, fileStream);

          //std::cout << line << std::endl;

        Maths::Vector3 dimensions = readVector3(line);

        std::shared_ptr<Shape> box = std::make_shared<Box>(dimensions.getX(), dimensions.getY(), dimensions.getZ(), m);
        box->transform = translationMatrix;
        shapes.push_back(box);
    }
    else if (shape == "shape_sphere")
    {
        Maths::Vector3 tranlate = readVector3(line);
        Maths::Matrix4 translationMatrix = Maths::MatrixFactory::translate(tranlate);

        readNextLine(line, fileStream);

        //std::cout << line << std::endl;

        float radius = readFloat(line);

        std::shared_ptr<Shape> sphere = std::make_shared<Sphere>(radius, m);
        sphere->transform = translationMatrix;
        shapes.push_back(sphere);
    }
    else if (shape == "shape_cone")
    {
        Maths::Vector3 tranlate = readVector3(line);
        Maths::Matrix4 translationMatrix = Maths::MatrixFactory::translate(tranlate);

        readNextLine(line, fileStream);
        float radius = readFloat(line);

        readNextLine(line, fileStream);
        float height = readFloat(line);

        std::shared_ptr<Shape> cone = std::make_shared<Cone>(radius, height, m);
        cone->transform = translationMatrix;
        shapes.push_back(cone);
    }
    else if (shape == "shape_cylinder")
    {
        Maths::Vector3 tranlate = readVector3(line);
        Maths::Matrix4 translationMatrix = Maths::MatrixFactory::translate(tranlate);

        readNextLine(line, fileStream);
        float radius = readFloat(line);

        readNextLine(line, fileStream);
        float height = readFloat(line);

        std::shared_ptr<Shape> cylinder = std::make_shared<Cylinder>(radius, height, m);
        cylinder->transform = translationMatrix;
        shapes.push_back(cylinder);
    }

}

void Drawables::Scene::parseGeometry(const std::string& token, std::string& line, std::ifstream& fileStream)
{
    std::istringstream sstream{ line };
    std::string part;

    // Get to texture index
    sstream >> part;
    sstream >> part;
    int texIndex = readInt(part);
    if (token == "geometry")
    {
        readNextLine(line, fileStream);
        line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
        std::string filePath = line;
        std::shared_ptr<Geometry> object = Geometry::loadOBJ(filePath);
        object->setTextureID(texIndex);
        objects.push_back(object);
    }
}

const int Drawables::Scene::readInt(std::string& line) const
{

        try
        {
            int result = std::stoi(line);
            return result;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "Cannot read " << line << " as an int." << std::endl;
            return -1;
        }
}

const float Drawables::Scene::readFloat(std::string& line) const
{

        try
        {
            float result = std::stof(line);
            return result;
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "Cannot read " << line << " as a float." << std::endl;
            return -1;
        }
}

const std::string Drawables::Scene::readString(std::string& line) const
{
    return line;
}

const Maths::Vector2 Drawables::Scene::readVector2(std::string& line) const
{

        float nums[2]{};
        int index = 0;

        std::string number{};
        std::istringstream stream{ line };

        while (stream >> number)
        {
            nums[index++] = readFloat(number);
        }

        if (index != 2)
        {
            std::cout << "ERROR: Not enough arguments." << std::endl;
            return {};
        }
        else
        {
            return { nums[0], nums[1] };
        }

}

const Maths::Vector3 Drawables::Scene::readVector3(std::string& line) const
{

        float nums[3]{};
        int index = 0;

        std::string number{};
        std::istringstream stream{ line };

        while (stream >> number)
        {
            nums[index++] = readFloat(number);
        }

        if (index != 3)
        {
            std::cout << "ERROR: Not enough arguments." << std::endl;
            return {};
        }
        else
        {
            return { nums[0], nums[1], nums[2] };
        }
}

const Maths::Vector3 Drawables::Scene::readColour(std::string& line) const
{
    return readVector3(line);
}

const bool Drawables::Scene::readNextLine(std::string& line, std::ifstream& fileStream, const bool EOFExpected)
{
    if (std::getline(fileStream, line))
    {
        lineNum++;
        return true;
    }
    else
    {
        if(!EOFExpected) std::cout << "ERROR: Unexpected EOF" << std::endl;
        return false;
    }
    
}
