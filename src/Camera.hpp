
#ifndef CCAMERA_H
#define CCAMERA_H

#include <GL/glut.h>
#include "Point.hpp"
#include "Vector.hpp"
extern GLint windowWidth, windowHeight;
class Camera {
 public:
	Point eye; 			//camera position
	Point ref; 			//look at point
	Vector viewup; 		//view up vector
	GLfloat aspect, nearDist, farDist, viewAngle, W, H;

	//Point eye; 			//camera position
	//Vector u, v, n; 		//view
	Vector viewNorm;   // ref-eye/|ref-eye|
	Camera();
	void set(Point Eye, Point look, Vector up);
	void set(float ex, float ey, float ez, float lx, float ly, float lz, float upx, float upy, float upz);
	void setViewNorm();
	void printCamera(void);
	void setDefaultCamera();

	void rotate(GLfloat angle);
	void translate(GLfloat tx, GLfloat ty, GLfloat tz);
	Vector transLR(GLfloat speed);
	Vector transFB(GLfloat speed);
	void setViewVolume(float viewAngle, float aspect, float Near, float Far);
	void setAspect(float aspect);
	void moveFar(float x);
	void moveNear(float x);

	/* another set of transforms*/
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);
	void slide(double du, double dv, double dn);

	/*  */
	void setProjectionMatrix();

};
#endif


