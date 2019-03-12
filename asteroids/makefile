###############################################################
# Program:
#     Milestone 12, Asteroids
#     Brother McCracken, CS165
# Author:
#     Steven Stolp
# Summary:
#     Put your summary code here...
#     Using classes, asteroids of three sizes that inherits from a 
#     rock base class moves accross the screen. The user navigates
#     a ship and can shoot bullets with the spacebar. The bullets
#     , the rock and ship classes all have a flying object from 
#     the flying object class.  
# Above and Beyond
#     The ship has three lives and the amount of lives left are
#     displayed on the screen. Loosing a life takes away 10
#     points. A score is also kept and is displayed. Large rocks
#     are three points, medium rocks 2 points, and small rocks
#     one point. When the rocks are cleared, a screen appears
#     to congradulate the player and can choose to start the
#     next level. At level three the ship fires two bullets, at
#     level 5, a target ball is called. When the circle is hit
#     the next fire calls a blast which destroys everythin in
#     it's path. When all three lives are killed, a game over
#     screen is displayed that shows the current score and the
#     high score, and the level. The user can choose to play
#     again by pressing the down arrow key.
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: uiInteract.o uiDraw.o point.o velocity.o flyingObject.o bullet.o rocks.o ship.o game.o driver.o
	g++ uiInteract.o uiDraw.o point.o velocity.o flyingObject.o bullet.o rocks.o ship.o game.o driver.o $(LFLAGS)

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
#    rocks.o        Contains all of the Rock classes
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

driver.o: driver.cpp game.h uiDraw.h
	g++ -c driver.cpp

game.o: game.cpp game.h uiDraw.h uiInteract.h point.h velocity.h flyingObject.h bullet.h rocks.h ship.h 
	g++ -c game.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp flyingObject.h point.h velocity.h uiDraw.h
	g++ -c flyingObject.cpp

ship.o: ship.cpp ship.h flyingObject.h point.h velocity.h uiDraw.h rocks.h
	g++ -c ship.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c bullet.cpp

rocks.o: rocks.cpp rocks.h flyingObject.h point.h velocity.h uiDraw.h bullet.h
	g++ -c rocks.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
