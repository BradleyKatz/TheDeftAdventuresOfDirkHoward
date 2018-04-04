#include <GL/glew.h>
#include "TitleScreen.hpp"
#include "GameplayScreen.hpp"
#include "CreditsScreen.hpp"
#include "RGBpixmap.h"

using namespace std;

const string TITLESCREEN_MUSIC = "Cosmic Adventure.wav";
const string GAMEPLAY_MUSIC = "Believe In My Heart.wav";
const string CREDITS_MUSIC = "Metroid Ending.wav";
const string GAME_OVER_MUSIC = "You Are Dead.wav";

GLint windowWidth, windowHeight;
World map;
Camera camera;

RGBpixmap meloniumTexture;
RGBpixmap cubeTexture;
RGBpixmap skySphere;
RGBpixmap trap;
RGBpixmap deadscreen;

void drawGrid()
{
	for (float i = -500; i <= 500; i += 5)
	{
		glBegin(GL_LINES);
			glColor3ub(0, 190, 150);
			glVertex3f(-500, -6, i);
			glVertex3f(500, -6, i);
			glVertex3f(i, -6,-500);
			glVertex3f(i, -6, 500);
		glEnd();
	}
}

void drawText(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, void* font, const char* string)
{
	glColor3f(r, g, b);
	glRasterPos3f(x, y, z);

	for (int i = 0; i < (int)strlen(string); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	windowWidth = glutGet(GLUT_SCREEN_WIDTH);
	windowHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("The Deft Adventures of Dirk Howard");

	glewInit();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	cubeTexture.readBMPFile("Textures\\Brick.bmp");
	cubeTexture.setTexture(0);

	meloniumTexture.readBMPFile("Textures\\Melonium.bmp");
	meloniumTexture.setTexture(1);

	skySphere.readBMPFile("Textures\\space.bmp");
	skySphere.setTexture(2);

	trap.readBMPFile("Textures\\trap.bmp");
	trap.setTexture(3);

	deadscreen.readBMPFile("Textures\\dead.bmp");
	deadscreen.setTexture(4);

	// Go to title screen by default
	TitleScreen::initTitleScreen();

	glutSetCursor(GLUT_CURSOR_NONE);
	glutFullScreen();
	glutMainLoop();
}
