#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"

class Actor;
class Player;
class Villain;
#include <string>
#include <vector>
//#include "GraphObject.h"
using namespace std;
#endif
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
    ~StudentWorld();
  void updateScore(int amount) {score += amount;};
    Player* getPlayer(){return playerPointer;};
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    Actor* getVillain(int x, int y);
    void addBurp(int i, int k, int dir, StudentWorld* world, Level lev);
    void addGarlicGoodie(int i, int k, int dir, StudentWorld* world, Level lev);
    void addExtraLifeGoodie(int i, int k, int dir, StudentWorld* world, Level lev);
    void addBarrel(int i, int k, int dir, StudentWorld* world, Level lev);
    void kongDead();
//    void simulateAttack();


private:
    vector<Actor*> actors;
    int score = 0;
    int gameLevel;
    int livesLeft;
    int levelDigit = 0;
    int gameStatus = 20;
    Player* playerPointer; //tracks our player 
    int tracker = 0;
};

 // STUDENTWORLD_H_
