#ifndef CHITBOX_H
#define CHITBOX_H

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "Shape.hpp"
#include "Matrix.hpp"

class Hitbox: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceColor[6][3];
	GLfloat Hitbox_face_norm_mc[6][3]; // normal face in mc
	GLfloat Hitbox_face_norm_wc[6][4]; //normal face in wc

public:
	bool isPassable;

	Hitbox();
	Hitbox(bool isPassable);
	void draw_face(int);
	void draw();

	bool isBackface(int);

	GLfloat getFaceShade(int);

};

#endif
