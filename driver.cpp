/*****************************************************
 * File: Driver.cpp
 * Author: Daniel R. Thomson
 *
 * Description: This file contains the main function
 *  that starts the game and the callback function
 *  that specifies what methods of the game class are
 *  called each time through the game loop.
 ******************************************************/

#include "game.h"
#include "uiInteract.h"

 /*************************************
  * All the interesting work happens here, when
  * I get called back from OpenGL to draw a frame.
  * When I am finished drawing, then the graphics
  * engine will wait until the proper amount of
  * time has passed and put the drawing on the screen.
  **************************************/
void callBack(const Interface *pUI, void *p)
{
	Game *pGame = (Game *)p;

	pGame->advance();
	pGame->handleInput(*pUI);
	pGame->draw(*pUI);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
	//I made the screen bigger, it's better that way
	Point topLeft(-250, 250);
	Point bottomRight(250, -250);

	Interface ui(argc, argv, "Asteroids", topLeft, bottomRight);
	Game game(topLeft, bottomRight);
	ui.run(callBack, &game);

	return 0;
}
