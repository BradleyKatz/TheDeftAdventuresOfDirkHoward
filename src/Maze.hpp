#ifndef MAZE_HPP
#define MAZE_HPP

#include <time.h>
#include <vector>
#include <list>
#include "Shape.hpp"
#include "Cube.hpp"
#include "Hitbox.hpp"
#include "Melonium.hpp"
#include <stdio.h>

using namespace std;

class Maze
{
protected:
	bool startPointSet, endPointSet;

	size_t mazeWidth, mazeHeight;
	vector<vector<bool> > maze;
	list<pair<GLint, GLint> > drillers;

	void setStartPoint();
	void setEndPoint();
	void setTrapPoints();

public:
	pair<size_t, size_t> startPoint;
	pair<size_t, size_t> endPoint;
	vector<pair<size_t, size_t> > trapPoints;
	size_t maxTraps;
	Maze(GLint width, GLint height);

	void generateRandomMaze();
	void printMaze();
	void generateMazeShapes(vector<vector<Shape*> >& shapeList);
	size_t getWidth();
	size_t getHeight();
};

#endif
