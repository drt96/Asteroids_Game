/***********************************************************************
 * Implementation File:	bigRock.cpp
 * Author:		Daniel R. Thomson
 * Summary:		Class for large asteroids
 ************************************************************************/

#include "bigRock.h"

int BigRock::rotation = BIG_ROCK_SPIN; // static int rotation

/*********************************************
 * BigRock :: Default Constructor
 *********************************************/
BigRock::BigRock() : Rock()
{
	setAlive(true);
}

/*********************************************
 * BigRock :: Non-Default Constructor
 *********************************************/
BigRock::BigRock(const Point& pos, const Velocity& motion) : Rock(pos, motion)
{
	setAlive(true);
}

/*********************************************
 * BigRock :: Destructor
 *********************************************/
BigRock::~BigRock()
{
}
