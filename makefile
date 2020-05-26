###############################################################
# Program:
#     Project 13, Asteroids
#     Brother Comeau, CS165
# Author:
#     Daniel R. Thomson
# Summary:
#	Fully working up compilation of projects 10, 11 and 12
#	with the inclusion of some major modifications.
#
# Above and Beyond
#
#	This program does quite a bit, alough not entirely 
#	persceivable at first. 
#
#	I included a life span for the ship, that it can get hit
#	by rocks up to 5 times before it respawns in the center of
#	the screen. I also included operator overloading that allows
#	for the velocity of the rocks that hit the ship to cause
#	scientifically correct collisions between the ship and 
#	rocks. It looks really fun. Lastly I added a speed cap
#	to the ship so that you don't go into hyper speed while 
#	trying to navigate the screen that I made bigger.
#
#	I added a special rock (The purple one) that cannot be
#	destoyed by bullets because that wouldn't be any fun,
#	since when a ship collides with this rock it enages in
#	a landing sequence allowing	the ship to land on the 
#	asteroid and complete the game.
#
#	Within this sequence I included the ability to leave back into
#	space out the top of the screen, the ability to get extra
#	fuel and the ability that when you land or crash your 
#	lander you have the	option to restart the game.
#	There's also special rock stablising functionality that
#	ensures that the special landable rock doesn't float away
#	when you're going to land on it.
###############################################################

LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rock.o bigRock.o mediumRock.o smallRock.o specialBigRock.o lander.o ground.o fuelcell.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rock.o bigRock.o mediumRock.o smallRock.o specialBigRock.o lander.o ground.o fuelcell.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o   Handles input events
#    point.o        The position on the screen
#    game.o         Handles the game interaction
#    velocity.o     Velocity (speed and direction)
#    flyingObject.o Base class for all flying objects
#    ship.o         The player's ship
#    bullet.o       The bullets fired from the ship
#    rock.o         Contains abstraction for Rock classes
#	 bigRock.o		Large asteroid functionality
#	 mediumRock.o	medium asteroid functionality
#	 smallRock.o	small asteroid functionality
#	 specialBigRock.o	Large rock that can be landed on
#	 lander.o		ship with  unique navigatation properties 
#	 ground.o		The terrain of the asteroid with a landing deck
#	 fuelcell.o		Extra fuel for a lander.
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

driver.o: driver.cpp game.h
	g++ -c driver.cpp

game.o: game.cpp game.h uiDraw.h uiInteract.h point.h velocity.h flyingObject.h bullet.h rock.h bigRock.h mediumRock.h smallRock.h ship.h specialBigRock.h lander.h ground.h fuelcell.h
	g++ -c game.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp flyingObject.h point.h velocity.h uiDraw.h
	g++ -c flyingObject.cpp

ship.o: ship.cpp ship.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c ship.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c bullet.cpp

rock.o: rock.cpp rock.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c rock.cpp

bigRock.o: bigRock.cpp bigRock.h rock.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c bigRock.cpp

mediumRock.o: mediumRock.cpp mediumRock.h rock.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c mediumRock.cpp

smallRock.o: smallRock.cpp smallRock.h rock.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c smallRock.cpp

specialBigRock.o: specialBigRock.cpp specialBigRock.h rock.h bigRock.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c specialBigRock.cpp

lander.o: lander.cpp lander.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c lander.cpp

fuelcell.o: fuelcell.cpp fuelcell.h point.h uiDraw.h
	g++ -c fuelcell.cpp

ground.o: ground.cpp ground.h point.h uiDraw.h
	g++ -c ground.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
