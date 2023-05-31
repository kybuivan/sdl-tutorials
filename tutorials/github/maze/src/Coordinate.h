/*
	The Coordinate struct is a data structure that holds coordinate information. 
	It is used by the Rooms, MazeObjects, and classes derived from MazeObjects
*/

#pragma once
struct Coordinate
{
public:
	int xPos;
	int yPos;
	Coordinate(int x, int y);
	Coordinate();
	~Coordinate();

	bool operator ==(const Coordinate &other) const
	{
		if (xPos == other.xPos && yPos == other.yPos)
			return true;
		else
			return false;
	}
	
	bool operator !=(const Coordinate &other) const
	{
		if (xPos != other.xPos || yPos != other.yPos)
			return true;
		else
			return false;
	}
};

