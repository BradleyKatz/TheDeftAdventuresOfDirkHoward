#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "Shape.hpp"
#include "Matrix.hpp"

class Cube: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceColor[6][3];
	GLfloat cube_face_norm_mc[6][3]; // normal face in mc
	GLfloat cube_face_norm_wc[6][4]; //normal face in wc
	GLuint textureIDs[6];

public:
	bool isVisible, isTrap;

	Cube();
	void draw_face(int);
	void draw();
	void setFaceNorm(int);
	bool isBackface(int);
	void setTextureID(GLint index, GLint textureID);

	GLfloat getFaceShade(int);

};

#endif
