
#include <Shader.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

using std::ifstream;
using std::ios;

namespace Spatialize {

Shader::Shader(const std::string& vertexShader,
		const std::string& geometryShader, const std::string& fragmentShader) : _vertexShader(vertexShader), _geometryShader(geometryShader), _fragmentShader(fragmentShader), _shaderProgram(0), _isInitialized(false) {
}

Shader::Shader(const std::string& vertexShader,
		const std::string& fragmentShader) : _vertexShader(vertexShader), _geometryShader(""), _fragmentShader(fragmentShader), _shaderProgram(0), _isInitialized(false) {
}

Shader::~Shader() {
	cleanupContext();
}

std::string Shader::loadFile(const std::string &fileName)
{
	ifstream inFile(fileName, ios::in);
	if (!inFile)
	{
		return fileName;
	}

	std::stringstream ss;
	ss << inFile.rdbuf();
	inFile.close();
	return ss.str();
}

void Shader::compileShader(const GLuint &shader, const std::string& code)
{
	const char *source;
	int length;

	source = code.c_str();
	length = code.size();
	glShaderSource(shader, 1, &source, &length);
	glCompileShader(shader);
	if (!checkShaderCompileStatus(shader))
	{
		exit(0);
	}
}

void Shader::init() {
	printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

	std::cout << _vertexShader << std::endl;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	compileShader(vertexShader, loadFile(_vertexShader));

	GLuint geometryShader = 0;
	if (_geometryShader != "")
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		compileShader(geometryShader, loadFile(_geometryShader));
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(fragmentShader, loadFile(_fragmentShader));

	// create program
	_shaderProgram.reset(new GLuint(glCreateProgram()));
	// attach shaders
	glAttachShader(*_shaderProgram, vertexShader);
	if (_geometryShader != "")
	{
		glAttachShader(*_shaderProgram, geometryShader);
	}
	glAttachShader(*_shaderProgram, fragmentShader);
	// link the program and check for errors
	glLinkProgram(*_shaderProgram);
	if (!checkProgramLinkStatus(*_shaderProgram))
	{
		exit(0);
	}

	_isInitialized = true;

	//exit(0);
}

void Shader::useProgram()
{
	if (!_isInitialized)
	{
		init();
	}

	glUseProgram(*_shaderProgram);
}

void Shader::releaseProgram() {
	glUseProgram(0);
}

// helper to check and display for shader compiler errors
bool Shader::checkShaderCompileStatus(GLuint obj) {
	GLint status;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetShaderInfoLog(obj, length, &length, &log[0]);
		std::cerr << &log[0];
		return false;
	}
	return true;
}

void Shader::setParameter(const std::string& name, glm::mat4 matrix) {
	GLint loc = glGetUniformLocation(*_shaderProgram, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setParameter(const std::string& name, glm::vec3 vector) {
	GLint loc = glGetUniformLocation(*_shaderProgram, name.c_str());
	glUniform3fv(loc, 1, glm::value_ptr(vector));
}

void Shader::setParameter(const std::string& name, GLuint id) {
	GLint loc = glGetUniformLocation(*_shaderProgram, name.c_str());
	glUniform1i(loc, id);
}

void Shader::setParameter(const std::string& name, float* values, int numValues) {
	GLint loc = glGetUniformLocation(*_shaderProgram, name.c_str());
	glUniform1fv(loc, numValues, values);
}

void Shader::setParameter(const std::string& name, glm::vec4* values, int numValues) {
	GLint loc = glGetUniformLocation(*_shaderProgram, name.c_str());
	glUniform4fv(loc, numValues, (float*)&values[0]);
}

void Shader::setParameter(const std::string& name, glm::vec3* values, int numValues) {
	GLint loc = glGetUniformLocation(*_shaderProgram, name.c_str());
	glUniform3fv(loc, numValues, (float*)&values[0]);
}

// helper to check and display for shader linker error
bool Shader::checkProgramLinkStatus(GLuint obj) {
	GLint status;
	glGetProgramiv(obj, GL_LINK_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetProgramInfoLog(obj, length, &length, &log[0]);
		std::cerr << &log[0];
		return false;
	}
	return true;
}

void Shader::initContextItem() {
	init();
}

void Shader::cleanupContextItem() {
	glDeleteProgram(*_shaderProgram);
}

}

