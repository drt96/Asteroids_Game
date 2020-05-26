/***********************************************************************
 * Header File: Velocity.h
 * Author:	Daniel R. Thomson
 * Summary:     The speed at which an object moves in a direction,
 *              including inertia
 ************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

#include <ostream>
#include <istream>

class Velocity
{
public:
	Velocity();
	Velocity(float dX, float dY);

	~Velocity() {}

	//getters
	float getDx() const { return dX; }
	float getDy() const { return dY; }

	//setters
	void setDx(float dX);
	void setDy(float dY);

private:
	float dX;
	float dY;
};

// Operator overloading
Velocity & operator + (const Velocity & lhs, const Velocity & rhs);
Velocity & operator += (Velocity & lhs, const Velocity & rhs);
Velocity & operator - (const Velocity & lhs, const Velocity & rhs);
bool operator == (const Velocity & lhs, const Velocity & rhs);
bool operator != (const Velocity & lhs, const Velocity & rhs);
bool operator > (const Velocity & lhs, const Velocity & rhs);
bool operator < (const Velocity & lhs, const Velocity & rhs);
bool operator >= (const Velocity & lhs, const Velocity & rhs);
bool operator <= (const Velocity & lhs, const Velocity & rhs);
std::ostream & operator << (std::ostream & lhs, const Velocity & rhs);
std::istream & operator >> (std::istream & lhs, Velocity & rhs);
Velocity & operator ++(Velocity & rhs);
Velocity & operator ++ (Velocity & lhs, int postfix);

#endif //velocity.h

