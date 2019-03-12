/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
#include <cmath>
#include "uiDraw.h"
#include "point.h"
#include "velocity.h"
#include "ship.h"
#include "rocks.h"
#include "bullet.h"
using namespace std;

/******************************************************
 * Function: Game
 * Description: Create a ship, fill the vector of rock
 * pointers with five large rocks.
 *************************************************************/
Game :: Game(Point t1, Point br)
      : topLeft(t1), bottomRight(br)
{
   setLevel(0);
   ball.setAlive(false);
   ball2.setAlive(false);
   setScore(0);
   setBlast(false);
   setHighScore(0);
   Velocity velocity(1, 1);
   Velocity velocity1(-1, -1);
   Velocity velocity2(-1, 1);
   Velocity velocity3(1, -1);
   velocities[0] = velocity;
   velocities[1] = velocity1;
   velocities[2] = velocity2;
   velocities[3] = velocity3;
   Ship ship1(-190, -190);
   Ship ship2(-175, -190);
   Ship ship3(-160, -190);
   ships[0] = ship1;
   ships[1] = ship2;
   ships[2] = ship3;
   newLevel();
}

/*************************************************************
 * Function: newLevel
 * Description: Makes more rocks with random positions
 * than the previous level.
 ******************************************************************/
void Game :: newLevel()
{
   setIsNextLevel(false);
   blast.setAlive(false);
   setLevel(getLevel() + 1);
   if (getLevel() > 4)
     ball.setAlive(true);
   if (getLevel() > 9)
     ball2.setAlive(true);
   int b = 0;
   for (int i = 0; i < getLevel() + 4; i++)
   {
      Point point(random(-200, 201), random(-200, 201));
      LargeAsteroid rock(velocities[b], point);
      lRocks.push_back(rock);
      b++;
      if (b > 3)
         b = 0;
   }
   setLives(3);
   ship.setPoint(0, 0);
}

/**********************************************************
 * Function: nextLevelScreen
 * Description: Lets user know it's a new level with
 * the score and the high score
/*********************************************************/
void Game ::  nextLevelScreen()
{
   Point Pos(0, 0);
   Point line1(-90, 40);
   Point line2(-90, 40);
   Point line3(-95, -45);
   Point num(-55, 49);
   drawRect(Pos, 200, 100, 0);
   drawText(line1, "Level");
   drawText(line2, "               cleared!!");
   drawText(line3, "Press down arrow to play next level");
   drawNumber(num, getLevel());
}

/****************************************************************
 * Function: drawGameOver
 * Description: tells the user the game is over with his score
 * and the high score. Asks to play a new game.
 ******************************************************************/
void Game :: drawGameOver()
{
   Point rect(0, 0);
   Point line1(-50, 40);
   Point line2(-90, 20);
   Point line3(-90, 0);
   Point line4(-90, -20);
   Point line5(-90, -40);
   Point line6(-90, -60);
   Point num1(20, 30);
   Point num2(10, 10);
   Point num3(10, -10);
   if (getGameIsOver())
     {
       
   drawRect(rect, 200, 200, 0);
   drawText(line1, "GAME OVER");
   drawText(line2, "Levels Completed:");
   drawText(line3, "Your Score:");
   drawText(line4, "High Score:");
   drawText(line5, "Press the down arrow key to");
   drawText(line6, "play again");
   drawNumber(num1, getLevel());
   drawNumber(num2, getScore());
   drawNumber(num3, getHighScore());
}
}
/***************************************************************
 * Function: newGame
 * Description: Clears the game.
 ***************************************************************/
void Game :: newGame()
{
   for (vector <LargeAsteroid> :: iterator a = lRocks.begin();
	a != lRocks.end();)
      a = lRocks.erase(a);
   for (vector <MediumAsteroid> :: iterator b = mRocks.begin();
	b != mRocks.end();)
     b = mRocks.erase(b);
   for (vector <SmallAsteroid> :: iterator c = sRocks.begin();
	c != sRocks.end();)
     c = sRocks.erase(c);
   setGameIsOver(false);
   setScore(0);
   setLevel(0);
   newLevel();
}

/***************************************************************
 * Function: drawScore
 * Description: Draws score on screen
 *****************************************************************/
void Game :: drawScore()
{
   Point point(-190, 190);
   Point point2(-150, 199);
   Point point3(130, 190);
   Point point4(180,199);
   drawNumber(point2, getScore());
   drawText(point, "Score:");
   drawText(point3, "Level:");
   drawNumber(point4, getLevel());
}

/****************************************************************
 * Function: endLevel
 * Description: Frees all memory from the previous level.
 *********************************************************/
void Game :: endLevel()
{
   setIsNextLevel(true);
}
 
/***********************************************************
 * Function: ~Game
 * Description: Before the game closes, makes sure all allocated memory
 * is freed.
 *************************************************************/
Game :: ~Game()
{
   for (vector<Bullet> :: iterator it = bullets.begin(); it != bullets.end();)
         it = bullets.erase(it);
   for (vector<LargeAsteroid> :: iterator it = lRocks.begin();
	it != lRocks.end();)
      it = lRocks.erase(it);
   for (vector<MediumAsteroid> :: iterator it = mRocks.begin();
	it != mRocks.end();)
     it = mRocks.erase(it);
   for (vector<SmallAsteroid> :: iterator it = sRocks.begin();
	it != sRocks.end();)
     it = sRocks.erase(it);
}

bool Game :: isNextLevel = false;
bool Game :: gameIsOver = false;

/****************************************************************************
 * Funciotn: getClosestDistance
 * Description: Checks how close the two objects are between two frames.
 *****************************************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
    dMax = max(dMax, abs(obj2.getVelocity().getDy()));
    dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }

   return sqrt(distMin);
}

/*************************************************************
 * Function: draw
 * Description: Loops through all the array for valid pointers to objects
 * and draws them.
 **********************************************************/
void Game :: draw(const Interface &pUI)
{
  if (ship.isAlive() && getLives() > 0)
      ship.draw();
   for (vector <Bullet> :: iterator it = bullets.begin();
        it != bullets.end();)
   {
      Bullet bullet = *it;
       bullet.draw();
       it++;
   }
   for (vector <LargeAsteroid> :: iterator a = lRocks.begin();
	a != lRocks.end();)
     {
       LargeAsteroid rock = *a;
       rock.draw();
       a++;
     }
   for (vector <MediumAsteroid> :: iterator b = mRocks.begin();
	b != mRocks.end();)
     {
       MediumAsteroid rock = *b;
       rock.draw();
       b++;
     }
   for (vector <SmallAsteroid> :: iterator c = sRocks.begin();
	c != sRocks.end(); c++)
     {
       SmallAsteroid rock = *c;
       rock.draw();
     }
   for (int i = 0; i < getLives(); i++)
      ships[i].draw();
   if (getIsNextLevel())
      nextLevelScreen();
   if (getGameIsOver())
      drawGameOver();
   drawScore();
  if (ball.isAlive())
      ball.draw();
  if (blast.isAlive())
    blast.draw();
  if (ball2.isAlive())
    ball2.draw();
}

/******************************************************************
 * Function: advance
 * Description: Advance calls other advance functions to move all the objects
 * in the game.
 ******************************************************************/
void Game :: advance()
{
   advanceShip();
   advanceBullets();
   advanceAsteroids();
   handleCollisions();
   cleanUpZombies();
}

/*********************************************************
 * Function: advanceShip
 * Description: Advances the ship if it is alive and
 * doesn't point to null.
 *****************************************************/
void Game :: advanceShip()
{
  if (ship.isAlive() && getLives() > 0)
      ship.advance();
}

/**********************************************
 * Function: advanceBullets
 * Description: move bullets forward if they are
 * valid.
 ***********************************************/
void Game :: advanceBullets()
{
   for (vector <Bullet> :: iterator it = bullets.begin();
        it != bullets.end(); it++)
   {
      Bullet bullet = *it;
         bullet.advance();
	 *it = bullet;
   }
   if (ball.isAlive())
     ball.advance();
   if (blast.isAlive())
     blast.advance();
   if (ball2.isAlive())
     ball2.advance();
}

/**************************************************************************
 * Function: advanceAsteroids
 * Description: advance asteroids foreward if they are valid.
 ***************************************************************/
void Game :: advanceAsteroids()
{
  for (vector<LargeAsteroid> :: iterator it = lRocks.begin();
       it != lRocks.end(); it++)
    {
      LargeAsteroid pRock = *it;
      if (pRock.isAlive())
        {
	  pRock.advance();
         *it = pRock;
	}
    }
  for (vector <MediumAsteroid> :: iterator a = mRocks.begin();
       a != mRocks.end(); a++)
    {
      MediumAsteroid rock = *a;
      if (rock.isAlive())
	{
	  rock.advance();
         *a = rock;
	}
    }
  for (vector <SmallAsteroid> :: iterator c = sRocks.begin();
       c != sRocks.end(); c++)
    {
      SmallAsteroid rock = *c;
      if (rock.isAlive())
	{
	  rock.advance();
          *c = rock;
	}
    }
}

/*************************************************************************
 * Function cleanUpZombies
 * Description: frees all allocated memory if the various object pointers
 * point to null;
 ***********************************************************************/
void Game :: cleanUpZombies()
{
   vector <Bullet> :: iterator it = bullets.begin();
   while (it != bullets.end())
   {
      Bullet bullet = *it;
      if (!bullet.isAlive())
         it = bullets.erase(it);
      else
         it++;
   }
   if (!ship.isAlive())
   {
     if (getLives() > 0)
         ship.setAlive(true);
     else
       {
	 ship.setAlive(true);
	 endGame();
       }
   }
   for (vector <LargeAsteroid> :: iterator it = lRocks.begin();
	it != lRocks.end();)
   {
      LargeAsteroid rock = *it;
      if (!rock.isAlive())
         it = lRocks.erase(it);
      else
         it++;
   }
   for (vector<MediumAsteroid> :: iterator it = mRocks.begin();
	it != mRocks.end();)
     {
       MediumAsteroid rock = *it;
       if (!rock.isAlive())
	 it = mRocks.erase(it);
       else
	 it++;
     }
   for (vector<SmallAsteroid> :: iterator it = sRocks.begin();
	it != sRocks.end();)
     {
       SmallAsteroid rock = *it;
       if (!rock.isAlive())
	 it = sRocks.erase(it);
       else
	 it++;
     }
}

/*********************************************************
 * Function :: handleCollisions
 * Description: Checks if a bullet has collided with a rock or
 * if a rock has collided with the ship and calls the kill functions
 * of both objects.
 *********************************************************************/
void Game :: handleCollisions()
{
  bool check = true;
      for (vector<Bullet> :: iterator it = bullets.begin();
        it != bullets.end(); it++)
   {
     Bullet bullet = *it;
     for (vector <LargeAsteroid> :: iterator b = lRocks.begin();
	  b != lRocks.end(); b++)
      {
	 LargeAsteroid pRock = *b;
         if (pRock.isAlive() && bullet.isAlive() && getLives() > 0)
         {
                  if (getClosestDistance(pRock, bullet) < 16)
                        {
                           setScore(getScore() + 3);
                           bullet.kill();
			   *it = bullet;
                           pRock.hit();
			   *b = pRock;
                           Velocity velocity(pRock.getVelocity().getDx(),
                                              pRock.getVelocity().getDy()
                                              + 1);
                           MediumAsteroid medium1(velocity,
                                                  pRock.getPoint());
                           Velocity velocity2(pRock.getVelocity().getDx(),
                                                   pRock.getVelocity().getDy() - 1);
                           MediumAsteroid medium2(velocity2, pRock.getPoint());
                           Velocity velocity3(pRock.getVelocity().getDx(),
                                                   pRock.getVelocity().getDy() + 2);
                           SmallAsteroid small(velocity3, pRock.getPoint());
                           mRocks.push_back(medium1);
                           mRocks.push_back(medium2);
                           sRocks.push_back(small);
                        }
	 }
      }
     for (vector<MediumAsteroid> :: iterator b = mRocks.begin();
	  b != mRocks.end(); b++)
       {
	 MediumAsteroid pRock = *b;
	 if (pRock.isAlive() && bullet.isAlive() && getLives() > 0)
	   {
	     if (getClosestDistance(pRock, bullet) < 8)
                       {
                           bullet.kill();
			   *it = bullet;
                           setScore(getScore() + 2);
                           pRock.hit();
			   pRock.kill();
			   *b = pRock;
                           Velocity velocity1(pRock.getVelocity().getDx()
                                              + 3,
                                           pRock.getVelocity().getDy());
                           SmallAsteroid small(velocity1,
                                               pRock.getPoint());
                           Velocity velocity2(pRock.getVelocity().getDx()
                                              - 6,
                                              pRock.getVelocity().getDy());
                           SmallAsteroid small2(velocity2,
                                                pRock.getPoint());
                           sRocks.push_back(small);
                           sRocks.push_back(small2);
                       }
	   }
       }
   for (vector<SmallAsteroid> :: iterator b = sRocks.begin();
	b != sRocks.end(); b++)
     {
       SmallAsteroid pRock = *b;
       if (pRock.isAlive() && bullet.isAlive())
	   {
	     if (getClosestDistance(pRock, bullet) < 4)
                        {
                           bullet.kill();
			   *it = bullet;
                           setScore(getScore() + 1);
                           pRock.hit();
			   *b = pRock;
                        }
	   }
     }
   if (bullet.isAlive() && ball.isAlive())
   {
      if (getClosestDistance(bullet, ball) < 10)
      {
         bullet.kill();
         *it = bullet;
         ball.kill();
         setBlast(true);
      }
   }
   if (bullet.isAlive() && ball2.isAlive())
     {
       if (getClosestDistance(bullet, ball2) < 10)
	 {
	   bullet.kill();
	   *it = bullet;
	   ball2.kill();
	   setBlast(true);
	 }
     }
   }
      if (blast.isAlive())
      {
         for (vector <LargeAsteroid> :: iterator it = lRocks.begin();
              it != lRocks.end(); it++)
         {
            LargeAsteroid pRock = *it;
            if (pRock.isAlive())
               if (getClosestDistance(pRock, blast) < 100)
               {
                  pRock.hit();
                  *it = pRock;
                  Velocity v(pRock.getVelocity().getDx(),
                             pRock.getVelocity().getDy()
                             + 1);
                  MediumAsteroid medium1(v, pRock.getPoint());
                  Velocity b(pRock.getVelocity().getDx(),
                             pRock.getVelocity().getDy()
                             - 2);
                  MediumAsteroid medium2(b, pRock.getPoint());
                  Velocity d(pRock.getVelocity().getDx() + 1,
                             pRock.getVelocity().getDy()
                             + 2);
                  SmallAsteroid small(d, pRock.getPoint());
                  mRocks.push_back(medium1);
                  mRocks.push_back(medium2);
                  setScore(getScore() + 3);
               }
         }
         for (vector <MediumAsteroid> :: iterator it = mRocks.begin();
              it != mRocks.end(); it++)
         {
            MediumAsteroid pRock = *it;
            if (pRock.isAlive())
	      if (getClosestDistance(pRock, blast) < 100)
               {
                  pRock.hit();
                  setScore(getScore() + 2);
                  *it = pRock;
                  Velocity a(pRock.getVelocity().getDx() + 3,
                             pRock.getVelocity().getDy());
                  Velocity b (pRock.getVelocity().getDx() - 6,
                              pRock.getVelocity().getDy());
                  SmallAsteroid small(a, pRock.getPoint());
                  SmallAsteroid small2(b, pRock.getPoint());
                  sRocks.push_back(small);
                  sRocks.push_back(small2);
               }
         }
         for (vector <SmallAsteroid> :: iterator it = sRocks.begin();
              it != sRocks.end(); it++)
         {
            SmallAsteroid pRock = *it;
            if (pRock.isAlive())
            {
               if (getClosestDistance(pRock, blast) < 100)
               {
                  pRock.hit();
                  *it = pRock;
                  setScore(getScore() + 1);
               }
            }
         }
      }
for (vector <LargeAsteroid> :: iterator it = lRocks.begin();
	it != lRocks.end(); it++)
      {
	LargeAsteroid pRock = *it;
	if (ship.isAlive() && pRock.isAlive() && getLives() > 0)
         {
                   if (getClosestDistance(pRock, ship) < 16)
                   {
                           ship.kill();
			   setScore(getScore() - 10);
                           setLives(getLives() - 1);
                           pRock.hit();
			   *it = pRock;
                           Velocity v(pRock.getVelocity().getDx(),
                                              pRock.getVelocity().getDy()
                                      + 1);
                           MediumAsteroid medium1(v, pRock.getPoint());
                           Velocity b(pRock.getVelocity().getDx(),
                                            pRock.getVelocity().getDy()
                                            - 2);
                           MediumAsteroid medium2(b, pRock.getPoint());
                           Velocity d(pRock.getVelocity().getDx() + 1,
                                            pRock.getVelocity().getDy()
                                            + 2);
                           SmallAsteroid small(d, pRock.getPoint());
                           mRocks.push_back(medium1);
                           mRocks.push_back(medium2);
                           sRocks.push_back(small);
		   }
	 }
      }
   for (vector<MediumAsteroid> :: iterator it = mRocks.begin();
        it != mRocks.end(); it++)
     {
       MediumAsteroid pRock = *it;
       if (pRock.isAlive() && ship.isAlive() && getLives() > 0)
     {
       if (getClosestDistance(pRock, ship) < 8)
                        {
                            ship.kill();
			    setScore(getScore() - 10);
                            setLives(getLives() - 1);
                            pRock.hit();
			    *it = pRock;
                            Velocity b(pRock.getVelocity().getDx() + 3,
                                       pRock.getVelocity().getDy());
                            SmallAsteroid small(b,pRock.getPoint());
                            Velocity a(pRock.getVelocity().getDx() - 6,
                                       pRock.getVelocity().getDy());
                            SmallAsteroid small2(a, pRock.getPoint());
                            sRocks.push_back(small);
                            sRocks.push_back(small2);
                        }
     }
     }
   for (vector<SmallAsteroid> :: iterator it = sRocks.begin();
	it != sRocks.end(); it++)
     {
       SmallAsteroid pRock = *it;
       if (pRock.isAlive() && ship.isAlive() && getLives() > 0)
	 {
                   if (getClosestDistance(pRock, ship) < 4)
                        {
                             ship.kill();
			     setScore(getScore() - 10);
                             setLives(getLives() - 1);
                             pRock.kill();
			     *it = pRock;
                        }
	 }
     }
   if (getScore() > getHighScore() && getGameIsOver())
         setHighScore(getScore());
   if ((lRocks.size() == 0) && (mRocks.size() == 0) && (sRocks.size() == 0))
	{
	  if (ship.isAlive())
    	   {
	     endLevel();
	     check2 = true; 
	   }
	}
}

/**********************************************************
 * Function handleInput
 * Description: Calls the ship to move depending on what
 * button was called if the ship is alive;
 ********************************************************/
void Game :: handleInput(const Interface &pUI)
{
   if (ship.isAlive())
   {
      if (pUI.isLeft())
         ship.moveLeft();
      if (pUI.isRight())
	ship.moveRight();
      if (pUI.isDown())
	{
	  if (check2)
	    {
	      newLevel();
	      check2 = false;
	    }
	  else if (check)
	    {
	      newGame();
	      check = false;
	    }
	}
      if (pUI.isDown() && getGameIsOver())
	newGame();
      if (pUI.isUp())
         ship.moveForeward();
      if (pUI.isSpace() && getLives() > 0)
      {
	if (getLevel() > 2)
	  {
	    Bullet bullet1;
	    Bullet bullet2;
	    Point one(ship.getPoint().getX() - 4,
		      ship.getPoint().getY() -4);
	Point two(ship.getPoint().getX() + 4,
		  ship.getPoint().getY() + 4);
	bullet1.fire(one, ship.getAngle(), ship.getVelocity().getDx(),
		     ship.getVelocity().getDy());
	bullet2.fire(two, ship.getAngle(), ship.getVelocity().getDx(),
		     ship.getVelocity().getDy());
	bullets.push_back(bullet1);
	bullets.push_back(bullet2);
	  }
      else
	{
	  Bullet newBullet;
	  newBullet.fire(ship.getPoint(),
                        ship.getAngle(),
                        ship.getVelocity().getDx(),
                        ship.getVelocity().getDy());
         bullets.push_back(newBullet);
	}
      }
      if (pUI.isSpace() && blastIsAlive())
      {
	blast.setBlast(ship.getPoint(),
		       ship.getAngle(),
		       ship.getVelocity().getDx(),
		       ship.getVelocity().getDy());
	blast.setAlive(true);
         setBlast(false);
	 }
   }
}
   bool Game :: check = false;
bool Game :: check2 = false;

