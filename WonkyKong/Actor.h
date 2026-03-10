#ifndef ACTOR_H_
#define ACTOR_H_
#include "Level.h"
#include "GraphObject.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
    Actor(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    virtual void doSomething();
    virtual ~Actor();
    StudentWorld* getWorld() {return world;};
    bool isAlive() {return aliveStatus;};
    void killObject() {aliveStatus = false;};
    Level getLevel() {return tracker;};
    virtual bool isVillain() {return false;};
    bool playerHere();
    virtual void isAttacked() {};

private:
    bool aliveStatus;
    StudentWorld* world;
    Level tracker;
    
    

    
};
class Floor : public Actor {
public:
    Floor(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
};
class Player : public Actor {
public:
    Player(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    virtual void doSomething();
//    void increaseBurps(int burps);
    void freeze(){frozen = true;};
    void isAttacked();
    void giveBurps() {burps+=5;};
    void giveLife() {lives+=1;};
    int numLives(){return lives;};
    int numBurps(){return burps;};

private:
    int jumping = 0;
    int lives = 3;
    int burps = 0;
    int dir;
    bool canJump = true;
    bool frozen = false;
    int frozenSeconds = 50;
};
class Villain : public Actor {
public:
//    virtual void doSomething();
    void menacingWalk();
    virtual void doDifferent() = 0;
    Villain(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    void incrementTicks() {tenTicks++;};
    int randDirection();
    int getTicks() {return tenTicks;};
    void isAttacked();
    virtual bool isVillain() {return true;};
    void menacingRoll();
        void destroyTicks() {
        tenTicks = 0;
    };

private:
    int tenTicks = 0;
};



class Kong : public Actor {
public:
    Kong(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    void doSomething();
private:
    int numTicks = 0;
    bool fleeingState = false;
    int barrelTime = 0;
    
//    void givePower(Player& player) {player.increaseBurps(5);};
};
class Goodie : public Actor {
public:
    Goodie(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    void doSomething();
    virtual void doDifferent() = 0; //virtual function because the different types of goodies will do different things but nothing is just a goodie 
    
};
class GarlicGoodie : public Goodie {
public:
    GarlicGoodie(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    void doDifferent();
//    void givePower(Player& player) {player.increaseBurps(5);};
};
class ExtraLifeGoodie : public Goodie {
public:
    ExtraLifeGoodie(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    void doDifferent();
//    void givePower(Player& player) {player.increaseBurps(5);};
};
class Burp : public Actor {
public:
    Burp(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    void doSomething();
private:
    int lifeTicks = 5;
//    void givePower(Player& player) {player.increaseBurps(5);};
};

class Ladder : public Actor {
public:
    Ladder(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
};

class Bonfire : public Actor {
public:
    Bonfire(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    void doSomething();
};

class Fireball : public Villain {
public:
    Fireball(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    void doSomething();
    void doDifferent();
    
private:
    bool climbingUp = false;
    bool climbingDown = false;
    
};
class Koopa : public Villain {
public:
    Koopa(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    void doSomething();
    void power();
    void doDifferent();
    
    
private:
    int koopaTime = 10;
    int freezeTimer = 0;
    
};
class Barrel : public Villain {
public:
    Barrel(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev);
    void doSomething();
    void doDifferent();

    
private:

    
};
#endif // ACTOR_H_
