#include "bullet.h"
#include <cmath>
#include "flyingObject.h"

// Put your bullet methods here


/*****************************************
 * Destroy bullet.
 ****************************************/
Bullet :: ~Bullet()
{
}

/*****************************************
 * Function: advance
 * Description: Advance bullet. Check to see if bullet
 * is off screen and make sure it "wraps."
 ****************************************/
void Bullet :: advance()
{
  FlyingObject::setFrameLife(FlyingObject::getFrameLife() - 1);
  if (FlyingObject::getFrameLife() > -1 && FlyingObject::isAlive())
    {
      FlyingObject::advance();
      if (FlyingObject::getPoint().getX() > 200)
         FlyingObject::setPoint(-200, FlyingObject::getPoint().getY());
      if (FlyingObject::getPoint().getX() < -200)
         FlyingObject::setPoint(200, FlyingObject::getPoint().getY());
      if (FlyingObject::getPoint().getY() > 200)
         FlyingObject::setPoint(FlyingObject::getPoint().getX(), -200);
      if (FlyingObject::getPoint().getY() < -200)
         FlyingObject::setPoint(FlyingObject::getPoint().getX(), 200);
       }
   else 
       FlyingObject::kill();
}

/****************************************************************
 *  Function: fire
 *  Description: The bullet initially gets the point of the ship and it's
 *  velocity plus BULLET_SPEED.
 **************************************************************/
void Bullet :: fire(Point point, float angle, int dx, int dy )
{
   FlyingObject::setPoint(point.getX(), point.getY());
   FlyingObject::setAngle(angle);
   Velocity velocity((BULLET_SPEED + dx) *
                             (sin (M_PI / 180.0 * angle)) * -1,
                             (BULLET_SPEED + dy) *
                             (-cos(M_PI / 180.0 * angle)) * -1);
   FlyingObject::setVelocity(velocity);
   FlyingObject::setFrameLife(40);
}

/****************************************************
 * Draw bullet.
 ***************************************************/
void Bullet :: draw()
{
   drawDot(FlyingObject::getPoint());
}
