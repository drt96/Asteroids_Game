/***********************************************************************
 * Header File:	FlyingObject.h
 * Author:	Daniel R. Thomson
 * Summary:	An abstract class that Bullet, Rock and Ship inherit from.
 ************************************************************************/

#include "flyingObject.h"

 /*********************************************
  * FLYINGOBJECT :: Constructor
  *********************************************/
FlyingObject::FlyingObject() : radius(0)
{
	setAlive(true);
}

/*********************************************
 * FLYINGOBJECT :: Non Default Constructor
 *********************************************/
FlyingObject::FlyingObject(const Point & pos, const Velocity & motion) : radius(0)
{
	setAlive(true);
	setPoint(pos);
	setVelocity(motion);
}

/*********************************************
 * FLYINGOBJECT :: Destructor
 *********************************************/
FlyingObject :: ~FlyingObject()
{}

/*********************************************
 * FlyingObject :: setPoint
 *	Mutator for objects of type Point
 *********************************************/
void FlyingObject::setPoint(Point pos)
{
	this->pos = pos;
}

/*********************************************
 * FlyingObject :: setVelocity
 *	Mutator for objects of type Velocity
 *********************************************/
void FlyingObject::setVelocity(Velocity motion)
{
	this->motion = motion;
}
