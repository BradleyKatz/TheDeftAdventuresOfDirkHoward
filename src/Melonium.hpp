#ifndef MELONIUM_HPP
#define MELONIUM_HPP

#include <GL/freeglut.h>
#include "Shape.hpp"

class Melonium : public Shape
{
protected:
	GLfloat size;
	GLuint textureID;

public:
	Melonium();
	Melonium(GLfloat objectSize);
	void draw();
	void setSize(GLfloat objectSize);
	void setTextureID(GLuint texID);
};

#endif
