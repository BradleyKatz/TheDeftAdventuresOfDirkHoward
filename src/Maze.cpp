#include "Maze.hpp"
#include <cmath>

using namespace std;

Maze::Maze(GLint width, GLint height)
{
	startPointSet = false;
	endPointSet = false;

	mazeWidth = width;
	mazeHeight = height;

	maxTraps = sqrt(mazeWidth * mazeHeight);

	maze.resize(mazeHeight);

	for (size_t y = 0; y < mazeHeight; y++)
		maze[y].resize(mazeWidth);

	for (size_t x = 0; x < mazeWidth; x++)
		for (size_t y = 0; y < mazeHeight; y++)
			maze[y][x] = false;
}

void Maze::setStartPoint()
{
	if (!startPointSet)
	{
		for (size_t y = 0; y < mazeHeight; y++)
		{
			for (size_t x = 0; x < mazeWidth; x++)
			{
				if (maze[y][x] == true)
				{
					startPoint.first = y;
					startPoint.second = x;
					startPointSet = true;
					return;
				}
			}
		}
	}
}

void Maze::setEndPoint()
{
	if (!endPointSet)
	{
		for (size_t y = mazeHeight - 1; y > 0; y--)
		{
			for (size_t x = mazeWidth - 1; x > 0; x--)
			{
				if (maze[y][x] == true)
				{
					endPoint.first = y;
					endPoint.second = x;
					endPointSet = true;
					return;
				}
			}
		}
	}
}

void Maze::setTrapPoints()
{
	if (trapPoints.size() < (size_t)maxTraps)
	{
		for (size_t y = 0; y < mazeHeight; y++)
		{
			bool trapSet = false;

			for (size_t x = 0; x < mazeWidth; x++)
			{
				if (maze[y][x] == true && (y != startPoint.first && x != startPoint.second) && (y != endPoint.first && x != endPoint.second))
				{
					switch (rand() % 10)
					{
						case 0:
							// 10% chance to place a trap here
							trapPoints.push_back(pair<size_t, size_t>(y, x));
							trapSet = true;
							break;
					}
				}

				if (trapSet)
				{
					if (trapPoints.size() < (size_t)maxTraps)
						break;
					else
						return;
				}
			}
		}
	}
}

void Maze::generateRandomMaze()
{
	trapPoints.clear();
	drillers.clear();

	// Seed RNG
	srand(time(0));

	drillers.push_back(make_pair(mazeWidth / 2, mazeHeight / 2));

	while (drillers.size() > 0)
	{
		list<pair<GLint, GLint> >::iterator start, end;

		start = drillers.begin();
		end = drillers.end();

		while (start != end)
		{
			bool removeDriller = false;

			switch (rand() % 4)
			{
				case 0:
					(*start).second -= 2;

					if ((*start).second < 0 || maze[(*start).second][(*start).first])
					{
						removeDriller = true;
						break;
					}
					else
					{
						maze[(*start).second + 1][(*start).first] = true;
					}

					break;
				case 1:
					(*start).second += 2;

					if ((size_t)(*start).second >= mazeHeight || maze[(*start).second][(*start).first])
					{
						removeDriller = true;
						break;
					}
					else
					{
						maze[(*start).second - 1][(*start).first] = true;
					}

					break;
				case 2:
					(*start).first -= 2;

					if ((*start).first < 0 || maze[(*start).second][(*start).first])
					{
						removeDriller = true;
						break;
					}
					else
					{
						maze[(*start).second][(*start).first + 1] = true;
					}

					break;
				case 3:
					(*start).first += 2;

					if ((size_t)(*start).first >= mazeWidth || maze[(*start).second][(*start).first])
					{
						removeDriller = true;
						break;
					}
					else
					{
						maze[(*start).second][(*start).first - 1] = true;
					}

					break;
			}

			if (removeDriller)
			{
				start = drillers.erase(start);
			}
			else
			{
				drillers.push_back(make_pair((*start).first, (*start).second));
				drillers.push_back(make_pair((*start).first, (*start).second));
				maze[(*start).second][(*start).first] = true;
				start++;
			}
		}
	}
	// Create perimeter around maze
	for (size_t y = 0; y < mazeHeight; y++)
	{
		maze[y].push_back(false);
	}

	vector<bool> bottomBarrier;
	bottomBarrier.resize(mazeWidth + 1);

	for (size_t i = 0; i < mazeWidth + 1; i++)
		bottomBarrier.push_back(false);

	maze.push_back(bottomBarrier);

	mazeWidth += (size_t) 1;
	mazeHeight += (size_t) 1;

	setStartPoint();
	setEndPoint();
	setTrapPoints();
}

void Maze::printMaze()
{
	for (size_t y = 0; y < mazeHeight; y++)
	{
		for (size_t x = 0; x < mazeWidth; x++)
		{
			if (y == startPoint.first && x == startPoint.second)
				printf("s");
			else if (y == endPoint.first && x == endPoint.second)
				printf("e");
			else if (maze[y][x])
			{
				bool isTrapPoint = false;

				for (unsigned int i = 0; i < trapPoints.size(); i++)
				{
					if (y == trapPoints[i].first && x == trapPoints[i].second)
					{
						isTrapPoint = true;
						break;
					}
				}

				if (isTrapPoint)
					printf("t");
				else
					printf("0");
			}
			else
				printf("1");
		}

		printf("\n");
	}
}

void Maze::generateMazeShapes(vector<vector<Shape*> >& shapeList)
{
	for (size_t y = 0; y < mazeHeight; y++)
	{
		for (size_t x = 0; x < mazeWidth; x++)
		{
			if (y == startPoint.first && x == startPoint.second)
			{
				shapeList[y][x] = new Cube();
				((Cube*)shapeList[y][x])->isVisible = false;
				shapeList[y][x]->translate(0, 100, 0);
			}
			else if (y == endPoint.first && x == endPoint.second)
			{
				shapeList[y][x] = new Melonium(1.0);
				shapeList[y][x]->scale_change(3.0);
				((Melonium*)shapeList[y][x])->setTextureID(1);
				shapeList[y][x]->translate(0, 3, 0);
			}
			else if (maze[y][x])
			{
				bool isTrapPoint = false;

				for (unsigned int i = 0; i < trapPoints.size(); i++)
				{
					if (y == trapPoints[i].first && x == trapPoints[i].second)
					{
						isTrapPoint = true;
						break;
					}
				}

				if (isTrapPoint)
				{
					shapeList[y][x] = new Cube();
					((Cube*)shapeList[y][x])->isVisible = false;
					((Cube*)shapeList[y][x])->isTrap = true;
					shapeList[y][x]->scale_change(3);
					shapeList[y][x]->translate(0, -3, 0);
				}
				else
				{
					shapeList[y][x] = new Cube();
					((Cube*)shapeList[y][x])->isVisible = false;
					shapeList[y][x]->translate(0, 100, 0);
				}
			}
			else
			{
				shapeList[y][x] = new Cube();

				((Cube*)shapeList[y][x])->setTextureID(0, 0);
				((Cube*)shapeList[y][x])->setTextureID(1, 0);
				((Cube*)shapeList[y][x])->setTextureID(2, 0);
				((Cube*)shapeList[y][x])->setTextureID(3, 0);
				((Cube*)shapeList[y][x])->setTextureID(4, 0);
				((Cube*)shapeList[y][x])->setTextureID(5, 0);

				shapeList[y][x]->scale_change(6);
			}

			shapeList[y][x]->translate(x * 14, 1, y * 14);
		}
	}
}

size_t Maze::getWidth()
{
	return mazeWidth;
}

size_t Maze::getHeight()
{
	return mazeHeight;
}
