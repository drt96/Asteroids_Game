/***********************************************************************
 * Implementation File:  Ship.h - A class representing the Ship
 * Author:		 Daniel R. Thomson
 * Summary:	         An object that can fly and fire bullets
 ************************************************************************/

#include "ship.h"

float Ship::angle = ROTATE_AMOUNT; // static float angle
float Ship::thrustAmount = THRUST_AMOUNT; //static float thrustAmount;

/********************************************
 * Ship :: DEFAULT CONSTRUCTOR
 ********************************************/
Ship::Ship() : FlyingObject(), life(5)
{}

/********************************************
 * Ship :: NON DEFAULT CONSTRUCTOR
 ********************************************/
Ship::Ship(const Point pos) : FlyingObject(pos, motion), life(5)
{}

/********************************************
 * Ship :: ROTATE LEFT
 ********************************************/
void Ship::rotateLeft()
{
	setAngle(getAngle() + ROTATE_AMOUNT);
}

/********************************************
 * Ship :: ROTATE RIGHT
 ********************************************/
void Ship::rotateRight()
{
	setAngle(getAngle() - ROTATE_AMOUNT);
}

/********************************************
 * Ship :: APPLY THRUST
 * Move in any given direction
 ********************************************/
void Ship::applyThrust()
{
	setPoint(getPoint());

	float angInRad = (M_PI / 180.0 * getAngle());

	float dx = thrustAmount * (-sin(angInRad));
	float dy = thrustAmount * (cos(angInRad));

	dx += getVelocity().getDx();
	dy += getVelocity().getDy();

	//Ensuring that we don't travel at warp speed
	if (dx > CAP_SPEED)	{		dx = CAP_SPEED;	}
	if (dy > CAP_SPEED)	{		dy = CAP_SPEED;	}
	if (dx < -CAP_SPEED)	{		dx = -CAP_SPEED;	}
	if (dy < -CAP_SPEED)	{		dy = -CAP_SPEED;	}

	setVelocity(Velocity(dx, dy));
}