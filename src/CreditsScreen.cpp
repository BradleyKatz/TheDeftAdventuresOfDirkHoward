#include "CreditsScreen.hpp"
#include "TitleScreen.hpp"

bool CreditsScreen::drawMessage = false;
GLint CreditsScreen::timeSinceLastDraw = 0;

void CreditsScreen::displayCreditsScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (drawMessage)
	{
		drawText((windowWidth / 2) - 800, windowHeight / 0.3, 0, 0.0, 1.0, 0.0, GLUT_BITMAP_9_BY_15, "YOU WIN!");
		drawText((windowWidth / 2) - 2000, windowHeight / 5, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, "PRESS ` TO RETURN TO TITLE");
	}

	drawText((windowWidth / 2) - 3800, windowHeight / 0.34, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, "THIS MELONIUM IS A FAKE LEFT BY THE DARK LORD DULK DEKT!!!");
	drawText((windowWidth / 2) - 1800, windowHeight / 0.36, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, "TO FIND THE REAL MELONIUM");
	drawText((windowWidth / 2) - 2600, windowHeight / 0.38, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, "FAX YOUR ORDER FORM TO 1-(800)-123-DEKT");
	drawText((windowWidth / 2) - 1600, windowHeight / 0.40, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, "ALONG WITH $20.00!!!");
	drawText((windowWidth / 2) - 2200, windowHeight / 0.43, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, "(PARENTAL PERMISSION REQUIRED)");

	drawText((windowWidth / 2) - 1800, windowHeight / 0.60, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, "THIS WAS A GAME WRITTEN BY");
	drawText((windowWidth / 2) - 1100, windowHeight / 0.66, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, "BRADLEY KATZ");
	drawText((windowWidth / 2) - 600, windowHeight / 0.72, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, "AND");
	drawText((windowWidth / 2) - 1400, windowHeight / 0.83, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, "STEPHAN KUWABARA");

	glFlush();
	glutSwapBuffers();
}

void CreditsScreen::animateText()
{
	int currentTime = clock();

	if (currentTime - timeSinceLastDraw > 150)
	{
		drawMessage = !drawMessage;
		timeSinceLastDraw = clock();
	}

	glutPostRedisplay();
}

void CreditsScreen::onKeyboardPress(unsigned char key, GLint x, GLint y)
{
	if (key == '`' || key == '~')
		TitleScreen::initTitleScreen();
}

void CreditsScreen::initCreditsScreen()
{
	AudioManager::stopBackgroundMusic();
	AudioManager::playBackgroundMusic(CREDITS_MUSIC);

	glDisable(GL_NORMALIZE);

	// Reset camera so that restarting the game puts players back at the start of the maze
	camera.setDefaultCamera();

	// Disable GameplayScreen event handlers that aren't used by the credits screen
	glutPassiveMotionFunc(NULL);

	glutDisplayFunc(displayCreditsScreen);
	glutKeyboardFunc(onKeyboardPress);
	glutIdleFunc(animateText);

	glMatrixMode(GL_PROJECTION);
	camera.setProjectionMatrix();

	gluOrtho2D(0.0, (GLdouble) windowWidth, 0.0, (GLdouble) windowHeight);
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set window color to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutPostRedisplay();
}
