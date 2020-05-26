/***********************************************************************
 * Header File:	FlyingObject.h
 * Author:	Daniel R. Thomson
 * Summary:	An abstract class that Rock, Bullet and Ship inherit from
 ************************************************************************/

#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include <iostream>

#include "point.h"
#include "velocity.h"

#define _USE_MATH_DEFINES
#include <math.h> 
#include <cmath>

#include "uiDraw.h"

class FlyingObject
{
public:

	FlyingObject();
	FlyingObject(const Point & pos, const Velocity & motion);
	~FlyingObject();

	//Getters
	Point getPoint() const { return pos; }
	Velocity getVelocity() const { return motion; }
	bool isAlive() const { return alive; }

	// each object has a unique radius
	virtual int getRadius() const { return radius; }


	//Setters
	void setPoint(Point pos);
	void setVelocity(Velocity motion);
	void setAlive(bool alive) { this->alive = alive; }

	/*********************************************
	* FlyingObject :: kill
	*   Get rid of the draw instance of that
	*   object and aid in the logic of game.h|.cpp
	*********************************************/
	virtual bool kill()
	{		
		setAlive(false);
		return false;
	}

	// Pure Vitual methods
	virtual void draw() = 0;
	virtual int hit() = 0;

	//Virtual methods

	//get logic from int game::wrapAround
  void advance(const int & wrap)
	{
		switch (wrap)
		{
		case 1:
			pos.setX(-pos.getX());
			break;
		case 2:
			pos.setY(-pos.getY());
			break;
		default:
			break;
		}
		pos.addX(motion.getDx());
		pos.addY(motion.getDy());
	}

protected:

	Point pos;
	Velocity motion;
	bool alive;
	int radius;
};

#endif //FLYINGOBJECT_H
