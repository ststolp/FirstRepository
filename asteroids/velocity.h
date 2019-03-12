#ifndef VELOCITY_H
#define VELOCITY_H


// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project
class Velocity
{
  private:
   float dx;
   float dy;
  public:
   Velocity();
   Velocity(int dx, int dy);
   float getDy() const {return dy;  }
   float getDx() const {return dx;  }
   void setDy(float dy) { this -> dy = dy;   }
   void setDx(float dx) { this -> dx = dx;   }
};

#endif /* velocity_h */
