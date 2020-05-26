/***********************************************************************
 * Header File:	SmallRock.h
 * Author:	Daniel R. Thomson
 * Summary:	Class for Small asteroids
 ************************************************************************/

#ifndef SMALLROCK_H
#define SMALLROCK_H

#include "rock.h"

class SmallRock :
	public Rock
{
public:
	SmallRock();
	SmallRock(const Point &pos, const Velocity& motion);
	~SmallRock();

	//overidden methods
	virtual void draw()
	{
		drawSmallAsteroid(pos, rotation);
		rotation += 10;
	}

	virtual int hit()
	{
		return 1;
	}

	virtual int getRadius() const { return SMALL_ROCK_SIZE; }

private:
	static int rotation;
};

#endif /*SMALLROCK_H*/
