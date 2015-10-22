#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <memory>
#include "MVRCore/GraphicsContext.H"
#include "GL/glew.h"

namespace Spatialize {

class Shader;
typedef std::shared_ptr<class Shader> ShaderRef;

class Shader : public MinVR::ContextObject {
public:
	Shader(const std::string &vertexShader, const std::string &geometryShader, const std::string &fragmentShader);
	Shader(const std::string &vertexShader, const std::string &fragmentShader);
	virtual ~Shader();

	void init();
	void useProgram();
	void releaseProgram();
	void setParameter(const std::string& name, glm::mat4 matrix);
	void setParameter(const std::string& name, glm::vec3 vector);
	void setParameter(const std::string& name, GLuint id);
	void setParameter(const std::string& name, float* values, int numValues);

	void initContextItem();
	bool updateContextItem(bool changed) { return true; }
	void cleanupContextItem();

private:
	std::string loadFile(const std::string &fileName);
	void compileShader(const GLuint &shader, const std::string& code);
	bool checkShaderCompileStatus(GLuint obj);
	bool checkProgramLinkStatus(GLuint obj);

	bool _isInitialized;
	MinVR::ContextSpecificPtr<GLuint> _shaderProgram;
	std::string _vertexShader;
	std::string _geometryShader;
	std::string _fragmentShader;
};

}


#endif /* SHADER_H_ */
