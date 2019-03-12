#ifndef flyingObject_h
#define flyingObject_h
// Put your FlyingObject class here
#include "point.h"
#include "velocity.h"
class FlyingObject
{
  private:
   Point point;
   Velocity velocity;
   bool alive;
   int size;
   int angle;
   int frameLife;
  public:
   FlyingObject();
   void setPoint(float x, float y);
   int getSize() const                 { return size;                  }
   int getFrameLife() const            { return frameLife;             }
   void setFrameLife(int frameLife)    { this -> frameLife = frameLife;}
   int getAngle() const                { return angle;                 }
   void setSize(int size)              { this ->size = size;           }
   void setAngle(int angle)            { this -> angle = angle;        }
   Point getPoint() const              { return point;                 }
   void setVelocity(Velocity velocity) { this ->velocity = velocity;   }
   Velocity getVelocity() const        { return velocity;              }
   void kill()                         { setAlive(false);              }
   virtual void advance()              { point.addX(velocity.getDx());
                               point.addY(velocity.getDy());           }
   void setAlive(bool alive)           { this -> alive = alive;        }
   bool isAlive() const                { return alive;                 } 
   ~FlyingObject();
};



#endif /* flyingObject_h */
