#include "Cube.hpp"
#include "Camera.hpp"

Cube::Cube()
{
	isVisible = true;
	isTrap = false;

	vertex[0][0] = -1;vertex[0][1] = -1;vertex[0][2] = -1;
	vertex[1][0] = -1;vertex[1][1] = 1; vertex[1][2] = -1;
	vertex[2][0] = 1;vertex[2][1] = -1; vertex[2][2] = -1;
	vertex[3][0] = 1;vertex[3][1] = 1;vertex[3][2] = -1;
	vertex[4][0] = -1;vertex[4][1] = -1;vertex[4][2] = 1;
	vertex[5][0] = -1;vertex[5][1] = 1; vertex[5][2] = 1;
	vertex[6][0] = 1;vertex[6][1] = -1;vertex[6][2] = 1;
	vertex[7][0] = 1;vertex[7][1] = 1;vertex[7][2] = 1;

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

	cube_face_norm_mc[0][0] = 0.0,cube_face_norm_mc[0][1] = 0.0,cube_face_norm_mc[0][2] = -1.0,
	cube_face_norm_mc[1][0] = 1.0, cube_face_norm_mc[1][1] = 0.0, cube_face_norm_mc[1][2] = 0.0;
	cube_face_norm_mc[2][0] = 0.0, cube_face_norm_mc[2][1] = 0.0, cube_face_norm_mc[2][2] = 1.0;
	cube_face_norm_mc[3][0] = -1.0, cube_face_norm_mc[3][1] = 0.0, cube_face_norm_mc[3][2] = 0.0;
	cube_face_norm_mc[4][0] = 0.0, cube_face_norm_mc[4][1] = 1.0, cube_face_norm_mc[4][2] = 0.0;
	cube_face_norm_mc[5][0] = 0.0, cube_face_norm_mc[5][1] = -1.0, cube_face_norm_mc[5][2] = 0.0;

}

void Cube::draw_face(int i)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureIDs[i]);

	glBegin(GL_QUADS); // use glBegin(GL_POLYGON);  for filled face
	glTexCoord2f(0, 1);
	glVertex3fv(&vertex[face[i][0]][0]);

	glTexCoord2f(0, 0);
	glVertex3fv(&vertex[face[i][1]][0]);

	glTexCoord2f(1, 0);
	glVertex3fv(&vertex[face[i][2]][0]);

	glTexCoord2f(1, 1);
	glVertex3fv(&vertex[face[i][3]][0]);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Cube::draw()
{
	glPushMatrix();
	this->ctm_multiply();

	glScalef(s, s, s);
	if (!isVisible){
		glNormal3f(cube_face_norm_mc[5][0],cube_face_norm_mc[5][1],cube_face_norm_mc[5][2]);
		this->setTextureID(5,3);

		glDisable(GL_CULL_FACE);
		draw_face(5);
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		return;
	}
	for (int i = 0; i < 6; i++) {
		// add your code for drawing color and shaded face
		glNormal3f(cube_face_norm_mc[i][0],cube_face_norm_mc[i][1],cube_face_norm_mc[i][2]);
		draw_face(i);
	}
	glPopMatrix();
}

void Cube::setTextureID(GLint index, GLint textureID)
{
	textureIDs[index] = textureID;
}

