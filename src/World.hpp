#ifndef CWORLD_HPP
#define CWORLD_HPP

#include "Sphere.hpp"
#include "Cube.hpp"
#include "Hitbox.hpp"
#include "Maze.hpp"
#include "Melonium.hpp"
#include <iostream>
#include <list>
#include <vector>

const size_t MAZE_WIDTH = 30;
const size_t MAZE_HEIGHT = 30;

class World
{
public:
	Maze *maze;
	Sphere *sphere;
	Hitbox* playerCollider;
	vector<vector<Shape*> > shapeList;

	World();
	~World();
	void draw_world(); // draw all objects in the world
	void reset(); // resets the world
};

#endif
