#include "blast.h"
#include "uiDraw.h"
/***********************************************************
 * Function: Blast
 * Description: Sets point and velocity by the parameters.
 ************************************************************/
Blast :: Blast(const Point & point, const int & dx, const int & dy)
{
   FlyingObject::setPoint(point);
   Velocity velocity((5 + dx) *
                     (sin(M_PI * 180.0 / angle)),
                     (5 + dy) *
                     (-cos(M_PI * 180.0 / angle)));
   FlyingObject::setVelocity(velocity);
   FlyingObject::setFrameLife(30);
   FlyingObject::setSize(1);
}

/*****************************************************************
 * Destroy blast.
 ***********************************************************/
Blast :: ~Blast()
{
}

/**************************************************************
 * Function: advance
 * Description: move the blast for 30 frames. The blast also
 * increases in size.
 ******************************************************/
void Blast :: advance()
{
   if (FlyingObject::isFrameLife() > 0)
   {
      FlyingObject::advance();
      FlyingObject::setSize(FlyingObject::getSize() * 1.30);
      FlyingObject::setFrameLife(FlyingObject::getFrameLife() - 1);
   }
   else
      FlyingObject::setAlive(false);
}
