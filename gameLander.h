/*************************************************************
 * File: gameLander.h
 * Author: Daniel Thomson
 *
 * Description: Contains the definition of the Lander game
*				 class.
 *************************************************************/

#ifndef LANDER_GAME_H
#define LANDER_GAME_H

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ground.h"
#include "velocity.h"
#include "lander.h"
#include "fuelcell.h"

#include <iostream>

#define FUEL        500    // initial fuel for the game
#define MIN_SPEED   3.0    // minimal landing speed
#define FALL_HEIGHT 4.0    // greatest height we can fall from
#define BONUS_FUEL  250    // canister of extra gas.

#define GRAVITY_AMOUNT 0.1

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class LanderGame
{
 public:
  /*********************************************
   * Constructor
   * Initializes the game
   *********************************************/
LanderGame(Point tl, Point br) : topLeft(tl), bottomRight(br), ground(Ground(topLeft, bottomRight))
  {
    // Set up the initial conditions of the game
    lander.setFuel(FUEL);
    bonus.draw();
  }
  
  /*********************************************
   * Function: handleInput
   * Description: Takes actions according to whatever
   *  keys the user has pressed.
   *********************************************/
  void handleInput(const Interface & ui);
  
  /*********************************************
   * Function: advance
   * Description: Move everything forward one
   *  step in time.
   *********************************************/
  void advance();
   
  /*********************************************
   * Function: draw
   * Description: draws everything for the game.
   *********************************************/
  void draw(const Interface & ui);

   /*********************************************
   * Function: fuelcellTaken
   * Description: Checks if lander has touched
   *  fuelcell
   *********************************************/
  void fuelcellTaken();
  
   /*********************************************
   * Function: playAgain
   * Description: Checks if user wants to play 
   *  again 
   *********************************************/
  void playAgain() const;

  /*********************************************
   * Function: init
   * Description: if you'd like to reply the game
   *********************************************/
  void init();

 private:
  /*********************************************
   * Function: justLanded
   * Description: Returns true if the lander has
   *  just successfully landed.
   *********************************************/
  bool justLanded() const;
  
  // The coordinates of the screen
  Point topLeft;
  Point bottomRight;
  
  Ground ground;
  Lander lander;
  Fuelcell bonus;
};

#endif /*LANDER_GAME_H*/
