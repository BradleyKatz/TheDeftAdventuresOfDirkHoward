/**
 * File: World.hpp
 */

#include "World.hpp"
#include "RGBpixmap.h"

using namespace std;

World::World()
{
	// Set dimensions of maze and generate the layout
	maze = new Maze(MAZE_WIDTH, MAZE_HEIGHT);
	maze->generateRandomMaze();

	// Resize list to prepare it for storing the maze's cubes
	shapeList.resize(maze->getWidth());

	for (unsigned int i = 0; i < shapeList.size(); i++)
		shapeList[i].resize(maze->getHeight());

	maze->generateMazeShapes(shapeList);

	playerCollider = new Hitbox();
	playerCollider->translate(5,5,10);

	sphere = new Sphere(90);
	sphere->rotate_mc(1,0,0,45);
}

World::~World()
{
	delete playerCollider;
	delete sphere;
    delete maze;
}

void World::reset()
{
	playerCollider->reset();
	shapeList.clear();

	delete maze;

	maze = new Maze(MAZE_WIDTH, MAZE_HEIGHT);
	maze->generateRandomMaze();

	// Resize list to prepare it for storing the maze's cubes
	shapeList.resize(maze->getWidth());

	for (unsigned int i = 0; i < shapeList.size(); i++)
		shapeList[i].resize(maze->getHeight());

	maze->generateMazeShapes(shapeList);
}
void World::draw_world()
{
	playerCollider->draw();
	sphere->draw();

	for (size_t y = 0; y < maze->getHeight(); y++)
	{
		for (size_t x = 0; x < maze->getWidth(); x++)
		{
			if (y == maze->endPoint.first && x ==maze->endPoint.second ){
				glColor3f(0.85, 0.85, 0.10);
			} else{
				glColor3f(1,1,1);
			}

			shapeList[y][x]->draw();
		}
	}
}

