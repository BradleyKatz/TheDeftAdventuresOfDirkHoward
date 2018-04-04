#include "Melonium.hpp"

Melonium::Melonium()
{
	size = 1.0;
	textureID = -1;
}

Melonium::Melonium(GLfloat objectSize)
{
	size = objectSize;
	textureID = -1;
}

void Melonium::setSize(GLfloat objectSize)
{
	size = objectSize;
}

void Melonium::setTextureID(GLuint texID)
{
	textureID = texID;
}

void Melonium::draw()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	this->ctm_multiply();
	glScalef(s, s, s);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glutSolidTeapot(size);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
