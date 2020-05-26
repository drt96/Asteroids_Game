/***********************************************************************
 * Header File:	MediumRock.h
 * Author:	Daniel R. Thomson
 * Summary:	Class for Medium asteroids
 ************************************************************************/

#ifndef MEDIUMROCK_H
#define MEDIUMROCK_H

#include "rock.h"

class MediumRock :
	public Rock
{
public:
	MediumRock();
	MediumRock(const Point &pos, const Velocity &motion);
	~MediumRock();

	//virtual overidden methods
	virtual void draw()
	{
		drawMediumAsteroid(pos, rotation);
		rotation += 5;
	}

	virtual int hit()
	{
		return 3;
	}

	virtual int getRadius() const { return MEDIUM_ROCK_SIZE; }

private:
	static int rotation;
};

#endif /*MEDIUMROCK_H*/
