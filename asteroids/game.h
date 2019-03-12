/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H
#include "flyingObject.h"
#include "uiInteract.h"
#include "ship.h"
#include "bullet.h"
#include "rocks.h"
#include <vector>
#include <list>
class Game
{
  private:
   Velocity velocities[4];
   Ship ship;
   Ball ball;
   Ball ball2;
   Blast blast;
   int score;
   int level;
   int highScore;
   Ship ships[3];
   Point topLeft;
   bool blastAlive;
   Point bottomRight;
   std::vector <LargeAsteroid> lRocks;
   std::vector <MediumAsteroid> mRocks;
   std::vector <SmallAsteroid> sRocks;
   int lives;
   static bool isNextLevel;
   static bool gameIsOver;
  public:
   int getLives() const            { return lives;                }
   void setIsNextLevel(bool level) { this -> isNextLevel = level; }
   void setGameIsOver(bool game) { this ->gameIsOver = game;    }
   bool getIsNextLevel() const   { return isNextLevel;          }
   bool getGameIsOver() const    { return gameIsOver;           }
   int getScore() const          { return score;                }
   int setLives(int lives)       { this ->lives = lives;        }
   void setScore(int score)      { this -> score = score;       }
   void setHighScore(int hScore) { this -> highScore = hScore;  }
   int getHighScore() const      { return highScore;            }
   void setLevel(int level)      { this -> level = level;       }
   int getLevel() const          { return level;                }
   void endLevel();
   static bool check;
   static bool check2;
   void newLevel();
   void setBlast(bool blast) { this -> blastAlive = blast;    }
   void drawScore();
   bool blastIsAlive()       { return blastAlive;             }
   void drawGameOver();
   void nextLevelScreen();
   void newGame();
   void endGame() { setGameIsOver(true);
     check = true;     }
   std::vector <Bullet> bullets;
   Game(Point t1, Point br);
   ~Game();
   void advanceBullets();
   void advanceShip();
   void advanceAsteroids();
   void handleCollisions();
   void cleanUpZombies();
   float getClosestDistance(const FlyingObject &obj1,
                            const FlyingObject &obj2) const;
void advance();
void handleInput(const Interface &pUI);
void draw(const Interface & pUI);
};

#endif /* GAME_H */
