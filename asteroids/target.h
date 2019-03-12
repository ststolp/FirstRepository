#define TARGET_H
#ifndef TARGET_H
#include "uiDraw.h"
#include "flyingObject.h"

// my target class
class Target : public FlyingObject
{
  public:
   Target();
   ~Target();
   bool isAlive() { return FlyingObject::isAlive();  }
   void draw()     { drawCircle(FlyingObject::getPoint(), 10);}
   void advance();
};

#endif
