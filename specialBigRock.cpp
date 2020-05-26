/***********************************************************************
* Implementation File:	SpecialBigRock.cpp
* Author:		Daniel R. Thomson
* Summary:		Class for large asteroids that can be landed on
************************************************************************/

#include "specialBigRock.h"

/*********************************************
* SpecialBigRock :: Default Constructor
*********************************************/
SpecialBigRock::SpecialBigRock(): BigRock()
{
}

/*********************************************
* SpecialBigRock :: Non-Default Constructor
*********************************************/
SpecialBigRock::SpecialBigRock(const Point& pos, const Velocity &motion): BigRock(pos, motion)
{
}

/*********************************************
* SpecialBigRock :: Destructor
*********************************************/
SpecialBigRock::~SpecialBigRock()
{
}
