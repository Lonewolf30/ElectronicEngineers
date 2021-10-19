#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#include <iostream>
#include <utility>

OpenGLTexture::OpenGLTexture(string textureName) {
	this->textureName = std::move(textureName);
}

void OpenGLTexture::Bind() {
	Bind(0);
}

void OpenGLTexture::Bind(int samplerSlot)
{
	glActiveTexture(GL_TEXTURE0+samplerSlot);
	glBindTexture(GL_TEXTURE_2D, resource.GetTextureId());
}

OpenGLTextureResource OpenGLTexture::GetShaderResource() {

	int x,y,n;
	stbi_set_flip_vertically_on_load(true);
	string textureLocation = "./Resources/textures/" + textureName + ".png";
	stbi_uc* imageData = stbi_load(textureLocation.c_str(), &x, &y, &n, STBI_rgb_alpha);

	if(imageData == nullptr)
		cout << "data not loaded" << endl;

	OpenGLTextureResource textureResource = OpenGLTextureResource();
	textureResource.Initialise();

	glBindTexture(GL_TEXTURE_2D, textureResource.GetTextureId());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA8, x,y,0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	stbi_image_free(imageData);
	return textureResource;
}

void OpenGLTexture::Initialise() {
	resource = GetShaderResource();
}

OpenGLTexture::OpenGLTexture() = default;
