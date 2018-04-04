#include <stdio.h>
#include "Camera.hpp"
#include "Matrix.hpp"
#include "World.hpp"
extern World map;

bool DEBUG = false;

Camera::Camera(){
	eye.x = 5.0, eye.y = 5.0, eye.z = 10.0;
	ref.x = 0.0, ref.y = 0.0, ref.z = 0.0;
	viewup.x = 0.0,viewup.y = 1.0, viewup.z = 0.0;
	aspect = 1.0, viewAngle = 60.0, nearDist = 1.0, farDist = 10000.0;
	setViewNorm();
}


void Camera::setDefaultCamera(void) { // make default camera
	eye.x = 5.0, eye.y = 5.0, eye.z = 10.0;
	ref.x = 0.0, ref.y = 0.0, ref.z = 0.0;
	viewup.x = 0.0,viewup.y = 1.0, viewup.z = 0.0;
	aspect = (float)glutGet(GLUT_SCREEN_WIDTH)/glutGet(GLUT_SCREEN_HEIGHT), viewAngle = 60.0, nearDist = 0.5, farDist = 100.0;
	setViewNorm();
}

void Camera::set(Point Eye, Point Look, Vector Up) {
	eye.set(Eye);
	ref.set(Look);
	viewup.set(Up);
	aspect = (float)glutGet(GLUT_SCREEN_WIDTH)/glutGet(GLUT_SCREEN_HEIGHT), viewAngle = 60.0, nearDist = 0.5, farDist = 100.0;
    setProjectionMatrix();
}
void Camera::setViewNorm() {
	GLfloat x, y, z, sr;
	x = ref.x-eye.x;
	y = ref.y-eye.y;
	z = ref.z-eye.z;
	sr = sqrt(x*x + y*y + z*z);
	x = x/sr;
	y = y/sr;
	z = z/sr;
	viewNorm.set(x, y, z);

}

void Camera::rotate(GLfloat speed){ //w.r.p.t WC
	// need to be implemented
	//setViewNorm();
	GLfloat tempx;

	tempx = (float)(eye.x + (ref.x-eye.x)*cos(speed)-sin(speed)*(ref.z-eye.z));
	ref.z = (float)(eye.z + (ref.x-eye.x)*sin(speed)+cos(speed)*(ref.z-eye.z));
	ref.x=tempx;
	setViewNorm();
}
void Camera::translate(GLfloat tx, GLfloat ty, GLfloat tz){ //w.r.p.t WC
	// need to be implemented
	eye.x += tx;
	eye.y += ty;
	eye.z += tz;
	ref.x += tx;
	ref.y += ty;
	ref.z += tz;
	setViewNorm();
}
Vector Camera::transLR(GLfloat speed){ //w.r.p.t WC
	// need to be implemented
	Vector ortho;              // Orthogonal vector for the view vector
	Vector direction;
	GLfloat x, z;
	x = ref.x-eye.x;
	z = ref.z-eye.z;
	ortho.x = -z;
	ortho.z =  x;


	direction.x = (ortho.x * speed);
	direction.y = 0;
	direction.z = (ortho.z * speed);
	setViewNorm();
	return direction;

}
Vector Camera::transFB(GLfloat speed){ //w.r.p.t WC
	// need to be implemented
	Vector direction;
	GLfloat x, z;
	x = ref.x-eye.x;
	z = ref.z-eye.z;
	direction.x = (x * speed);
	direction.y = 0;
	direction.z = (z * speed);
	setViewNorm();
	return (direction);

}
void Camera::moveFar(float x){
	if (x+farDist > nearDist){
		farDist += x;
	}
}
void Camera::moveNear(float x){
	if (x+nearDist < farDist){
		nearDist += x;
	}
}
void Camera::setProjectionMatrix() {
	//set();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, ref.x, ref.y, ref.z, viewup.x,viewup.y,viewup.z);

}
