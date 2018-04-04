#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include <GL/freeglut.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <math.h>

#include "World.hpp"
#include "Camera.hpp"
#include "time.h"
#include "AudioManager.hpp"
#include "Matrix.hpp"

using namespace std;

const char* const YOU_ARE_DEAD = "GAME OVER";
const char* const RESTART_PROMPT = "PRESS ANY KEY TO RESTART";

extern GLint windowWidth, windowHeight;
extern void drawText(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, void* font, const char* string);
extern void drawGrid();

extern World map;
extern Camera camera;

extern const string GAMEPLAY_MUSIC, GAME_OVER_MUSIC;

class GameplayScreen
{
private:
	static bool keystates[256];
	static bool drawPrompt;
	static GLint timeSinceLastDraw;

	// Block instantiation
	GameplayScreen(){}
	static void displayGameplayScreen();
	static void keyboardMove(GLfloat theta);
	static void move();

	static void keyboardAction(unsigned char key, GLint x, GLint y);
	static void keyboardUp(unsigned char key, GLint x, GLint y);
	static void mouseMotion(GLint x, GLint y);
public:
	static void initGameplayScreen();
	static bool checkCollison(Matrix obj1, Matrix obj2, GLfloat scale);
	static bool checkDeath(Matrix obj1);
	static void collisionResolve(Vector direction, Matrix obj1, Matrix obj2,GLfloat scale);
};

#endif
