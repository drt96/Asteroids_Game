/***********************************************************************
 * Implementation File:	Rock.cpp
 * Author:		Daniel R. Thomson
 * Summary:		Abstract parent class for Rock type classes
 ************************************************************************/

#include "rock.h"

 /*********************************************
  * Rock :: Default Constructor
  *********************************************/
Rock::Rock() : FlyingObject()
{}

/*********************************************
 * Rock :: Non-Default Constructor
 *********************************************/
Rock::Rock(const Point & pos, const Velocity & motion) : FlyingObject(pos, motion)
{}

/*********************************************
 * Rock :: Destructor
 *********************************************/
Rock ::~Rock()
{}
