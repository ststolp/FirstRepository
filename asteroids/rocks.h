#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include "bullet.h"
// Define the following classes here:
//   Rock
class Rock : public FlyingObject
{
  public:
   Rock() {}
   float getAngle() const      { return FlyingObject::getAngle();            }
   void setAngle(float angle)  { FlyingObject::setAngle(angle);   }
   int getType() const         { return type;             }
   void setType(int type)      { this -> type = type;     }
   virtual int hit() = 0;
   Point getPoint() const      { return FlyingObject::getPoint(); }
   Velocity getVelocity()      { return FlyingObject::getVelocity();}
   void draw() {}
   int getSize() const {}
   bool isAlive() const        { return FlyingObject::isAlive();      }
   ~Rock();
   private:
   int type;
   int angle;
};
//   BigRock
class LargeAsteroid : public Rock
{
  public:
   LargeAsteroid(Velocity velocity, Point point);
   ~LargeAsteroid();
   void advance();
   void draw();
   int getSize() const { return BIG_ROCK_SIZE;   }
   int hit()  { FlyingObject::kill();
     return getType();   }
};
//   MediumRock
class MediumAsteroid : public Rock
{
  public:
   MediumAsteroid(Velocity velocity, Point point);
   void advance();
   void draw();
   int hit()   { FlyingObject::kill();
     return getType();      }
   int getSize() const { return MEDIUM_ROCK_SIZE;   }
   ~MediumAsteroid();
};
//   SmallRock
class SmallAsteroid : public Rock
{
  public:
   SmallAsteroid(Velocity velocity, Point point);
   void advance();
   void draw();
   int hit()   { FlyingObject::kill();
     return getType();     }
   int getSize() const    { return SMALL_ROCK_SIZE;   }
   ~SmallAsteroid();
};

//  targetRock
class Ball : public Rock
{
 public:
  Ball();
  void advance();
  void draw();
  int hit() { return 0;}
  ~Ball();
  bool isAlive()  { return FlyingObject::isAlive();   }
};
   
#endif /* rocks_h */
