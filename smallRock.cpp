/***********************************************************************
 * Implementation File:	SmallRock.cpp
 * Author:		Daniel R. Thomson
 * Summary:		Class for Small asteroids
 ************************************************************************/

#include "smallRock.h"

int SmallRock::rotation = SMALL_ROCK_SPIN; //static int rotation

/*********************************************
 * SmallRock :: Default Constructor
 *********************************************/
SmallRock::SmallRock() : Rock()
{
	setAlive(true);
}

/*********************************************
 * SmallRock :: Non-Default Constructor
 *********************************************/
SmallRock::SmallRock(const Point & pos, const Velocity& motion) : Rock(pos, motion)
{
	setAlive(true);
}

/*********************************************
 * SmallRock :: Destructor
 *********************************************/
SmallRock::~SmallRock()
{}
