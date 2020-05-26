/***********************************************************************
 * Implementation File:	MediumRock.cpp
 * Author:		Daniel R. Thomson
 * Summary:		Class for Medium asteroids
 ************************************************************************/

#include "mediumRock.h"

int MediumRock::rotation = MEDIUM_ROCK_SPIN; // static int rotation

/*********************************************
 * MediumRock :: Default Constructor
 *********************************************/
MediumRock::MediumRock() : Rock()
{
	setAlive(true);
}

/*********************************************
 * MediumRock :: Non-Default Constructor
 *********************************************/
MediumRock::MediumRock(const Point &pos, const Velocity& motion) : Rock(pos, motion)
{
	setAlive(true);
}

/*********************************************
 * MediumRock :: Destructor
 *********************************************/
MediumRock::~MediumRock()
{}
