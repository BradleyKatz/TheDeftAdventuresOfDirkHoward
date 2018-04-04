#include "TitleScreen.hpp"
#include "GameplayScreen.hpp"

bool TitleScreen::drawPrompt = false;
GLint TitleScreen::timeSinceLastDraw = 0;

void TitleScreen::displayTitleScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawText((windowWidth / 2) - 1600, windowHeight / 0.3, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, TITLE);
	drawText((windowWidth / 2) - 1350, windowHeight / 0.32, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, SUBTITLE);

	if (TitleScreen::drawPrompt)
	{
		drawText((windowWidth / 2) - 1350, windowHeight / 5, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, PROMPT);
	}

	glFlush();
	glutSwapBuffers();
}

void TitleScreen::animatePrompt()
{
	int currentTime = clock();

	if (currentTime - TitleScreen::timeSinceLastDraw > 150)
	{
		TitleScreen::drawPrompt = !TitleScreen::drawPrompt;
		TitleScreen::timeSinceLastDraw = clock();
	}

	glutPostRedisplay();
}

void TitleScreen::onKeyboardPress(unsigned char key, GLint x, GLint y)
{
	if (key == '`' || key == '~')
		glutLeaveMainLoop();
	else
		GameplayScreen::initGameplayScreen();
}

void TitleScreen::onMouseClick(GLint key, GLint buttonState, GLint x, GLint y)
{
	if (buttonState == GLUT_DOWN)
		GameplayScreen::initGameplayScreen();
}

void TitleScreen::initTitleScreen()
{
	AudioManager::stopBackgroundMusic();
	AudioManager::playBackgroundMusic(TITLESCREEN_MUSIC);

	glDisable(GL_NORMALIZE);

	// Reset camera so that restarting the game puts players back at the start of the maze
	camera.setDefaultCamera();

	// Disable GameplayScreen event handlers that aren't used by the title screen
	glutPassiveMotionFunc(NULL);
	glutKeyboardUpFunc(NULL);

	glutDisplayFunc(displayTitleScreen);
	glutKeyboardFunc(onKeyboardPress);
	glutMouseFunc(onMouseClick);
	glutIdleFunc(animatePrompt);

	glMatrixMode(GL_PROJECTION);

	camera.setProjectionMatrix();

	gluOrtho2D(0.0, (GLdouble) windowWidth, 0.0, (GLdouble) windowHeight);
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set window color to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutPostRedisplay();
}
