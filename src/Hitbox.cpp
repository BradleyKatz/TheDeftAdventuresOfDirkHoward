#include "Hitbox.hpp"
#include "Camera.hpp"

Hitbox::Hitbox()
{
	isPassable = true;

    vertex[0][0] = -1;vertex[0][1] = -6;vertex[0][2] = -1;
    vertex[1][0] = -1;vertex[1][1] = 0; vertex[1][2] = -1;
    vertex[2][0] = 1;vertex[2][1] = -6; vertex[2][2] = -1;
    vertex[3][0] = 1;vertex[3][1] = 0;vertex[3][2] = -1;
    vertex[4][0] = -1;vertex[4][1] = -6;vertex[4][2] = 1;
    vertex[5][0] = -1;vertex[5][1] = 0; vertex[5][2] = 1;
    vertex[6][0] = 1;vertex[6][1] = -6;vertex[6][2] = 1;
    vertex[7][0] = 1;vertex[7][1] = 0;vertex[7][2] = 1;

    face[0][0] = 0;face[0][1] = 1;face[0][2] = 3; face[0][3] = 2;
    face[1][0] = 3;face[1][1] = 7;face[1][2] = 6;face[1][3] = 2;
    face[2][0] = 7;face[2][1] = 5;face[2][2] = 4;face[2][3] = 6;
    face[3][0] = 4;face[3][1] = 5;face[3][2] = 1;face[3][3] = 0;
    face[4][0] = 5;face[4][1] = 7;face[4][2] = 3;face[4][3] = 1;
    face[5][0] = 6;face[5][1] = 4;face[5][2] = 0;face[5][3] = 2;


	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0; faceColor[0][2] = 0.0;
	faceColor[1][0] = 0.0, faceColor[1][1] = 1.0; faceColor[1][2] = 0.0;
	faceColor[2][0] = 0.0, faceColor[2][1] = 0.0; faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0, faceColor[3][1] = 1.0; faceColor[3][2] = 0.0;
	faceColor[4][0] = 1.0, faceColor[4][1] = 0.0; faceColor[4][2] = 1.0;
	faceColor[5][0] = 0.0, faceColor[5][1] = 1.0; faceColor[5][2] = 1.0;

	Hitbox_face_norm_mc[0][0] = 0.0,Hitbox_face_norm_mc[0][1] = 0.0,Hitbox_face_norm_mc[0][2] = -1.0,
	Hitbox_face_norm_mc[1][0] = 1.0, Hitbox_face_norm_mc[1][1] = 0.0, Hitbox_face_norm_mc[1][2] = 0.0;
	Hitbox_face_norm_mc[2][0] = 0.0, Hitbox_face_norm_mc[2][1] = 0.0, Hitbox_face_norm_mc[2][2] = 1.0;
	Hitbox_face_norm_mc[3][0] = -1.0, Hitbox_face_norm_mc[3][1] = 0.0, Hitbox_face_norm_mc[3][2] = 0.0;
	Hitbox_face_norm_mc[4][0] = 0.0, Hitbox_face_norm_mc[4][1] = 1.0, Hitbox_face_norm_mc[4][2] = 0.0;
	Hitbox_face_norm_mc[5][0] = 0.0, Hitbox_face_norm_mc[5][1] = -1.0, Hitbox_face_norm_mc[5][2] = 0.0;

}

Hitbox::Hitbox(bool passable)
{
	isPassable = passable;

	vertex[0][0] = -1;vertex[0][1] = -6;vertex[0][2] = -1;
	vertex[1][0] = -1;vertex[1][1] = 0; vertex[1][2] = -1;
	vertex[2][0] = 1;vertex[2][1] = -6; vertex[2][2] = -1;
	vertex[3][0] = 1;vertex[3][1] = 0;vertex[3][2] = -1;
	vertex[4][0] = -1;vertex[4][1] = -6;vertex[4][2] = 1;
	vertex[5][0] = -1;vertex[5][1] = 0; vertex[5][2] = 1;
	vertex[6][0] = 1;vertex[6][1] = -6;vertex[6][2] = 1;
	vertex[7][0] = 1;vertex[7][1] = 0;vertex[7][2] = 1;

	face[0][0] = 0;face[0][1] = 1;face[0][2] = 3; face[0][3] = 2;
	face[1][0] = 3;face[1][1] = 7;face[1][2] = 6;face[1][3] = 2;
	face[2][0] = 7;face[2][1] = 5;face[2][2] = 4;face[2][3] = 6;
	face[3][0] = 4;face[3][1] = 5;face[3][2] = 1;face[3][3] = 0;
	face[4][0] = 5;face[4][1] = 7;face[4][2] = 3;face[4][3] = 1;
	face[5][0] = 6;face[5][1] = 4;face[5][2] = 0;face[5][3] = 2;


	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0; faceColor[0][2] = 0.0;
	faceColor[1][0] = 0.0, faceColor[1][1] = 1.0; faceColor[1][2] = 0.0;
	faceColor[2][0] = 0.0, faceColor[2][1] = 0.0; faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0, faceColor[3][1] = 1.0; faceColor[3][2] = 0.0;
	faceColor[4][0] = 1.0, faceColor[4][1] = 0.0; faceColor[4][2] = 1.0;
	faceColor[5][0] = 0.0, faceColor[5][1] = 1.0; faceColor[5][2] = 1.0;

	Hitbox_face_norm_mc[0][0] = 0.0,Hitbox_face_norm_mc[0][1] = 0.0,Hitbox_face_norm_mc[0][2] = -1.0,
	Hitbox_face_norm_mc[1][0] = 1.0, Hitbox_face_norm_mc[1][1] = 0.0, Hitbox_face_norm_mc[1][2] = 0.0;
	Hitbox_face_norm_mc[2][0] = 0.0, Hitbox_face_norm_mc[2][1] = 0.0, Hitbox_face_norm_mc[2][2] = 1.0;
	Hitbox_face_norm_mc[3][0] = -1.0, Hitbox_face_norm_mc[3][1] = 0.0, Hitbox_face_norm_mc[3][2] = 0.0;
	Hitbox_face_norm_mc[4][0] = 0.0, Hitbox_face_norm_mc[4][1] = 1.0, Hitbox_face_norm_mc[4][2] = 0.0;
	Hitbox_face_norm_mc[5][0] = 0.0, Hitbox_face_norm_mc[5][1] = -1.0, Hitbox_face_norm_mc[5][2] = 0.0;
}

void Hitbox::draw_face(int i)
{
	glBegin(GL_POLYGON); // use glBegin(GL_POLYGON);  for filled face
		glVertex3fv(&vertex[face[i][0]][0]);
		glVertex3fv(&vertex[face[i][1]][0]);
		glVertex3fv(&vertex[face[i][2]][0]);
		glVertex3fv(&vertex[face[i][3]][0]);
	glEnd();
}

void Hitbox::draw()
{
	return;
}
