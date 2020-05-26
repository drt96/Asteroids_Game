/***********************************************************************
* Header File:
*    LANDER : The class that makes the object that the user maneuvers
*	 to fulfil game purpose
* Author:
*    Daniel R. Thomson
* Summary:
*   An Asteroid lander, is a ship that can land on an asteroid with 
*	limited fuel
************************************************************************/

#ifndef LANDER_H
#define LANDER_H

#include "flyingObject.h"

/*********************************************
* Lander
* An Asteroid ship of great and epic ability.
*********************************************/
class Lander :
	public FlyingObject
{
public:
	Lander();
	Lander(const Point & pos);

	~Lander() { }

	//getters
	int getFuel() const
	{
		if (fuel < 0)
		{
			return 0;
		}
		else return fuel;
	}
	bool isLanded() const { return landed; }

	//setters
	void setFuel(int fuel) { this->fuel = fuel; }
	void setLanded(bool landed) { this->landed = landed; }

	//methods
	bool canThrust();	//is able to move

	void applyGravity(float gravity); //natural down motion
	void applyThrustLeft(); //move right
	void applyThrustRight(); //move left
	void applyThrustBottom(); //slow decent

	//Vitual overrides
	virtual int hit()
	{
		return 0;
	}
	
	virtual void draw()
	{
		drawLander(pos);
	}

private:

	bool landed;
	int fuel;
	float gravity;
};

#endif //lander.h
