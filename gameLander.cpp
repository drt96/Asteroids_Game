/*************************************************************
 * File: gameLander.cpp
 * Author: Daniel Thomson
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *************************************************************/

#include "gameLander.h"

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ground.h"
#include "velocity.h" //part of project addition
#include "lander.h"
#include "fuelcell.h" // project addition
#include <iostream>

/******************************************
 * GAME :: JUST LANDED
 * Did we land successfully?
 ******************************************/
bool LanderGame:: justLanded() const
{
  bool landed = false;
  
  Point platformCenter = ground.getPlatformPosition();
  int width = ground.getPlatformWidth();
  
  float xDiff = lander.getPoint().getX() - platformCenter.getX();
  float yDiff = lander.getPoint().getY() - platformCenter.getY();

  float margin = width / 2.0;
   
  if (fabs(xDiff) < margin)
    {
      // between edges
      
      if (yDiff < 4 && yDiff >= 0)
	{
         // right above it
         
	  if (fabs(lander.getVelocity().getDx()) < 3 && fabs(lander.getVelocity().getDy()) < 3)
	    {
            // we're there!
	      landed = true;
	    }
	}
    }
   
  return landed;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void LanderGame:: advance()
{
  fuelcellTaken();
  
  if (lander.isAlive() && !lander.isLanded())
    {
      // advance the lander
      lander.applyGravity(GRAVITY_AMOUNT);
      lander.advance();
   
      // check for crash
      if (!ground.isAboveGround(lander.getPoint()))
	{
	  lander.setAlive(false);
	}
   
      // check for just landed
      if (justLanded())
	{
	  lander.setLanded(true);
	}	
    }
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void LanderGame:: handleInput(const Interface & ui)
{  
  if (lander.isAlive() && !lander.isLanded())
    {
      if (ui.isDown())
	{
	  lander.applyThrustBottom();
	}
      
      if (ui.isLeft())
	{
	  lander.applyThrustLeft();
	}
      
      if (ui.isRight())
	{
	  lander.applyThrustRight();
	}
      
    } else
    {
      if (ui.isSpace())
	{
	  init();
	}
    }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void LanderGame:: draw(const Interface & ui)
{
  lander.draw();
  
  if (!bonus.isTaken())
    {
      bonus.draw();
    }
  
  if (lander.isLanded())
    {
      drawText(Point(), "You have successfully landed!");
      playAgain();
    }
  
  if (!lander.isAlive())
    {
      drawText(Point(), "You have crashed!");
      playAgain();
    }
  
  if (lander.canThrust())
    {
      drawLanderFlames(lander.getPoint(), ui.isDown(), ui.isLeft(), ui.isRight());
    }
  
  if (bonus.isTaken())
    {
      drawText(Point(90, 100), "BONUS FUEL!");
    }
   
  Point fuelLocation;
  fuelLocation.setX(topLeft.getX() + 5);
  fuelLocation.setY(topLeft.getY() - 5);
  
  drawNumber(fuelLocation, lander.getFuel());

  // draw ground
  ground.draw();
}

/*********************************************
 * GAME :: FUELCELLTAKEN
 * Check to see if lander has flown by.
 *********************************************/
void LanderGame:: fuelcellTaken()
{
  if (!bonus.isTaken())
    {
      if ((lander.getPoint().getX() > 85 && lander.getPoint().getX() < 120)
	  && (lander.getPoint().getY() > 90 && lander.getPoint().getY() < 105))
	{
	  bonus.setTaken(true);
	  lander.setFuel((lander.getFuel() + BONUS_FUEL));
	}
    } else
    {
      bonus.setTaken(true);
    }
}

/*********************************************
 * GAME :: PLAYAGAIN
 * Display a prompt to replay.
 *********************************************/
void LanderGame:: playAgain() const
{
  drawText(Point(0,-10), "Press \"Space\" to play again");
}

/*********************************************
 * GAME :: INIT
 * Initialise all game parameters.
 *********************************************/
void LanderGame:: init ()
{
  Point newP;
  newP.addY(150);
  Velocity newV;

  lander.setPoint(newP);
  lander.setVelocity(newV);
  lander.setLanded(false);
  lander.setAlive(true);
  lander.setFuel(500);
  lander.draw();
  
  ground.generateGround();
  
  bonus.setTaken(false);
  bonus.draw();
}
