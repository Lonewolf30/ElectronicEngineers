#include "OpenGLTextureResource.h"


OpenGLTextureResource::OpenGLTextureResource() {
	referenceCount = 1;
	textureId = 0;
}

void OpenGLTextureResource::Initialise()
{
	glGenTextures(1, &textureId);
}

void OpenGLTextureResource::AddReference() {
	referenceCount++;
}

bool OpenGLTextureResource::RemoveReference() {
	referenceCount--;
	return referenceCount == 0;
}

GLuint OpenGLTextureResource::GetTextureId() {
	return textureId;
}

