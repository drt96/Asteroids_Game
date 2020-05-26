/***********************************************************************
* Header File:	SpecialBigRock.h
* Author:	Daniel R. Thomson
* Summary:	Class for large asteroids that can be landed on
************************************************************************/

#include "bigRock.h"

class SpecialBigRock :
	public BigRock
{
public:
	SpecialBigRock();
	SpecialBigRock(const Point& pos, const Velocity &motion);
	~SpecialBigRock();

	//Overidden Virtuals
	virtual void draw()
	{
		drawLargeAsteroid(pos, rotation, true);
		rotation += 2;
	}

	virtual int hit()
	{
		//spawns itself,because it's not supposed to die
		return 4;
	}

	virtual bool kill()
	{
		//This will be used to allow the ship to become an asteroid lander
		return true;
	}

private:
};

