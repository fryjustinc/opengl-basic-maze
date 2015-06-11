#ifndef __MAZEMODEL
#define __MAZEMODEL

#include <vector>
#include "Maze.h"
using namespace std; //makes using vectors easy

class MazeModel
{
public:
	MazeModel()
	{
	}
	
	MazeModel(Maze const & maze)
	{
		size_t h = maze.getHeight();
		size_t w = maze.getWidth();
		float unit = this->getUnitSize();
		
		size_t maxMazeWalls = w*(h+1) + h*(w+1);
		size_t maxElements = maxMazeWalls*2;
		
		for(size_t y=0; y<h+1; y++)
		{
			for(size_t x=0; x<w+1; x++)
			{
				positions.push_back(x*unit);
				positions.push_back(y*unit+unit/8);
				positions.push_back(0);
				positions.push_back(x*unit-unit/8);
				positions.push_back(y*unit);
				positions.push_back(0);
				positions.push_back(x*unit + unit / 8);
				positions.push_back(y*unit);
				positions.push_back(0);
				positions.push_back(x*unit);
				positions.push_back(y*unit - unit / 8);
				positions.push_back(0);
				positions.push_back(x*unit);
				positions.push_back(y*unit + unit / 8);
				positions.push_back(unit);
				positions.push_back(x*unit - unit / 8);
				positions.push_back(y*unit);
				positions.push_back(unit);
				positions.push_back(x*unit + unit / 8);
				positions.push_back(y*unit);
				positions.push_back(unit);
				positions.push_back(x*unit);
				positions.push_back(y*unit - unit / 8);
				positions.push_back(unit);
			}
		}
		
		//bottom lines
		int i = 0;
		for(size_t y=0; y<h; y++)
		{
			for(size_t x=0; x<w; x++)
			{
				bool blocked = maze.bottomBlocked(x, y);
				if(blocked)
				{
					elements.push_back(8*(y*(w+1)+x));
					elements.push_back(8 * (y*(w + 1) + x)+4);
					elements.push_back(8 * (y*(w + 1) + x)+3);
					elements.push_back(8 * (y*(w + 1) + x) + 4);
					elements.push_back(8 * (y*(w + 1) + x) + 3);
					elements.push_back(8 * (y*(w + 1) + x) + 7);
					elements.push_back(8 * (y*(w + 1) + x) + 3);
					elements.push_back(8 * (y*(w + 1) + x) + 7);
					elements.push_back(8*(y*(w+1)+x+1)+3);
					elements.push_back(8 * (y*(w + 1) + x) + 7);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 3);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 7);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 3);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 7);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 0);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 7);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 0);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 4);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 0);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 4);
					elements.push_back(8 * (y*(w + 1) + x));
					elements.push_back(8 * (y*(w + 1) + x + 1) + 4);
					elements.push_back(8 * (y*(w + 1) + x));
					elements.push_back(8 * (y*(w + 1) + x)+4);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 4);
					elements.push_back(8 * (y*(w + 1) + x) + 4);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 7);
					elements.push_back(8 * (y*(w + 1) + x) + 4);
					elements.push_back(8 * (y*(w + 1) + x + 1) + 7);
					elements.push_back(8 * (y*(w + 1) + x) + 7);
				}
			}
		}
		
		//top lines, top row
		for(size_t x=0; x<w; x++)
		{
			bool blocked = maze.topBlocked(x, h-1);
			if(blocked)
			{
				elements.push_back(8 * (h*(w + 1) + x));
				elements.push_back(8 * (h*(w + 1) + x) + 4);
				elements.push_back(8 * (h*(w + 1) + x) + 3);
				elements.push_back(8 * (h*(w + 1) + x) + 4);
				elements.push_back(8 * (h*(w + 1) + x) + 3);
				elements.push_back(8 * (h*(w + 1) + x) + 7);
				elements.push_back(8 * (h*(w + 1) + x) + 3);
				elements.push_back(8 * (h*(w + 1) + x) + 7);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 3);
				elements.push_back(8 * (h*(w + 1) + x) + 7);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 3);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 7);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 3);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 7);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 0);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 7);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 0);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 4);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 0);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 4);
				elements.push_back(8 * (h*(w + 1) + x));
				elements.push_back(8 * (h*(w + 1) + x + 1) + 4);
				elements.push_back(8 * (h*(w + 1) + x));
				elements.push_back(8 * (h*(w + 1) + x) + 4);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 4);
				elements.push_back(8 * (h*(w + 1) + x) + 4);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 7);
				elements.push_back(8 * (h*(w + 1) + x) + 4);
				elements.push_back(8 * (h*(w + 1) + x + 1) + 7);
				elements.push_back(8 * (h*(w + 1) + x) + 7);
			}
		}
		
		//left lines
		for(size_t y=0; y<h; y++)
		{
			for(size_t x=0; x<w; x++)
			{
				bool blocked = maze.leftBlocked(x, y);
				if(blocked)
				{
					elements.push_back(8 * (y*(w + 1) + x)+1);
					elements.push_back(8 * (y*(w + 1) + x) + 5);
					elements.push_back(8 * (y*(w + 1) + x) + 2);
					elements.push_back(8 * (y*(w + 1) + x) + 5);
					elements.push_back(8 * (y*(w + 1) + x) + 2);
					elements.push_back(8 * (y*(w + 1) + x) + 6);
					elements.push_back(8 * (y*(w + 1) + x) + 2);
					elements.push_back(8 * (y*(w + 1) + x) + 6);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 2);
					elements.push_back(8 * (y*(w + 1) + x) + 6);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 2);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 6);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 2);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 6);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 1);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 6);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 1);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 5);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 1);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 5);
					elements.push_back(8 * (y*(w + 1) + x)+1);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 5);
					elements.push_back(8 * (y*(w + 1) + x)+1);
					elements.push_back(8 * (y*(w + 1) + x) + 5);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 5);
					elements.push_back(8 * (y*(w + 1) + x) + 5);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 6);
					elements.push_back(8 * (y*(w + 1) + x) + 5);
					elements.push_back(8 * ((y+1)*(w+1)+x) + 6);
					elements.push_back(8 * (y*(w + 1) + x) + 6);
				}
			}
		}
		
		//right col
		for(size_t y=0; y<h; y++)
		{
			bool blocked = maze.rightBlocked(w-1, y);
			if(blocked)
			{
				elements.push_back(8 * (y*(w + 1) + h) + 1);
				elements.push_back(8 * (y*(w + 1) + h) + 5);
				elements.push_back(8 * (y*(w + 1) + h) + 2);
				elements.push_back(8 * (y*(w + 1) + h) + 5);
				elements.push_back(8 * (y*(w + 1) + h) + 2);
				elements.push_back(8 * (y*(w + 1) + h) + 6);
				elements.push_back(8 * (y*(w + 1) + h) + 2);
				elements.push_back(8 * (y*(w + 1) + h) + 6);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 2);
				elements.push_back(8 * (y*(w + 1) + h) + 6);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 2);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 6);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 2);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 6);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 1);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 6);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 1);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 5);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 1);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 5);
				elements.push_back(8 * (y*(w + 1) + h) + 1);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 5);
				elements.push_back(8 * (y*(w + 1) + h) + 1);
				elements.push_back(8 * (y*(w + 1) + h) + 5);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 5);
				elements.push_back(8 * (y*(w + 1) + h) + 5);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 6);
				elements.push_back(8 * (y*(w + 1) + h) + 5);
				elements.push_back(8 * ((y + 1)*(w + 1) + h) + 6);
				elements.push_back(8 * (y*(w + 1) + h) + 6);
			}
		}
		
		elements.push_back(0);
		elements.push_back(8 * (w));
		elements.push_back((h+1)*(w) * 8);
		elements.push_back(8 * (w));
		elements.push_back((h + 1)*(w)* 8);
		elements.push_back(((h+1)*(w)+w) * 8);



		//This is just to make the GPU buffer the max size it could be
		while(elements.size() < maxElements)
			elements.push_back(0);
	}
	
	size_t getwallsBytes() const
	{
		return walls.size()*sizeof(GLfloat);
	}
	size_t getwallsCount() const
	{
		return walls.size();
	}
	GLfloat const * getwalls() const
	{
		return &walls[0];
	}
	GLfloat const * getPosition() const
	{ return &positions[0]; }
	
	GLuint const * getElements() const
	{ return &elements[0]; }
	
	size_t getElementCount() const
	{ return elements.size(); }
	
	size_t getElementBytes() const
	{ return elements.size()*sizeof(GLuint); }
	
	size_t getVertexCount() const
	{ return positions.size()/3; }
	
	size_t getPositionBytes() const
	{ return positions.size()*sizeof(GLfloat); }
	
	float getUnitSize()
	{ return 1.0f; }
	
private:
	vector<GLfloat> positions;
	vector<GLuint> elements;
	vector<GLfloat> walls;
};

#endif
