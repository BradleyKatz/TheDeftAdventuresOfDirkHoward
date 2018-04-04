#include "GameplayScreen.hpp"
#include "TitleScreen.hpp"
#include "CreditsScreen.hpp"
#include <math.h>

bool GameplayScreen::keystates[256];
bool dead = false;

bool GameplayScreen::drawPrompt = false;
GLint GameplayScreen::timeSinceLastDraw = 0;

void GameplayScreen::displayGameplayScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.setProjectionMatrix();
	drawGrid();
	glColor3f(1, 1, 1);
	map.draw_world();

	if (checkDeath(map.playerCollider->getMC()))
	{
		camera.setDefaultCamera();
		gluOrtho2D(0.0, (GLdouble) windowWidth, 0.0, (GLdouble) windowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawText((windowWidth / 2) - 600, windowHeight / 0.3, 0, 1.0, 0.0, 0.0, GLUT_BITMAP_9_BY_15, YOU_ARE_DEAD);

		if (drawPrompt)
		{
			drawText((windowWidth / 2) - 1350, windowHeight / 5, 0, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15, RESTART_PROMPT);
		}
	}

	glFlush();
	glutSwapBuffers();
}
bool GameplayScreen::checkDeath(Matrix obj1){
	if (obj1.mat[1][3] < -100){

		return true;
	}
	return false;
}
bool GameplayScreen::checkCollison(Matrix obj1, Matrix obj2,GLfloat scale){
	//check x
	//	GLfloat x,y,z;


	if (fabs(obj1.mat[0][3]-obj2.mat[0][3]) < fabs(obj1.mat[0][0]*scale+1) ){
		// check y
		if (fabs(obj1.mat[1][3]-obj2.mat[1][3]) < fabs(obj1.mat[1][1]*scale+6)){

			// check z
			if (fabs(obj1.mat[2][3]-obj2.mat[2][3]) <fabs(obj1.mat[2][2]*scale+1)){

				return true;
			}
		}
	}
	return false;
}
void GameplayScreen::collisionResolve(Vector direction, Matrix obj1, Matrix obj2,GLfloat scale){
	GLfloat xDev = fabs((obj1.mat[0][3]-obj2.mat[0][3]))- fabs((obj1.mat[0][0]*scale+1));
	GLfloat zDev = fabs((obj1.mat[2][3]-obj2.mat[2][3]))- fabs((obj1.mat[2][2]*scale+1));
	GLfloat devDist = sqrt(pow(xDev,2)+pow(zDev,2));
	GLfloat xDist =(obj2.mat[0][3]-obj1.mat[0][3]);
	GLfloat zDist =(obj2.mat[2][3]-obj1.mat[2][3]);


	if((direction.x < 0 && direction.z< 0 && xDist<0 && zDist <0 ) ||
			(direction.x < 0 && direction.z> 0 && xDist<0 && zDist >0) ||
			(direction.x > 0 && direction.z< 0 && xDist>0 && zDist <0)  ||
			(direction.x > 0 && direction.z> 0 && xDist>0 && zDist >0)){
		camera.translate(direction.x,direction.y,direction.z);
	}else{

		if (xDev > zDev){
			camera.translate((xDev/devDist)*direction.x,0,(-zDev/devDist)*direction.z);

		} else{
			camera.translate((-xDev/devDist)*direction.x,0,(zDev/devDist)*direction.z);
		}
	}
}

void GameplayScreen::keyboardMove(GLfloat theta)
{
	Vector direction,direction2;
	size_t count, count2;
	bool isCollision;

	if (!dead){

		if ((keystates['w'] && keystates['a']) || (keystates['W'] && keystates['A']))
		{
			direction = camera.transFB(theta/2);
			direction2 = camera.transLR(-theta/2);
			count = 0;
			count2 = 0;
			do{
				if (GameplayScreen::checkCollison(map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor())){
					if(count2 == map.maze->endPoint.first && count == map.maze->endPoint.second){
						map.reset();
						CreditsScreen::initCreditsScreen();
						break;
					}
					else if(((Cube*)map.shapeList[count2][count])->isTrap){
						dead = true;
						AudioManager::playBackgroundMusic(GAME_OVER_MUSIC);
						break;
					}else{
						GameplayScreen::collisionResolve(direction,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
						GameplayScreen::collisionResolve(direction2,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
					}
					isCollision = true;
				}
				count ++;
				if (count == map.maze->getWidth()){
					count = 0;
					count2++;
				}

			}while(isCollision == false && count2 < map.maze->getHeight());

			if(!isCollision){
				camera.translate(direction.x,direction.y,direction.z);
				camera.translate(direction2.x,direction2.y,direction2.z);
			}
			isCollision = false;
			count=0;
			count2=0;
		}
		else if ((keystates['w'] && keystates['d']) || (keystates['W'] && keystates['D']))
		{
			direction = camera.transFB(theta/2);
			direction2 = camera.transLR(theta/2);
			count = 0;
			count2 = 0;
			do{
				if (GameplayScreen::checkCollison(map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor())){
					if(count2 == map.maze->endPoint.first && count == map.maze->endPoint.second){
						map.reset();
						CreditsScreen::initCreditsScreen();
						break;
					}
					else if(((Cube*)map.shapeList[count2][count])->isTrap){
						dead = true;
						AudioManager::playBackgroundMusic(GAME_OVER_MUSIC);
						break;
					}else{
						GameplayScreen::collisionResolve(direction,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
						GameplayScreen::collisionResolve(direction2,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
					}
					isCollision = true;
				}
				count ++;
				if (count == map.maze->getWidth()){
					count = 0;
					count2++;
				}

			}while(isCollision == false && count2 < map.maze->getHeight());

			if(!isCollision){
				camera.translate(direction.x,direction.y,direction.z);
				camera.translate(direction2.x,direction2.y,direction2.z);
			}
			isCollision = false;
			count=0;
			count2=0;
		}
		else if ((keystates['s'] && keystates['a']) || (keystates['S'] && keystates['A']))
		{
			direction2 = camera.transLR(-theta/2);
			direction =	camera.transFB(-theta/2);

			count = 0;
			count2 = 0;
			do{
				if (GameplayScreen::checkCollison(map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor())){
					if(count2 == map.maze->endPoint.first && count == map.maze->endPoint.second){
						map.reset();
						CreditsScreen::initCreditsScreen();
						break;
					}
					else if(((Cube*)map.shapeList[count2][count])->isTrap){
						dead = true;
						AudioManager::playBackgroundMusic(GAME_OVER_MUSIC);
						break;
					}else{
						GameplayScreen::collisionResolve(direction,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
						GameplayScreen::collisionResolve(direction2,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
					}
					isCollision = true;
				}
				count ++;
				if (count == map.maze->getWidth()){
					count = 0;
					count2++;
				}

			}while(isCollision == false && count2 < map.maze->getHeight());

			if(!isCollision){
				camera.translate(direction.x,direction.y,direction.z);
				camera.translate(direction2.x,direction2.y,direction2.z);
			}
			isCollision = false;
			count=0;
			count2=0;
		}
		else if ((keystates['s'] && keystates['d']) || (keystates['S'] && keystates['D']))
		{
			direction = camera.transFB(-theta/2);
			direction2 = camera.transLR(theta/2);
			count = 0;
			count2 = 0;
			do{
				if (GameplayScreen::checkCollison(map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor())){
					if(count2 == map.maze->endPoint.first && count == map.maze->endPoint.second){
						map.reset();
						CreditsScreen::initCreditsScreen();
						break;
					}
					else if(((Cube*)map.shapeList[count2][count])->isTrap){
						dead = true;
						AudioManager::playBackgroundMusic(GAME_OVER_MUSIC);
						break;
					}else{
						GameplayScreen::collisionResolve(direction,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
						GameplayScreen::collisionResolve(direction2,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
					}
					isCollision = true;
				}
				count ++;
				if (count == map.maze->getWidth()){
					count = 0;
					count2++;
				}

			}while(isCollision == false && count2 < map.maze->getHeight());

			if(!isCollision){
				camera.translate(direction.x,direction.y,direction.z);
				camera.translate(direction2.x,direction2.y,direction2.z);
			}
			isCollision = false;
			count=0;
			count2=0;
		}
		if (keystates['a'] || keystates['A'])
		{
			direction = camera.transLR(-theta);
			count = 0;
			count2 = 0;
			do{
				if (GameplayScreen::checkCollison(map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor())){
					if(count2 == map.maze->endPoint.first && count == map.maze->endPoint.second){
						map.reset();
						CreditsScreen::initCreditsScreen();
						break;
					}
					else if(((Cube*)map.shapeList[count2][count])->isTrap){
						dead = true;
						AudioManager::playBackgroundMusic(GAME_OVER_MUSIC);
						break;
					}else{
						GameplayScreen::collisionResolve(direction,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
					}
					isCollision = true;
				}
				count ++;
				if (count == map.maze->getWidth()){
					count = 0;
					count2++;
				}

			}while(isCollision == false && count2 < map.maze->getHeight());

			if(!isCollision){
				camera.translate(direction.x,direction.y,direction.z);
			}
			isCollision = false;
			count=0;
			count2=0;
		}
		else if (keystates['w'] || keystates['W'])
		{
			direction = camera.transFB(theta);
			count = 0;
			count2 = 0;
			do{
				if (GameplayScreen::checkCollison(map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor())){
					if(count2 == map.maze->endPoint.first && count == map.maze->endPoint.second){
						map.reset();
						CreditsScreen::initCreditsScreen();
						break;
					}
					else if(((Cube*)map.shapeList[count2][count])->isTrap){
						dead = true;
						AudioManager::playBackgroundMusic(GAME_OVER_MUSIC);
						break;
					}else{
						GameplayScreen::collisionResolve(direction,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
					}

					isCollision = true;
				}
				count ++;
				if (count == map.maze->getWidth()){
					count = 0;
					count2++;
				}

			}while(isCollision == false && count2 < map.maze->getHeight());

			if(!isCollision){
				camera.translate(direction.x,direction.y,direction.z);
			}
			isCollision = false;
			count=0;
			count2=0;
		}
		else if (keystates['d'] || keystates['D'])
		{
			direction = camera.transLR(theta);
			count = 0;
			count2 = 0;
			do{
				if (GameplayScreen::checkCollison(map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor())){
					if(count2 == map.maze->endPoint.first && count == map.maze->endPoint.second){
						map.reset();
						CreditsScreen::initCreditsScreen();
						break;
					}
					else if(((Cube*)map.shapeList[count2][count])->isTrap){
						dead = true;
						AudioManager::playBackgroundMusic(GAME_OVER_MUSIC);
						break;
					}else{
						GameplayScreen::collisionResolve(direction,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
					}
					isCollision = true;
				}
				count ++;
				if (count == map.maze->getWidth()){
					count = 0;
					count2++;
				}

			}while(isCollision == false && count2 < map.maze->getHeight());

			if(!isCollision){
				camera.translate(direction.x,direction.y,direction.z);
			}
			isCollision = false;
			count=0;
			count2=0;
		}
		else if (keystates['s'] || keystates['S'])
		{
			direction = camera.transFB(-theta);
			count = 0;
			count2 = 0;
			do{
				if (GameplayScreen::checkCollison(map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor())){
					if(count2 == map.maze->endPoint.first && count == map.maze->endPoint.second){
						map.reset();
						CreditsScreen::initCreditsScreen();
						break;
					}
					else if(((Cube*)map.shapeList[count2][count])->isTrap){
						dead = true;
						AudioManager::playBackgroundMusic(GAME_OVER_MUSIC);
						map.sphere->rotate_mc(1,0,0,-45);
						break;
					}else{
						GameplayScreen::collisionResolve(direction,map.shapeList[count2][count]->getMC(),map.playerCollider->getMC(),map.shapeList[count2][count]->getScaleFactor());
					}
					isCollision = true;
				}
				count ++;
				if (count == map.maze->getWidth()){
					count = 0;
					count2++;
				}

			}while(isCollision == false && count2 < map.maze->getHeight());

			if(!isCollision){
				camera.translate(direction.x,direction.y,direction.z);
			}
			isCollision = false;
			count=0;
			count2=0;
		}
	}else{

		camera.translate(0,-theta*20,0);
		glutPassiveMotionFunc(NULL);
		glutMotionFunc(NULL);
		camera.ref.y += theta * 50; // Rotate
	}
	map.playerCollider->setPos(camera.eye.x,camera.eye.y,camera.eye.z);
	map.sphere->setPos(camera.eye.x,camera.eye.y,camera.eye.z);
	glutPostRedisplay();
}

void GameplayScreen::move()
{
	// Character movement

	GLfloat speed = 0.0025;
	GLfloat theta = 1;
	static int oldTime = clock(), newTime;
	newTime = clock();
	theta = (newTime - oldTime) * speed;
	if(GameplayScreen::checkDeath(map.playerCollider->getMC())){

		((Sphere*)map.sphere)->textureID = 4;
		map.sphere->rotate_mc(1, 0, 0, 0.1);

		if (newTime - timeSinceLastDraw > 150)
		{
			drawPrompt = !drawPrompt;
			timeSinceLastDraw = clock();
		}

	}else{
		keyboardMove(theta);
	}
	map.shapeList[map.maze->endPoint.first][map.maze->endPoint.second]->rotate_mc(0,1,0,0.5);
	map.sphere->rotate_mc(0,1,0,0.1);
	oldTime = newTime;

	glutPostRedisplay();
}

void GameplayScreen::keyboardAction(unsigned char key, GLint x, GLint y)
{
	if (checkDeath(map.playerCollider->getMC()))
		TitleScreen::initTitleScreen();

	if (key == 'a' || key == 'A')
	{
		keystates['a'] = true;
		keystates['A'] = true;
	}
	if (key == 'd' || key == 'D')
	{
		keystates['d'] = true;
		keystates['D'] = true;
	}
	if (key == 's' || key == 'S')
	{
		keystates['s'] = true;
		keystates['S'] = true;
	}
	if (key == 'w' || key == 'W')
	{
		keystates['w'] = true;
		keystates['W'] = true;
	}
	if (key == '`' || key == '~')
	{
		TitleScreen::initTitleScreen();
	}
	if (key =='p' || key == 'P')
	{
		AudioManager::playBackgroundMusic(GAME_OVER_MUSIC);
		map.sphere->rotate_mc(1,0,0,-45);
		dead = true;
	}
	if (key =='o' || key == 'O')
	{
		if (!((Cube *)map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second - 1])->isVisible && !((Cube *)map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second - 1])->isTrap)
		{
			camera.eye.x = map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second - 1]->getMC().mat[0][3];
			camera.eye.z = map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second - 1]->getMC().mat[2][3];
		}
		else if (!((Cube *)map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second])->isVisible && !((Cube *)map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second])->isTrap)
		{
			camera.eye.x = map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second]->getMC().mat[0][3];
			camera.eye.z = map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second]->getMC().mat[2][3];
		}
		else if (!((Cube *)map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second + 1])->isVisible && !((Cube *)map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second + 1])->isTrap)
		{
			camera.eye.x = map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second + 1]->getMC().mat[0][3];
			camera.eye.z = map.shapeList[map.maze->endPoint.first - 1][map.maze->endPoint.second + 1]->getMC().mat[2][3];
		}
		else if (!((Cube *)map.shapeList[map.maze->endPoint.first][map.maze->endPoint.second - 1])->isVisible && !((Cube *)map.shapeList[map.maze->endPoint.first][map.maze->endPoint.second - 1])->isTrap)
		{
			camera.eye.x = map.shapeList[map.maze->endPoint.first][map.maze->endPoint.second - 1]->getMC().mat[0][3];
			camera.eye.z = map.shapeList[map.maze->endPoint.first][map.maze->endPoint.second - 1]->getMC().mat[2][3];
		}
		else if (!((Cube *)map.shapeList[map.maze->endPoint.first ][map.maze->endPoint.second + 1])->isVisible && !((Cube *)map.shapeList[map.maze->endPoint.first][map.maze->endPoint.second + 1])->isTrap)
		{
			camera.eye.x = map.shapeList[map.maze->endPoint.first][map.maze->endPoint.second + 1]->getMC().mat[0][3];
			camera.eye.z = map.shapeList[map.maze->endPoint.first][map.maze->endPoint.second + 1]->getMC().mat[2][3];
		}
		else if (!((Cube *)map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second - 1])->isVisible && !((Cube *)map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second - 1])->isTrap)
		{
			camera.eye.x = map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second - 1]->getMC().mat[0][3];
			camera.eye.z = map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second - 1]->getMC().mat[2][3];
		}
		else if (!((Cube *)map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second])->isVisible && !((Cube *)map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second])->isTrap)
		{
			camera.eye.x = map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second]->getMC().mat[0][3];
			camera.eye.z = map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second]->getMC().mat[2][3];
		}
		else if (!((Cube *)map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second + 1])->isVisible && !((Cube *)map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second + 1])->isTrap)
		{
			camera.eye.x = map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second + 1]->getMC().mat[0][3];
			camera.eye.z = map.shapeList[map.maze->endPoint.first + 1][map.maze->endPoint.second + 1]->getMC().mat[2][3];
		}

		camera.ref.x = camera.eye.x+6;
		camera.ref.z = camera.eye.z+6;
	}
}

void GameplayScreen::keyboardUp(unsigned char key, GLint x, GLint y)
{
	if (key == 'a' || key == 'A')
	{
		keystates['a'] = false;
		keystates['A'] = false;
	}
	if (key == 'd' || key == 'D')
	{
		keystates['d'] = false;
		keystates['D'] = false;
	}
	if (key == 's' || key == 'S')
	{
		keystates['s'] = false;
		keystates['S'] = false;
	}
	if (key == 'w' || key == 'W')
	{
		keystates['w'] = false;
		keystates['W'] = false;
	}
}

void GameplayScreen::mouseMotion(GLint x, GLint y)
{
	POINT mousePos;
	int mid_x = windowWidth  >> 1;
	int mid_y = windowHeight >> 1;
	float angle_y  = 0.0f;
	float angle_z  = 0.0f;

	GetCursorPos(&mousePos);	// Get the 2D mouse cursor (x,y) position

	if( (mousePos.x == mid_x) && (mousePos.y == mid_y) ) return;

	SetCursorPos(mid_x, mid_y);	// Set the mouse cursor in the center of the window

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angle_y = (float)( (mid_x - mousePos.x) ) / 1000;
	angle_z = (float)( (mid_y - mousePos.y) ) / 1000;

	// The higher the value is the faster the camera looks around.
	camera.ref.y += angle_z * 2;

	// limit the rotation around the x-axis
	if((camera.ref.y - camera.eye.y) > 8)  camera.ref.y = camera.eye.y + 8;
	if((camera.ref.y - camera.eye.y) <-8)  camera.ref.y = camera.eye.y - 8;

	camera.rotate(-angle_y); // Rotate
	glutPostRedisplay();
}

void GameplayScreen::initGameplayScreen()
{
	AudioManager::stopBackgroundMusic();
	AudioManager::playBackgroundMusic(GAMEPLAY_MUSIC);

	// Disable TitleScreen event handlers that aren't used by the gameplay screen
	glutMouseFunc(NULL);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_NORMALIZE);

	camera.eye.x = map.shapeList[map.maze->startPoint.first][map.maze->startPoint.second]->getMC().mat[0][3];
	camera.eye.y = 2.5;
	camera.eye.z = map.shapeList[map.maze->startPoint.first][map.maze->startPoint.second]->getMC().mat[2][3];
	camera.ref.x = camera.eye.x + 6;
	camera.ref.y = camera.eye.y;
	camera.ref.z = camera.eye.z + 6;

	camera.setProjectionMatrix();
	map.playerCollider->setPos(camera.eye.x,camera.eye.y,camera.eye.z);
	map.sphere->setPos(camera.eye.x,camera.eye.y,camera.eye.z);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	dead = false;
	((Sphere*)map.sphere)->textureID = 2;

	glutPassiveMotionFunc(mouseMotion);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboardAction);
	glutKeyboardUpFunc(keyboardUp);
	glutDisplayFunc(displayGameplayScreen);
	glutIdleFunc(move);
}
