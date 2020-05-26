/***********************************************************************
 * Header File:  Ship.h - A class representing the Ship
 * Author:	 Daniel R. Thomson
 * Summary:	 An object that can fly and fire bullets
 ************************************************************************/

#ifndef SHIP_H
#define SHIP_H

#define SHIP_SIZE 10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
const double CAP_SPEED = 6.0;

#include "flyingObject.h"

 /*********************************************
  * Ship
  * A rocket ship of great and epic ability.
  *********************************************/
class Ship : public FlyingObject
{
public:

	Ship();
	Ship(const Point pos);

	~Ship() { }

	//getters
	float getAngle() const { return angle; }
	bool canThrust() const { return thrust; };
	int getLife() const { return life; }

	//setters
	void setThrust(bool thrust) { this->thrust = thrust; }
	void setAngle(float angle) { this->angle = angle; }
	void setLife(int life) { this->life = life; }

	//methods
	void rotateLeft(); // move left
	void rotateRight(); // move right
	void applyThrust(); // forward motion

	//Overridden virtual methods
	virtual void draw()
	{
		drawShip(pos, getAngle(), canThrust());
	}

	virtual int hit()
	{
		return -1;
	}

	virtual int getRadius() const { return SHIP_SIZE; }
	
private:

	int life;
	bool thrust;
	static float thrustAmount;
	static float angle;
};

#endif/*SHIP_H*/
