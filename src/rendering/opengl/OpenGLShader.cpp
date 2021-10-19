#include "OpenGLShader.h"

#include <cctype>
#include <string>
#include <algorithm>

inline std::string trim(const std::string &s)
{
	auto wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
	auto wsback=std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
	return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
}

OpenGLShader::OpenGLShader(const string& fileName) {
	this->fileName = fileName;
	this->shaderResource = OpenGLShaderResource();
}

void OpenGLShader::Initialise() {
	shaderResource.Initialise();

	string vertexCode = ReadShaderFile(this->fileName + "\\vertex.glsl");
	string fragmentCode = ReadShaderFile(this->fileName + "\\fragment.glsl");

	AddVertexShader(vertexCode);
	AddFragmentShader(fragmentCode);

//	AddAllAttributes(vertexShaderText);

	CompileShader();

	AddAllUniforms(vertexCode);
	AddAllUniforms(fragmentCode);
}

OpenGLShader::OpenGLShader() = default;

void OpenGLShader::AddAllAttributes(const string &text) {

}

void OpenGLShader::Bind() {
	glUseProgram(this->shaderResource.GetProgramId());
}

string getShaderType(int type) {
	switch(type){
		case GL_VERTEX_SHADER : return "Vertex";
		case GL_FRAGMENT_SHADER : return "Fragment";
		case GL_GEOMETRY_SHADER : return "Geometric";
	}

	return "";
}

void OpenGLShader::AddProgram(const string &text, int type) {
	int shader = glCreateShader(type);
	if (shader == 0)
		exit(-1);

	const char* code = text.c_str();
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == 0) {
		GLchar log[1024] = {0};
		GLint size = 0;
		glGetShaderInfoLog(shader, 1024, &size, log);
		fprintf(stderr, "Error compiling Shader %s:\n %s ", getShaderType(type).c_str(), log);
		exit(-1);
	}

	glAttachShader(this->shaderResource.GetProgramId(), shader);
}

void OpenGLShader::AddVertexShader(const string &text) {
	AddProgram(text, GL_VERTEX_SHADER);
}

void OpenGLShader::AddFragmentShader(const string &text) {
	AddProgram(text, GL_FRAGMENT_SHADER);
}

void OpenGLShader::AddGeometricShader(const string &text) {
	AddProgram(text, GL_GEOMETRY_SHADER);
}

void OpenGLShader::SetUniformi(const string &uniformName, int value) {
	glUniform1i(this->shaderResource.GetUniforms()[uniformName], value);
}

void OpenGLShader::SetUniformf(const string &uniformName, float value) {
	glUniform1f(this->shaderResource.GetUniforms()[uniformName], value);
}

void OpenGLShader::SetUniform(const string &uniformName, Vector2d value) {
	glUniform2f(this->shaderResource.GetUniforms()[uniformName], static_cast<float>(value.GetX()), static_cast<float>(value.GetY()));
}

void OpenGLShader::SetUniform(const string &uniformName, Vector3d value) {
	glUniform3f(this->shaderResource.GetUniforms()[uniformName], static_cast<float>(value.GetX()), static_cast<float>(value.GetY()), static_cast<float>(value.GetZ()));
}

string OpenGLShader::ReadShaderFile(const string &fileName) {
	string shaderSource;

	fstream shaderFilReader(R"(.\Resources\opengl\shaders\)" + fileName, fstream::in);
	string line;
	while(getline(shaderFilReader, line)){
		shaderSource += line + "\n";
	}

	shaderFilReader.close();
	return shaderSource;
}

void OpenGLShader::CompileShader() {
	glLinkProgram(this->shaderResource.GetProgramId());

	GLint status;
	glGetProgramiv(this->shaderResource.GetProgramId(), GL_LINK_STATUS, &status);
	if (status == 0) {
		GLchar log[1024] = {0};
		GLint size = 0;
		glGetProgramInfoLog(this->shaderResource.GetProgramId(), 1024, &size, log);
		fprintf(stderr, "Error Shader Link_status %d:\n %s ", this->shaderResource.GetProgramId(), log);
		exit(-1);
	}

	glValidateProgram(this->shaderResource.GetProgramId());
	glGetProgramiv(this->shaderResource.GetProgramId(), GL_VALIDATE_STATUS, &status);
	if (status == 0) {
		GLchar log[1024] = {0};
		GLint size = 0;
		glGetProgramInfoLog(this->shaderResource.GetProgramId(), 1024, &size, log);
		fprintf(stderr, "Error Shader Validation %d:\n %s ", this->shaderResource.GetProgramId(), log);
		exit(-1);
	}

}

void OpenGLShader::AddAllUniforms(const string& shaderText) {
	map<string, vector<GLSLStruct>> structs;

	const string UNIFORM_KEYWORD = "uniform";
	const string& shaderCode = shaderText;

	auto uniformStartLocation = shaderCode.find(UNIFORM_KEYWORD);
	while(uniformStartLocation != string::npos)
	{
//		if(!(uniformStartLocation != 0
//			 && (shaderCode[uniformStartLocation - 1] == ' ') || (shaderCode[uniformStartLocation - 1] == ';')
//			 && (shaderCode[uniformStartLocation + UNIFORM_KEYWORD.length()]))) {
//			uniformStartLocation = shaderCode.find(UNIFORM_KEYWORD, uniformStartLocation + UNIFORM_KEYWORD.length());
//			continue;
//		}

		auto begin = uniformStartLocation + UNIFORM_KEYWORD.length()+1;
		auto end = shaderCode.find(';', begin);

		string uniformLine = trim(shaderCode.substr(begin, end - begin));

		auto whiteSpace = uniformLine.find(' ');
		string uniformName = trim(uniformLine.substr(whiteSpace+1, uniformLine.length()-whiteSpace+1));
		string uniformType = trim(uniformLine.substr(0, whiteSpace));

		this->shaderResource.GetUniformNames().push_back(uniformName);
		this->shaderResource.GetUniformType().push_back(uniformType);
		AddUniform(uniformName, uniformType, structs);

		uniformStartLocation = shaderCode.find(UNIFORM_KEYWORD, uniformStartLocation + UNIFORM_KEYWORD.length());
	}
}

void OpenGLShader::AddUniform(const string& uniformName, const string& uniformType, map<string, vector<GLSLStruct>> structs) {
	bool addThis = true;

	if(structs.find(uniformType) != structs.end()) {
		vector<GLSLStruct> structComponents = structs[uniformType];
		addThis = false;
		for (const auto &item : structComponents){
			AddUniform(uniformName + "." + item.name, item.type, structs);
		}
	}

	if(!addThis)
		return;

	GLint uniformLocation = glGetUniformLocation(this->shaderResource.GetProgramId(), uniformName.c_str());
	if(uniformLocation == -1) {
		fprintf(stderr, "Could not Find uniform:%s", uniformName.c_str());
		exit(-1);
	}

	shaderResource.GetUniforms().insert(pair<string,int> (uniformName, uniformLocation));

}

