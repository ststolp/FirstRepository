#include "rocks.h"
#include "uiDraw.h"

// Put your Rock methods here

/***********************************
 * Destroy rock.
 ***********************************/
Rock :: ~Rock()
{
}

/*********************************************************************
 * Function: LargeAsteroid
 * Description: The Lage Asteroid accepts a point and velocity and sets
 * itt own point and velocity accordingly.
 ************************************************************/
LargeAsteroid :: LargeAsteroid(Velocity velocity, Point point)
{
   FlyingObject::setVelocity(velocity);
   FlyingObject::setPoint(point.getX(), point.getY());
   Rock::setAngle(random(0, 360));
   setType(1);
}

/*******************************************
 * Destroy Large asteroid.
 ********************************************/
LargeAsteroid :: ~LargeAsteroid()
{
}

/****************************************************
 * Function: advance
 * Description: Advance Large asteroid. Making sure it stays on the
 * the screen by wrapping around it.
 ***************************************************/
void LargeAsteroid :: advance()
{
   FlyingObject::advance();
   Rock::setAngle(getAngle() + BIG_ROCK_SPIN);
   if (FlyingObject::getPoint().getX() > 200)
      FlyingObject::setPoint(-200, FlyingObject::getPoint().getY());
   if (FlyingObject::getPoint().getX() < -200)
      FlyingObject::setPoint(200, FlyingObject::getPoint().getY());
   if (FlyingObject::getPoint().getY() > 200)
      FlyingObject::setPoint(FlyingObject::getPoint().getX(), -200);
   if (FlyingObject::getPoint().getY() < -200)
      FlyingObject::setPoint(FlyingObject::getPoint().getX(), 200);
}

/****************************************
 * Draw Large asteroid.
 ******************************************/
void LargeAsteroid :: draw()
{
   drawLargeAsteroid(FlyingObject::getPoint(), getAngle());
}

/************************************************************
 * Function: MediumAsteroid
 * Description: Constructor for medium asteroid accepts a velocity and point
 * and sets its own point and velocity accordingly.
 *************************************************************/
MediumAsteroid :: MediumAsteroid(Velocity velocity, Point point)
{
   FlyingObject::setPoint(point.getX(), point.getY());
   FlyingObject::setVelocity(velocity);
   Rock::setAngle(random(0, 360));
   setType(2);
}

/*********************************************
 * Function: advance
 * Description: advance medium asteroid. Make sure it stays
 * on the screen by wrapping around it.
 *************************************************/
void MediumAsteroid :: advance()
{
   FlyingObject::advance();
   Rock::setAngle(getAngle() + MEDIUM_ROCK_SPIN);
   if (FlyingObject::getPoint().getX() > 200)
      FlyingObject::setPoint(-200, FlyingObject::getPoint().getY());
   if (FlyingObject::getPoint().getX() < -200)
      FlyingObject::setPoint(200, FlyingObject::getPoint().getY());
   if (FlyingObject::getPoint().getY() > 200)
      FlyingObject::setPoint(FlyingObject::getPoint().getX(), -200);
   if (FlyingObject::getPoint().getY() < -200)
      FlyingObject::setPoint(FlyingObject::getPoint().getX(), 200);
}

/*************************************************
 * draw Medium asteroid.
 *************************************************/
void MediumAsteroid :: draw()
{
   drawMediumAsteroid(FlyingObject::getPoint(), getAngle());
}

/*************************************
 * Destroy medium asteroid.
 **************************************/
MediumAsteroid :: ~MediumAsteroid()
{
}

/*************************************************************
 * Function: SmallAsteroid
 * Desciption: Constructor for small asteroid accepts a velocity and point
 * and sets its own accordingly.
 ****************************************************************/
SmallAsteroid :: SmallAsteroid(Velocity velocity, Point point)
{
   FlyingObject::setPoint(point.getX(), point.getY());
   FlyingObject::setVelocity(velocity);
   Rock::setAngle(random(0, 360));
   setType(3);
}

/********************************************************
 * Destroy small asteroid.
 ************************************************************/
SmallAsteroid :: ~SmallAsteroid()
{
}

/**************************************************************
 * Draw Small asteroid.
 **************************************************************/
void SmallAsteroid :: draw()
{
   drawSmallAsteroid(FlyingObject::getPoint(), getAngle());
}

/*******************************************************************
 * Function: Advance
 * Description: Advance small asteroid. Make sure it stays on the screen by
 * wrapping around it.
 **************************************************************/
void SmallAsteroid :: advance()
{
   FlyingObject::advance();
   Rock::setAngle(getAngle() + SMALL_ROCK_SPIN);
   if (FlyingObject::getPoint().getX() > 200)
      FlyingObject::setPoint(-200, FlyingObject::getPoint().getY());
   if (FlyingObject::getPoint().getX() < -200)
      FlyingObject::setPoint(200, FlyingObject::getPoint().getY());
   if (FlyingObject::getPoint().getY() > 200)
      FlyingObject::setPoint(FlyingObject::getPoint().getX(), -200);
   if (FlyingObject::getPoint().getY() < -200)
      FlyingObject::setPoint(FlyingObject::getPoint().getX(), 200);
}

/******************************************************************
 * Function: Ball
 * Description: Ball gets a random point and random velocity.
 *****************************************************************/
Ball :: Ball()
{
  Point point (random(-200, 201), random(-200, 201));
  FlyingObject::setPoint(point.getX(), point.getY());
  int num;
  int num2;
  do
    {
      num = random(-1, 1);
    } while(num == 0);
  do
    {
      num2 = random(-1, 1);
    } while (num2 == 0);
  Velocity velocity(num, num2);
  FlyingObject::setVelocity(velocity);
}

/*******************************
 * Destroy ball.
 **************************************/
Ball :: ~Ball()
{
}

/****************************************************
 * Function: advance
 * Description: advance the ball and keep it on 
 * the screen.
 ************************************************************/
void Ball :: advance()
{
  FlyingObject::advance();
  if (FlyingObject::getPoint().getX() > 200)
    FlyingObject::setPoint(-200, FlyingObject::getPoint().getY());
  if (FlyingObject::getPoint().getX() < -200)
    FlyingObject::setPoint(200, FlyingObject::getPoint().getY());
  if (FlyingObject::getPoint().getY() > 200)
    FlyingObject::setPoint(-200, FlyingObject::getPoint().getY());
  if (FlyingObject::getPoint().getY() < -200)
    FlyingObject::setPoint(FlyingObject::getPoint().getX(), 200);
}

/*********************************************
 * Draw the ball....
 ***********************************************/
void Ball :: draw()
{
  drawCircle(FlyingObject::getPoint(), 10);
}
