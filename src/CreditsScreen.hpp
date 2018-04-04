#ifndef CREDITS_SCREEN_HPP
#define CREDITS_SCREEN_HPP

#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <string>
#include "AudioManager.hpp"
#include "Camera.hpp"

using namespace std;

extern GLint windowWidth, windowHeight;
extern void drawText(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, void* font, const char* string);
extern Camera camera;

extern const string CREDITS_MUSIC;

extern GLint windowWidth, windowHeight;
extern void drawText(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, void* font, const char* string);

using namespace std;

class CreditsScreen
{
protected:
	static bool drawMessage;
	static GLint timeSinceLastDraw;

	// Disable initialization of TitleScreen Objects
	CreditsScreen(){}

	static void displayCreditsScreen();
	static void animateText();
	static void onKeyboardPress(unsigned char key, GLint x, GLint y);

public:
	static void initCreditsScreen();
};

#endif
