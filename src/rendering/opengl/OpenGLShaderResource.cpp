#include "OpenGLShaderResource.h"

#include <iostream>

OpenGLShaderResource::OpenGLShaderResource() {
	uniforms = {};
	uniformNames = {};
	uniformType = {};
}

void OpenGLShaderResource::Finalise() {

	const GLuint buffer [] = {programId};

	glDeleteBuffers(1, buffer);
}

void OpenGLShaderResource::AddReference() {
	referenceCount++;
}

bool OpenGLShaderResource::RemoveReference() {
	referenceCount--;

	return referenceCount == 0;
}

GLuint OpenGLShaderResource::GetProgramId() const {
	return programId;
}

map<string, int>& OpenGLShaderResource::GetUniforms()  {
	return uniforms;
}

vector<string> &OpenGLShaderResource::GetUniformNames() {
	return uniformNames;
}

vector<string> &OpenGLShaderResource::GetUniformType() {
	return uniformType;
}

void OpenGLShaderResource::Initialise() {
	programId = glCreateProgram();

	referenceCount = 1;
	if(programId == 0)
	{
		exit(-1);
	}
}






