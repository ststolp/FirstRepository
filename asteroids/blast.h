#define BLAST_H
#ifndef BLAST_H
#include "uiDraw.h"
#include "flyingObject.h"

// my blast class
class Blast : public FlyingObject
{
  public:
   Blast(const Point & point, int angle, const int & dx, const int & dy);
   void advance();
   ~Blast();
   void draw()     { drawCircle(FlyingObject::getPoint(), FlyingObject::getSize())          }
};

#endif
