/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "flyingObject.h"
#include "point.h"
#include "velocity.h"
#include "ship.h"
#include "rock.h"
#include "bullet.h"
#include "uiDraw.h"
#include "uiInteract.h"

#include "bigRock.h"
#include "mediumRock.h"
#include "smallRock.h"
#include "specialBigRock.h"

#include "ground.h"
#include "lander.h"
#include "fuelcell.h"

#include <iostream>

#define FUEL        500    // initial fuel for the game
#define MIN_SPEED   3.0    // minimal landing speed
#define FALL_HEIGHT 4.0    // greatest height we can fall from
#define BONUS_FUEL  250    // canister of extra gas.

#define GRAVITY_AMOUNT 0.1 //Gravity of the asteroids
#define SHIP_DAMAGE -1 //when collisions occur with asteroids and your ship

using namespace std;

class Game
{
public:

	/*********************************************
	 * Constructor
	 * Initializes the game
	 *********************************************/
	Game(Point tl, Point br);
	~Game();

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

	/**********************************************************
	 * Function: getClosestDistance
	 * Description: Determine how close these two objects will
	 *   get in between the frames.
	 **********************************************************/
	float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;

	/*********************************************
	* Function: JUST LANDED
	* Description: Returns true if the lander has
	*  just successfully landed.
	*********************************************/
	bool justLanded() const;

	/*********************************************
	* Function: FUELCELL TAKEN
	* Description: Checks if asteroid lander has
	* touched the fuelcell
	*********************************************/
	void fuelcellTaken();

	/*********************************************
	* Function: PLAY AGAIN
	* Description: Checks if user wants to play
	*  again
	*********************************************/
	void playAgain() const;

	/*********************************************
	* Function: INIT
	* Description: if you'd like to reply the game
	* this handles the logic
	*********************************************/
	bool init();

	/**************************************************************************
	* GAME :: Randomise Direction
	* Randomise where from and in which direction an object is going to start
	**************************************************************************/
	void randomiseDirection(Point & point, Velocity & velocity);

	/**************************************************************************
	* GAME :: IS ON SCREEN
	* Determines if a given point is on the screen.
	**************************************************************************/
	bool isOnScreen(const Point & point);

private:

	//used for creation logic
	//Probably not the best method, but #define's we're cutting it:
	const int lAsteroid = 0;
	const int mAsteroid = 2;
	const int sAsteroid = 3;
	const int specialAsteroid = 4;

	// For creation args
	int spawn;
	bool hasInitialised;
	//Are we flying in space or is the ship landing
	bool shipLanding;

	// The coordinates of the screen
	Point topLeft;
	Point bottomRight;

	//The coordinates for the ships health bar
	Point shipHealth;
	Point shipHealthText;

	vector<Bullet*> bullets;
	vector<Rock*> rocks;
	Ship ship;

	Ground ground;
	Lander lander;
	Fuelcell bonus;

	/*************************************************
	 * Private methods to help with the game logic.
	 *************************************************/
	int wrapAround(const Point & point);
	void advanceBullets();
	void advanceRocks();
	void advanceShip();
	void advanceLander();
	void setUpAsteroidLander(const bool & shipLanding, const int & it);
	Rock* createRock(const int & spawn, const int & parRock, const float & rockLog);
	void rockHitLogic(const int & spawn, const int & it);
	void handleBulletCollisions();
	void handleShipCollisions();
	void cleanUpZombies();
};

#endif /* GAME_H */
