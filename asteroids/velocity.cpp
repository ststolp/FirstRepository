#include "velocity.h"


// Put your velocity methods here
/****************************************
 * Default constructor set velocity to
 * zero.
 ****************************************/
Velocity :: Velocity()
{
   setDx(0);
   setDy(0);
}

/*********************************************
 * Non-default constructor sets velocity to
 * a given velocity.
 **********************************************/
Velocity :: Velocity(int dx, int dy)
{
   setDy(dy);
   setDx(dx);
}
