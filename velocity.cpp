/***********************************************************************
 * Implemenation File:	Velocity.cpp
 * Author:		Daniel R. Thomson
 * Summary:             The speed at which an object moves in a
 *                      direction, inlcuding inertia
 ************************************************************************/

#include "velocity.h"

 /********************************************
  * VELOCITY :: DEFAULT CONSTRUCTOR
  ********************************************/
Velocity::Velocity() : dX(0.0), dY(0.0)
{ }

/********************************************
 * VELOCITY :: NON DEFAULT CONSTRUCTOR
 ********************************************/
Velocity::Velocity(float dX, float dY)
{
	setDx(dX);
	setDy(dY);
}

/********************************************
 * VELOCITY :: Set Velocity X coordinate
 ********************************************/
void Velocity::setDx(float dX)
{
	this->dX = dX;
}

/********************************************
 * VELOCITY :: Set Velocity Y coordinate
 ********************************************/
void Velocity::setDy(float dY)
{
	this->dY = dY;
}

/********************************************
* VELOCITY ::  Non member Operator Overides
********************************************/
extern Velocity & operator + (const Velocity & lhs, const Velocity & rhs)
{
	Velocity add;
	add.setDx(lhs.getDx() + rhs.getDx());
	add.setDy(lhs.getDy() + rhs.getDy());
	return add;
}

extern Velocity & operator += (Velocity & lhs, const Velocity & rhs)
{
	lhs.setDx(lhs.getDx() + rhs.getDx());
	lhs.setDy(lhs.getDy() + rhs.getDy());
	return lhs;
}

Velocity & operator - (const Velocity & lhs, const Velocity & rhs)
{
	Velocity sub;
	sub.setDx(lhs.getDx() - rhs.getDx());
	sub.setDy(lhs.getDy() - rhs.getDy());
	return sub;
}

extern bool operator == (const Velocity & lhs, const Velocity & rhs)
{
	if ((lhs.getDx() == rhs.getDx()) && (lhs.getDy() == rhs.getDy()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
extern bool operator != (const Velocity & lhs, const Velocity & rhs)
{
	return !(lhs == rhs);
}

extern bool operator > (const Velocity & lhs, const Velocity & rhs)
{
	if ((lhs.getDx() > rhs.getDx()) || (lhs.getDy() > rhs.getDy()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

extern bool operator < (const Velocity & lhs, const Velocity & rhs)
{
	if ((lhs.getDx() < rhs.getDx()) || (lhs.getDy() < rhs.getDy()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

extern bool operator >= (const Velocity & lhs, const Velocity & rhs)
{
	if ((lhs == rhs) || (lhs > rhs))
	{
		return true;
	}
	else
	{
		return false;
	}
}

extern bool operator <= (const Velocity & lhs, const Velocity & rhs)
{
	if ((lhs == rhs) || (lhs < rhs))
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::ostream & operator << (std::ostream & out, const Velocity & rhs)
{
	out << "(dx="
		<< rhs.getDx()
		<< ", dy="
		<< rhs.getDy();

	return out;
}

std::istream & operator >> (std::istream & in, Velocity & rhs)
{
	in >> rhs;
	return in;
}

extern Velocity & operator ++(Velocity & rhs)
{
	return rhs += Velocity(1, 1);
}

extern Velocity & operator ++ (Velocity & lhs, int postfix)
{
	Velocity old(lhs);
	lhs += Velocity(1, 1);
	return old;
}