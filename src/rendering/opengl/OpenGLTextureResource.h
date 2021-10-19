#ifndef ELECTRONICENGINEERS_OPENGLTEXTURERESOURCE_H
#define ELECTRONICENGINEERS_OPENGLTEXTURERESOURCE_H

#define GLEW_STATIC
#include <GL/glew.h>

class OpenGLTextureResource {
public:
	OpenGLTextureResource();
	void Initialise();
	void AddReference();
	bool RemoveReference();
	GLuint GetTextureId();

private:
	GLuint textureId;
	int referenceCount;
};


#endif
