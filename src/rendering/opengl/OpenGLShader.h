#ifndef ELECTRONICENGINEERS_OPENGLSHADER_H
#define ELECTRONICENGINEERS_OPENGLSHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "../../core/vec2/Vector2d.h"
#include "../../core/vec3/Vector3d.h"
#include "../../core/Matrix4f.h"

#include "./OpenGLShaderResource.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

struct GLSLStruct {
	string name;
	string type;
};

class OpenGLShader {
public:
	explicit OpenGLShader(const string& fileName);
	OpenGLShader();

	void Initialise();

	void Bind();

	void SetUniformi(const string& uniformName, int value);
	void SetUniformf(const string& uniformName, float value);
	void SetUniform(const string& uniformName, Vector2d value);
	void SetUniform(const string& uniformName, Vector3d value);

private:
	OpenGLShaderResource shaderResource;
	string fileName;

	static string ReadShaderFile(const string& fileName);

	void AddProgram(const string& text, int type);
	void AddVertexShader(const string& text);
	void AddFragmentShader(const string& text);
	void AddGeometricShader(const string& text);

	void AddAllAttributes(const string& text);
	void CompileShader();
	void AddAllUniforms(const string& shaderText);
	void AddUniform(const string& uniformName, const string& uniformType, map<string, vector<GLSLStruct>> structs);
};

#endif
