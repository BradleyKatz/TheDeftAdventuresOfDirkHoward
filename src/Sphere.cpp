#include "Sphere.hpp"

Sphere::Sphere() {
	radius = 1.0, slices = 50, stacks = 50;
	textureID = 2;
	quad = gluNewQuadric();

	gluQuadricTexture(quad, GL_TRUE);
	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluQuadricNormals(quad, GLU_SMOOTH);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
Sphere::Sphere(GLfloat rad) {
	radius = rad, slices = rad*50, stacks = rad*50;
	textureID = 2;
	quad = gluNewQuadric();

	gluQuadricTexture(quad, GL_TRUE);
	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluQuadricNormals(quad, GLU_SMOOTH);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
Sphere::~Sphere() {
}

void Sphere::draw() {

	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glPushMatrix();
	this->ctm_multiply();
	gluSphere(quad, radius, slices, stacks);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
}

