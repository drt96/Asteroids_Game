/***********************************************************************
 * Header File:	Rock.h
 * Author:	Daniel R. Thomson
 * Summary:	Abstract parent class for rock type classes
 ************************************************************************/

#ifndef ROCK_H
#define ROCK_H

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#include "flyingObject.h"

class  Rock :
	public FlyingObject
{
public:
	Rock();
	Rock(const Point & pos, const Velocity & motion);
	~Rock();

	// VIRTUAL
	// each object has a unique radius
	virtual int getRadius() const { return radius; } 

	//Pure Virtual functions
	virtual void draw() = 0;
	virtual int hit() = 0;

protected:
};

#endif /* rock_h */
