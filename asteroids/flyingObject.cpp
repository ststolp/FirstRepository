#include "flyingObject.h"


// Put your FlyingObject method bodies here
/***************************************************
 * Function: FlyingObject
 * Description: Sets alive to true.
 **************************************************/
FlyingObject :: FlyingObject()
{
   setAlive(true);
}

/**************************************************
 * Function: ~FlyingObject
 * Description: Destroy FlyingObject.
 *******************************************/
FlyingObject :: ~FlyingObject()
{
}

/************************************************
 * Function: setPoint
 * Description: Accepts a coordinate to set x
 * and y.
 *****************************************************/
void FlyingObject :: setPoint(float x, float y)
{
   point.setX(x);
   point.setY(y);
}



