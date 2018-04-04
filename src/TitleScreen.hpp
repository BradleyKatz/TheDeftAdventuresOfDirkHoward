#ifndef TITLE_SCREEN_HPP
#define TITLE_SCREEN_HPP

#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <string>
#include "AudioManager.hpp"
#include "Camera.hpp"

using namespace std;

const char* const TITLE = "The Deft Adventures of Dirk Howard:";
const char* const SUBTITLE = "Quest For The Shining Melonium";
const char* const PROMPT = "PRESS ANY KEY TO START";

extern GLint windowWidth, windowHeight;
extern void drawText(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, void* font, const char* string);
extern Camera camera;

extern const string TITLESCREEN_MUSIC;

using namespace std;

class TitleScreen
{
protected:
	static bool drawPrompt;
	static GLint timeSinceLastDraw;

	// Disable initialization of TitleScreen Objects
	TitleScreen(){}

	static void displayTitleScreen();
	static void animatePrompt();
	static void onKeyboardPress(unsigned char key, GLint x, GLint y);
	static void onMouseClick(GLint button, GLint buttonState, GLint x, GLint y);

public:
	static void initTitleScreen();
};

#endif
