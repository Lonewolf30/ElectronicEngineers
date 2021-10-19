#ifndef ELECTRONICENGINEERS_OPENGLSHADERRESOURCE_H
#define ELECTRONICENGINEERS_OPENGLSHADERRESOURCE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <vector>
#include <map>

using namespace std;

class OpenGLShaderResource {
private:
	GLuint programId = -1;
	int referenceCount = 0;
	map<string,int> uniforms;
	vector<string> uniformNames;
	vector<string> uniformType;

public:
	OpenGLShaderResource();
	void Initialise();

	void Finalise();
	void AddReference();
	bool RemoveReference();

	GLuint GetProgramId() const;
	map<string, int> &GetUniforms();
	vector<string> &GetUniformNames();
	vector<string> &GetUniformType();
};


#endif