#ifndef ELECTRONICENGINEERS_OPENGLTEXTURE_H
#define ELECTRONICENGINEERS_OPENGLTEXTURE_H

#include "./OpenGLTextureResource.h"

#include <string>

using namespace std;

class OpenGLTexture {
public:
	OpenGLTexture();
	explicit OpenGLTexture(string textureName);
	void Bind();
	void Bind(int samplerSlot);
	void Initialise();

private:
	OpenGLTextureResource resource;
 	string textureName;

	OpenGLTextureResource GetShaderResource();
};


#endif
