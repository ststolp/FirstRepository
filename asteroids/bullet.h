#ifndef BULLET_H
#define BULLET_H

#define BULLET_SPEED 5
#define BULLET_LIFE 40



// Put your Bullet class here
#include "flyingObject.h"
#include "uiDraw.h"
class Bullet : public FlyingObject
{
  private:
   float angle;
  public:
   Bullet() {}
   ~Bullet();
   void advance();
   void setAngle(int angle)    { FlyingObject::setAngle(angle);            }
   float getAngle() const      { return FlyingObject::getAngle();          } 
   void draw();
   bool isAlive() const        { return FlyingObject::isAlive();   }
   void fire(Point point, float angle, int dx, int dy);
};



#endif /* bullet_h */
