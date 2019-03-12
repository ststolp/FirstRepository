#include "target.h"
#include "uiDraw.h"
/****************************************************
 * Function: Target
 * Description: Set the target at a random coordinate
 * and a random velocity.
 *****************************************************/
Target :: Target()
{
   FlyingObject::setPoint(random(-200, 201), random(-200, 201));
   float num;
   float num2;
   do
   {
     num = (random(-1, 2));
   } while (num != 0);
   do
   {
     num2 = (random(-1, 2));
   } while (num2 != 0);
   Velocity velocity(num, num2);
   FlyingObject::setVelocity(velocity);
   FlyingObject::setAngle(1);
}

/**************************************************
 */

void Target :: advance()
{
   FlyingObject::setAngle(FlyingObject::getAngle() + 1);
   FlyingObject::advance();
}

/********************************************
 * Destroy target.
 ********************************************/
Target :: ~Target()
{
}

