#ifndef SHADER_H
#define SHADER_H
#include <string>
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "Maths/Vector4.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Shader
{
public:
	Shader(const std::string& vertPath = "", const std::string& fragPath = "");
	~Shader() = default;

	void createShaders();
	void useShader();
	void setUniform(const char* name, const Maths::Matrix4& matrix) const;
	void setUniform(const char* name, const float value) const;
	void setUniform(const char* name, const int value) const;
	void setUniform(const char* name, const Maths::Vector3& vector) const;
	void setUniform(const char* name, const Maths::Vector4& vector) const;

private:
	std::string _vertShader;
	std::string _fragShader;
	unsigned int _id;
	unsigned int _vertID;
	unsigned int _fragID;

	const std::string readFile(const std::string& path) const;
	const unsigned int compileShader(GLenum type, const std::string& shader);
};
#endif // !SHADER_H


