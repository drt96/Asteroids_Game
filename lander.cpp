/***********************************************************************
* Implementation File:
*    LANDER : A class representing the Asteroid lander
* Author:
*    Daniel R. Thomson
* Summary:
*    An object that HAS a velocity() and point() and is maneuvered by the
*    user it moves at one pixel per frame has 500 units of fuel to start
*    out with.
************************************************************************/

#include "lander.h"

/********************************************
* LANDER :: DEFAULT CONSTRUCTOR
********************************************/
Lander::Lander(): FlyingObject(), landed(false)
{}

/********************************************
* LANDER :: NON DEFAULT CONSTRUCTOR
********************************************/
Lander::Lander(const Point & pos) : FlyingObject(pos, motion), landed(false)
{}

/********************************************
* LANDER :: Is the state of Lander able to
*          assert movement?
********************************************/
bool Lander::canThrust()
{
	if (getFuel() > 0 &&
		alive != false &&
		landed != true)
	{
		return true;
	}
	else return false;
}

/********************************************
* LANDER :: natural downward movement
********************************************/
void Lander::applyGravity(float gravity)
{
	//gravitational acceleration done in velocity
	motion.setDy(getVelocity().getDy() - gravity);
}

/********************************************
* LANDER :: move right
********************************************/
void Lander::applyThrustLeft()
{
	if (canThrust())
	{
		motion.setDx(getVelocity().getDx() + .1);
		setVelocity(motion);
		setFuel(getFuel() - 1);
	}
}

/********************************************
* LANDER :: move left
********************************************/
void Lander::applyThrustRight()
{
	if (canThrust())
	{
		motion.setDx(getVelocity().getDx()-.1);
		setVelocity(motion);
		setFuel(getFuel() - 1);
	}
}

/********************************************
* LANDER :: slow decent
********************************************/
void Lander::applyThrustBottom()
{
	setPoint(pos);
	if (canThrust())
	{
		motion.setDy(getVelocity().getDy() + .3);
		setVelocity(motion);
		setFuel(getFuel() - 2);
	}
}
