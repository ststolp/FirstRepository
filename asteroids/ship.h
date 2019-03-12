#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10
#define BLAST_SPEED 5
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5



// Put your Ship class here
#include "flyingObject.h"
#include "rocks.h"
class Ship : public FlyingObject
{
  private:
   Velocity velocity;
  public:
   int getSize() const { return SHIP_SIZE;                             }
   Ship();
   ~Ship();
   void setVelocity(Velocity velocity) { this -> velocity = velocity;  }
   Velocity getVelocity() const { return velocity;                     }
   Ship(int x, int y);
   void moveLeft();
   void setAlive(bool alive) { FlyingObject::setPoint(0, 0);
     FlyingObject::setAlive(alive);          }
   void moveRight();
   //  bool isAlive() const { return FlyingObject::isAlive();              }
   void setAngle(int angle) { FlyingObject::setAngle(angle);           }
   int getAngle() const { return FlyingObject::getAngle();             }
   void draw();
   void moveForeward();
   void advance();
};

class Blast : public FlyingObject
{
 public:
  Blast() {}
  void setBlast(const Point & point, int angle, int dx, int dy);
  ~Blast();
  void advance();
  void draw();
  bool isAlive() { return FlyingObject::isAlive();   }
  void setAlive(bool alive) { FlyingObject::setAlive(alive);   }
};

#endif /* ship_h */
