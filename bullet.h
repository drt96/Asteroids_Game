/***********************************************************************
 * Header File:	Bullet.h
 * Author:	Daniel R. Thomson
 * Summary:	This is a projectile.
 ************************************************************************/

#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"

class Bullet :
	public FlyingObject
{
public:
	Bullet();
	Bullet(const Point & pos);
	~Bullet();

	//getters
	int getLifespan() { return lifespan; }

	//setters
	void setLifespan(int lifespan) { this->lifespan = lifespan; }

	//methods
	void fire(Point pos, const float & angle, const Velocity & speed);

	//virtual Overides functions
	virtual void draw()
	{
		drawDot(pos, lifespan);
	}

	virtual int hit()
	{
		return 0;
	}

	virtual int getRadius() const { return 0; }

private:
	int lifespan;
};

#endif //BULLET_H
