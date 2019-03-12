#include "ship.h"
#include <cmath>
#include "uiDraw.h"
// Put your ship methods here

/************************************************
 * Function: Ship
 * Description: Constructor makes ship alive and sets position
 * in the middle.
 ************************************************/
Ship :: Ship()
{
   FlyingObject::setPoint(0, 0);
   FlyingObject::setAngle(60);
}

/***************************************************
 * Function: Ship
 * Description: Ship constructor that has a given coordinate.
 ************************************************/
Ship :: Ship(int x, int y)
{
   FlyingObject::setPoint(x, y);
   FlyingObject::setAngle(60);
}

/*******************************************************
 * Function: moveLeft:
 * Description: Rotate ship to the left.
 ****************************************************/
void Ship :: moveLeft()
{
  setAngle(getAngle() + ROTATE_AMOUNT);
}

/****************************************************
 * Function: moveRight
 * Descripion: Rotate ship to the right.
 *********************************************************/
void Ship :: moveRight()
{
  setAngle(getAngle() - ROTATE_AMOUNT);
}

/********************************************************
 * Function: moveForeward:
 * Description: Reset velocity to the current angle.
 ********************************************************/
void Ship :: moveForeward()
{
   velocity.setDx(THRUST_AMOUNT *
                  (sin(M_PI / 180.0 * getAngle())) * -1);
   velocity.setDy(THRUST_AMOUNT *
                  (-cos(M_PI / 180.0 * getAngle())) * -1);
   FlyingObject::setVelocity(getVelocity());
}

/*********************************************************
 * Destroy ship.
 *******************************************************/
Ship :: ~Ship()
{
}

/***************************************************************
 * Draw ship.
 ***********************************************************/
void Ship :: draw()
{
   drawShip(FlyingObject::getPoint(), getAngle());
}

/*************************************************************
 * Advance ship. Makes sure it stays on the screen by changing
 * coordinate to stay on screen.
 ***************************************************************/
void Ship :: advance()
{
   if (FlyingObject::getPoint().getX() > 200)
      FlyingObject::setPoint(-200, FlyingObject::getPoint().getY());
   if (FlyingObject::getPoint().getX() < -200)
      FlyingObject::setPoint(200, FlyingObject::getPoint().getY());
   if (FlyingObject::getPoint().getY() > 200)
      FlyingObject::setPoint(FlyingObject::getPoint().getX(), -200);
   if (FlyingObject::getPoint().getY() < -200)
      FlyingObject::setPoint(FlyingObject::getPoint().getX(), 200);
   FlyingObject::advance();
}

/*****************************************************************************
 * Function setBlast
 * Description: Blast gets the ships point and velocity plus a little
 * more speed.
 ***************************************************************************/
void Blast :: setBlast(const Point & point, int angle,
		       int dx, int dy)
{
  FlyingObject::setPoint(point.getX(), point.getY());
  FlyingObject::setFrameLife(20);
  FlyingObject::setSize(10);
  Velocity a((dx + BLAST_SPEED) *
	     (sin(M_PI / 180.0 * angle)) * -1,
             (dx + BLAST_SPEED) * (-cos(M_PI / 180.0 *
					angle)) * -1);
  FlyingObject::setVelocity(a);
}

/******************************************************
 * Function: advance
 * Description: Advance the blast.
 **************************************************/
void Blast :: advance()
{
  FlyingObject::advance();
  FlyingObject::setFrameLife(FlyingObject::getFrameLife() - 1);
  if (FlyingObject::getFrameLife() < 0)
    FlyingObject::kill();
  if (FlyingObject::getPoint().getX() > 200)
    FlyingObject::setPoint(-200, FlyingObject::getPoint().getY());
  if (FlyingObject::getPoint().getX() < -200)
    FlyingObject::setPoint(200, FlyingObject::getPoint().getY());
  if (FlyingObject::getPoint().getY() > 200)
    FlyingObject::setPoint(FlyingObject::getPoint().getX(), -200);
if (FlyingObject::getPoint().getY() < -200)
  FlyingObject::setPoint(FlyingObject::getPoint().getX(), 200);
}

/*****************************************************
 * Function: draw
 * Description: Draw the blast
 ********************************************************/
void Blast :: draw()
{
  drawCircle(FlyingObject::getPoint(), 100);
}

/********************************************
 * Destroy blast.
 ***********************************************/
Blast :: ~Blast()
{
}
