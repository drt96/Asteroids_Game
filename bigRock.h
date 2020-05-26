/***********************************************************************
 * Header File:	bigRock.h
 * Author:	Daniel R. Thomson
 * Summary:	Class for Big asteroids
 ************************************************************************/

#ifndef BIGROCK_H
#define BIGROCK_H

#include "rock.h"

class BigRock :
	public Rock
{
public:
	BigRock();
	BigRock(const Point& pos, const Velocity &motion);
	~BigRock();

	//overidden method
	virtual void draw()
	{
		drawLargeAsteroid(pos, rotation);
		rotation += 2;
	}

	virtual int hit()
	{
		return 2;
	}

	virtual int getRadius() const { return BIG_ROCK_SIZE; }

protected:
	static int rotation;
};

#endif /*BIGROCK_H*/
