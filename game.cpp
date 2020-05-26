/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 * *********************************************************************/

#include "game.h"

 // These are needed for the getClosestDistance function,
 // which is currently unused
#include <limits>
#include <algorithm>

using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 7

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game::Game(Point tl, Point br)
	: topLeft(tl), bottomRight(br), ship(),
	spawn(lAsteroid), ground(topLeft, bottomRight),
	shipLanding(false), hasInitialised(false)
{
	//Lander initial states
	lander.setAlive(false);
	lander.setPoint(Point(0, 200));

	//Ship health bar
	shipHealthText.setX(tl.getX() + 15);
	shipHealthText.setY(tl.getY() - 15);
	
	shipHealth.setX(shipHealthText.getX() + 75);
	shipHealth.setY(shipHealthText.getY() + 10);

	//create Five big rocks to start out with
	for (int i = 0; i < 5; i++)
	{
		rocks.push_back(createRock(spawn, 0, 0.0));
	}

	//Create one instance of a special big rock
	rocks.push_back(createRock(specialAsteroid, 0, 0.0));

}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i] != NULL)
		{
			delete rocks[i];
			rocks[i] = NULL;
		}
		rocks.clear();
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i] != NULL)
		{
			delete bullets[i];
			bullets[i] = NULL;
		}
		bullets.clear();
	}
}

/**************************************************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 **************************************************************************/
void Game::advance()
{
	if (!shipLanding)
	{
		advanceBullets();
		advanceRocks();
		advanceShip();
		handleBulletCollisions();
		handleShipCollisions();
		cleanUpZombies();
	}
	else
	{
		advanceLander();
	}

}

/**************************************************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it, allowing for wrap around
 **************************************************************************/
void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i]->FlyingObject::advance(wrapAround(bullets[i]->getPoint()));
			bullets[i]->setLifespan((bullets[i]->getLifespan() - 1));

			if (bullets[i]->getLifespan() <= 0)
			{
				bullets[i]->kill();
			}
		}
	}
}

/**************************************************************************
 * GAME :: ADVANCE Rock
 * Go through each Rock and advance it, allowing for wrap around
 **************************************************************************/
void Game::advanceRocks()
{
	for (int i = 0; i < rocks.size(); i++)
	{
		// we have a rock, make sure it's alive
		if (rocks[i]->isAlive())
		{
			// move it forward
			rocks[i]->FlyingObject::advance(wrapAround(rocks[i]->getPoint()));
		}
		else if (!rocks[i]->isAlive())
		{
			rocks[i]->kill();
		}
	}
}

/**************************************************************************
 * GAME :: ADVANCE SHIP
 * Advance the Ship, allowing for wrap around
 **************************************************************************/
void Game::advanceShip()
{
	if (ship.isAlive())
	{
		ship.FlyingObject::advance(wrapAround(ship.getPoint()));
	}
	drawText(shipHealthText, "Ship Health: ");
	drawNumber(shipHealth, ship.getLife());
}

/***************************************
* GAME :: ADVANCE LANDER
* advance Subsection of the game.
***************************************/
void Game::advanceLander()
{
	fuelcellTaken();

	if (lander.isAlive() && !lander.isLanded())
	{
		// advance the lander
		lander.applyGravity(GRAVITY_AMOUNT);
		lander.FlyingObject::advance(0);

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

		if (!isOnScreen(lander.getPoint()))
		{
			hasInitialised = init();
		}
	}
}

/******************************************************************
* GAME :: Set Up Asteroid Lander
* Establish conditions of subection of game
*******************************************************************/
void Game:: setUpAsteroidLander(const bool & shipLanding, const int & it)
{
	if (shipLanding)
	{
		lander.setAlive(true);
		lander.setLanded(false);
		lander.setFuel(500);
		bonus.setTaken(false);
		lander.setVelocity(Velocity(0, 0));

		//The Ship has docked
		ship.setPoint(Point(rocks[it]->getPoint().getX(), rocks[it]->getPoint().getY()));
	}
}

/**************************************************************************
* GAME :: WRAP AROUND
* Determines if a given point is off the screen and returns int's for
* advancing logic.
**************************************************************************/
int Game::wrapAround(const Point & point)
{
	if ((point.getX() > bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT)
		|| (point.getX() < topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT))
	{
		return 1;
	}
	else if ((point.getY() > topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT)
		|| (point.getY() < bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT))
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

/**************************************************************************
* GAME :: IS ON SCREEN
* Determines if a given point is on the screen.
**************************************************************************/
bool Game::isOnScreen(const Point & point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
* GAME :: Randomise Direction 
* Randomise where from and in which direction an object is going to start
**************************************************************************/
void Game:: randomiseDirection(Point & point, Velocity & velocity)
{
	double leftRight = random(1, 10000);

	if (leftRight > 5000) 
	{
		// left
		point.setX(topLeft.getX());
		point.setY(random(bottomRight.getY(), bottomRight.getX()));
		velocity.setDx(1);
	}
	else
	{
		//or right
		point.setX(topLeft.getY());
		point.setY(random(bottomRight.getY(), bottomRight.getX()));
		velocity.setDx(-1);
	}
	velocity.setDy(random(-3.0, 3.0));
}

/**************************************************************************
 * GAME :: CREATE ROCK
 * Create a rock of determinant constriants
 **************************************************************************/
Rock* Game::createRock(const int & spawn, const int & parRock, const float & rockLog)
{
	Rock* newRock = NULL;
	Point origin;
	Velocity direction;

	if (spawn == lAsteroid) //Large Asteroids
	{
		//randomise the selection for left of right of screen
		randomiseDirection(origin, direction);
		newRock = new BigRock(origin, direction);
	}

	if (spawn == specialAsteroid) // Special Asteroids
	{
		if (hasInitialised)
		{
			origin.setX(ship.getPoint().getX());
			origin.setY(ship.getPoint().getY() - 30);
		}
		else
		{
			//randomise the selection for left of right of screen
			randomiseDirection(origin, direction);
		}
		newRock = new SpecialBigRock(origin, direction);
	}

	if (spawn == mAsteroid) //Medium Asteroids
	{
		origin = rocks[parRock]->getPoint(); //Where on the screen did it's bigger ancestor die
		direction = rocks[parRock]->getVelocity();
		direction.setDy(direction.getDy() + rockLog); // Leaving up or down
		newRock = new MediumRock(origin, direction);
	}

	if (spawn == sAsteroid) // Small Asteroids
	{
		origin = rocks[parRock]->getPoint(); // Where on the screen did it's bigger ancestor die
		direction = rocks[parRock]->getVelocity();
		direction.setDx(direction.getDx() + rockLog); // Leaving left or right
		newRock = new SmallRock(origin, direction);
	}

	return newRock;
}

/**************************************************************************
* GAME :: ROCK HIT LOGIC
* ENCAPSULATES LOGIC FOR COLLISIONS WITH ROCKS
**************************************************************************/
void Game::rockHitLogic(const int & spawn, const int & it)
{
	// Counts how many time's the ship was hit.
	// If ship.life falls under 5 ship respawns at center.
	if (spawn == SHIP_DAMAGE)
	{
		ship.setLife(ship.getLife() + SHIP_DAMAGE);
	}

	if (spawn == specialAsteroid)
	{
	}

	if (spawn == mAsteroid)
	{
		//If a large asteroid was hit create two mediums and a small
		rocks.push_back(createRock(mAsteroid, it, 1.0));
		rocks.push_back(createRock(mAsteroid, it, -1.0));
		rocks.push_back(createRock(sAsteroid, it, 2.0));
	}

	if (spawn == sAsteroid)
	{
		//If a medium asteroid was hit create two smalls
		rocks.push_back(createRock(sAsteroid, it, 3.0));
		rocks.push_back(createRock(sAsteroid, it, -3.0));
	}
}

/**************************************************************************
 * GAME :: HANDLE BULLET COLLISIONS
 * Check for a collision between a Rock and a bullet.
 **************************************************************************/
void Game::handleBulletCollisions()
{
	// Temporary collision variables
	float rockSize;
	float bulletDistance;
	Rock * tempRock;

	// Check for a hit (if it is close enough to any live bullets)
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < rocks.size(); j++)
		{
			tempRock = rocks[j];
			rockSize = tempRock->getRadius();
			bulletDistance = getClosestDistance(*(bullets[i]), *tempRock);

			if (bullets[i] != NULL && bullets[i]->isAlive())
			{
				// this bullet is alive, see if its too close

				// check if the rock is at this point (in case it was hit)
				if (rocks[j] != NULL && rocks[j]->isAlive())
				{

					/*if ((fabs(bullets[i]->getPoint().getX() - rocks[j]->getPoint().getX()) <= rocks[j]->getRadius()
						&& fabs(bullets[i]->getPoint().getY() - rocks[j]->getPoint().getY()) <= rocks[j]->getRadius()))*/
					if (bulletDistance <= rockSize)
					{
						//we have a hit!
						spawn = rocks[j]->hit();

						//Work out which rocks should be showing up
						rockHitLogic(spawn, j);

						// the bullet is dead
						bullets[i]->kill();

						// the rock is dead as well
						rocks[j]->kill();
					}
				}
			}// if bullet is alive
		} // for Rocks
	}// for bullets
}

/**************************************************************************
* GAME :: HANDLE SHIP COLLISIONS
* Check for a collision between a Rock and a Ship.
**************************************************************************/
void Game::handleShipCollisions()
{
	float rockSize;
	float shipDistance;
	Rock * tempRock;
	// now check for a hit (if it is close enough to any live bullets)
	for (int i = 0; i < rocks.size(); i++)
	{
		// this rock is alive, see if its too close
			// check if the ship is at this point (in case it was hit)
		if (rocks[i] != NULL && rocks[i]->isAlive())
		{
			tempRock = rocks[i];
			rockSize = tempRock->getRadius();
			shipDistance = getClosestDistance(ship, *tempRock);
			if (shipDistance <= rockSize
				/*fabs(ship.getPoint().getX() - rocks[i]->getPoint().getX()) <= ship.getRadius()
				&& fabs(ship.getPoint().getY() - rocks[i]->getPoint().getY()) <= ship.getRadius()*/)
			{
				//"Captain Kirk, damage to the ship's shield is beyond repair." We're going to be destroyed.
				spawn = ship.hit();

				ship.setVelocity(Velocity(ship.getVelocity().getDx() + rocks[i]->getVelocity().getDx(), ship.getVelocity().getDy() + rocks[i]->getVelocity().getDy()));

				// Collisions cause velocity change.
				// I decided this over immediately ending the game since it looks cooler.

				//ship.setVelocity(ship.getVelocity() + rocks[i]->getVelocity());

				//Work out ship damage
				rockHitLogic(spawn, i);

				//Respawn the ship
				if (!(ship.getLife() > 0))
				{
					ship.setPoint(0);
					ship.setLife(5);
				}

				// the rock is dead as well or we are engaging in a landing sequence
				shipLanding = rocks[i]->kill();
				setUpAsteroidLander(shipLanding, i);
				if (shipLanding && ship.getLife() < 5)
				{
					ship.setLife(ship.getLife() - SHIP_DAMAGE);
				}
			}
		} // for Ship and Rocks
	} //end loop of vector
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets and rocks out of the list)
 **************************************************************************/
void Game::cleanUpZombies()
{
	vector<Rock*>::iterator rockIt = rocks.begin();

	while (rockIt != rocks.end())
	{
		Rock* pRock = *rockIt;

		// check for destroyed rock
		if (pRock != NULL && !pRock->isAlive())
		{
			// the rock is destroyed, but the memory is not freed up yet
			delete *rockIt;
			*rockIt = NULL;
			rockIt = rocks.erase(rockIt);
		}
		else
		{
			rockIt++;// advance the iterator
		}
	}

	// Look for dead bullets
	vector<Bullet*>::iterator bulletIt = bullets.begin();

	while (bulletIt != bullets.end())
	{
		Bullet* pBullet = *bulletIt;

		if (!pBullet->isAlive())
		{
			delete *bulletIt;
			*bulletIt = NULL;
			// remove from vector and move on
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++; // advance the iterator
		}
	}
}

/**************************************************************************
 * GAME :: HANDLE INPUT
 * Accept input from the user
 **************************************************************************/
void Game::handleInput(const Interface & ui)
{
	if (!shipLanding)
	{
		// Handle controls for  the ship
		// Forward thrusting motion
		if (ui.isUp())
		{
			if (ship.isAlive())
			{
				ship.setThrust(true);
				ship.applyThrust();
			}
			else
			{
				ship.setThrust(false);
			}
		} //when not pressed, don't thrust
		else
		{
			ship.setThrust(false);
		}

		// left
		if (ui.isLeft())
		{
			ship.rotateLeft();
		}

		// right
		if (ui.isRight())
		{
			ship.rotateRight();
		}

		// Check for "Spacebar
		// fire bullets
		if (ui.isSpace())
		{
			Bullet* newBullet = new Bullet(ship.getPoint());
			newBullet->fire(ship.getPoint(), ship.getAngle(), ship.getVelocity());

			bullets.push_back(newBullet);
		}
	}
	else
	{
		//Handle controls for asteroid lander
		if (lander.isAlive() && !lander.isLanded())
		{
			//slow decent
			if (ui.isDown())
			{
				lander.applyThrustBottom();
			}

			//thrust to the right
			if (ui.isLeft())
			{
				lander.applyThrustLeft();
			}

			//thrust to the left

			if (ui.isRight())
			{
				lander.applyThrustRight();
			}
		}
		else
		{
			//Once the ship has landed or crashed on the asteroid,
			// we can then start the game over.
			if (ui.isSpace())
			{
				hasInitialised = init();
			}
		}

	}
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game::draw(const Interface & ui)
{
	if (!shipLanding)
	{
		// draw the rock(s), if they are alive
		for (int i = 0; i < rocks.size(); i++)
		{
			if (rocks[i] != NULL && rocks[i]->isAlive())
			{
				rocks[i]->draw();
			}
		}

		// draw the ship, if alive
		if (ship.isAlive())
		{
			ship.draw();
		}

		// draw the bullet(s), if they are alive
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->isAlive())
			{
				bullets[i]->draw();
			}
		}
	}
	else
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
			drawText(Point(90, 100), "BONUS!");
		}

		Point fuelLocation;
		fuelLocation.setX(topLeft.getX() + 5);
		fuelLocation.setY(topLeft.getY() - 5);

		drawNumber(fuelLocation, lander.getFuel());

		// draw ground
		ground.draw();
	}
}

/*********************************************
* Function: JUST LANDED
* Description: Returns true if the lander has
*  just successfully landed.
*********************************************/
bool Game::justLanded() const
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

/*********************************************
* GAME :: FUELCELLTAKEN
* Check to see if lander has flown by.
*********************************************/
void Game::fuelcellTaken()
{
	if (!bonus.isTaken())
	{
		if ((lander.getPoint().getX() > 85 && lander.getPoint().getX() < 120)
			&& (lander.getPoint().getY() > 90 && lander.getPoint().getY() < 105))
		{
			bonus.setTaken(true);
			lander.setFuel((lander.getFuel() + BONUS_FUEL));
		}
	}
	else
	{
		bonus.setTaken(true);
	}
}

/*********************************************
* GAME :: PLAYAGAIN
* Display a prompt to replay.
*********************************************/
void Game::playAgain() const
{
	drawText(Point(0, -10), "Press \"Space\" to play again");
}

/*********************************************
* GAME :: INIT
* Initialise all game parameters.
*********************************************/
bool Game::init()
{
	//get rid of old living rocks
	vector<Rock*>::iterator rockIt = rocks.begin();

	while (rockIt != rocks.end())
	{
		Rock* pRock = *rockIt;

		// check for destroyed rock
		if (pRock != NULL && pRock->isAlive())
		{
			// the rock is destroyed, but the memory is not freed up yet
			delete *rockIt;
			*rockIt = NULL;
			rockIt = rocks.erase(rockIt);
		}
		else
		{
			rockIt++;// advance the iterator
		}
	}

	shipLanding = false;
	spawn = 0;

	//Lander initial states
	lander.setAlive(false);
	bonus.setTaken(false);
	lander.setPoint(Point(0, 200));

	//ship initial states
	ship.setVelocity(Velocity(0, 0));

	//Ship health bar
	shipHealthText.setX(topLeft.getX() + 15);
	shipHealthText.setY(topLeft.getY() - 15);

	shipHealth.setX(shipHealthText.getX() + 75);
	shipHealth.setY(shipHealthText.getY() + 10);

	//create Five big rocks to start out with
	for (int i = 0; i < 5; i++)
	{
		rocks.push_back(createRock(spawn, 0, 0.0));
	}

	//Create one instance of a special big rock
	rocks.push_back(createRock(specialAsteroid, 0, 0.0));
	return true;
}

/**********************************************************
* Function: getClosestDistance
* Description: Determine how close these two objects will
*   get in between the frames.
**********************************************************/
float Game::getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
	// find the maximum distance traveled
	float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
	dMax = max(dMax, abs(obj2.getVelocity().getDx()));
	dMax = max(dMax, abs(obj2.getVelocity().getDy()));
	dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.

	float distMin = std::numeric_limits<float>::max();
	for (float i = 0.0; i <= dMax; i++)
	{
		Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
			obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
		Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
			obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));

		float xDiff = point1.getX() - point2.getX();
		float yDiff = point1.getY() - point2.getY();

		float distSquared = (xDiff * xDiff) + (yDiff * yDiff);

		distMin = min(distMin, distSquared);
	}

	return sqrt(distMin);
}