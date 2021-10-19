#include "UiObject.h"

UiObject::UiObject() = default;

void UiObject::Initialise(string _texture) {
	this->texture = OpenGLTexture(std::move(_texture));
	this->texture.Initialise();
}

void UiObject::Render(OpenGLShader shader, Vector2d displaySize) {
	texture.Bind();
	shader.Bind();
	shader.SetUniform("offset", offset);
	shader.SetUniform("scale", scale);
	shader.SetUniform("windowSize", displaySize);
	shader.SetUniformf("r", 0);

	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(-1,-1);
		glVertex2f(-1,1);
		glVertex2f(1,-1);
		glVertex2f(1,1);
	glEnd();
}

void UiObject::Input(Mouse mouse, Keyboard keyboard) {

}

void UiObject::Update(double delta) {

}
