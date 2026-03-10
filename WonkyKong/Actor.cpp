#include "Actor.h"
#include "StudentWorld.h"
#include "Level.h"
//#include "SoundFX.h"
#include <cmath>

using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : GraphObject(imageID, startX, startY, startDirection), aliveStatus(true), world(worl), tracker(lev) {
    
}
void Actor::doSomething() {
    
    
}
Actor::~Actor() {
    
}
bool Actor::playerHere() {
    return (getX() == getWorld()->getPlayer()->getX() && getY() == getWorld()->getPlayer()->getY());
}
Player::Player(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Actor(imageID, startX, startY, startDirection = right, worl, lev)  {
    
    lives = 3;
    burps = 0;
    dir = right;
}
Floor::Floor(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Actor(imageID, startX, startY, startDirection = none, worl, lev)  {

}
Ladder::Ladder(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Actor(imageID, startX, startY, startDirection = none, worl, lev)  {

}
Kong::Kong(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Actor(imageID, startX, startY, startDirection, worl, lev)  {

}
Burp::Burp(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Actor(imageID, startX, startY, startDirection, worl, lev)  {

}
Bonfire::Bonfire(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Actor(imageID, startX, startY, startDirection = none, worl, lev)  {

}
GarlicGoodie::GarlicGoodie(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Goodie(imageID, startX, startY, startDirection = none, worl, lev)  {

}
Goodie::Goodie(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Actor(imageID, startX, startY, startDirection = none, worl, lev)  {

}
Barrel::Barrel(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Villain(imageID, startX, startY, startDirection, worl, lev)  {

}
ExtraLifeGoodie::ExtraLifeGoodie(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Goodie(imageID, startX, startY, startDirection = none, worl, lev)  {

}
Villain::Villain(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Actor(imageID, startX, startY, startDirection, worl, lev) {
    
}
Koopa::Koopa(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Villain(imageID, startX, startY, randDirection(), worl, lev)  {

}
int Villain::randDirection() {
    if(randInt(1, 2) == 1) { //generates random direction
        return left;
    }
    return right;
}
void Villain::isAttacked() {
    killObject();
    getWorld()->playSound(SOUND_ENEMY_DIE); //when a villain is attakced we want it to die
    getWorld()->increaseScore(100);
    doDifferent();
}
void Fireball::doDifferent() {
    int x = randInt(1, 3); //if fireball dies could add garlic goodie
    if(x == 1) {
        getWorld()->addGarlicGoodie(getX(), getY(), getDirection(), getWorld(), getLevel());
    }
}
void Koopa::doDifferent() { //if koopa dies could drop extra life
    int x = randInt(1, 3);
    if(x == 1) {
        getWorld()->addExtraLifeGoodie(getX(), getY(), getDirection(), getWorld(), getLevel());
    }
}
//void Barrel::doDifferent() {
//    int x = randInt(1, 3);
//    if(x == 1) {
//        getWorld()->addExtraLifeGoodie(getX(), getY(), getDirection(), getWorld(), getLevel());
//    }
//}

void Villain::menacingWalk() { //walk back and fourth over ladders
    int dir;
    if(getDirection() == left) {
        dir = -1;
    }
    else {
        dir = 1;
    }
    if(tenTicks == 10) {
        tenTicks = 0;
        if(getLevel().getContentsOf(getX()+dir, getY()) == Level::floor ||  (getLevel().getContentsOf(getX()+dir, getY()-1) != Level::floor && getLevel().getContentsOf(getX()+dir, getY()-1) != Level::ladder)) {
            if(getDirection() == left)
                setDirection(right);
            else
                setDirection(left);
            return;
        }
        moveTo(getX()+dir, getY());
    }
}
void Villain::menacingRoll() {
    int dir;
    if(getDirection() == left) {
        dir = -1;
    }
    else {
        dir = 1;
    } //has the barrel roll
    if(tenTicks == 10) {
        destroyTicks();
        if(getLevel().getContentsOf(getX()+dir, getY()) == Level::floor) {
            if(getDirection() == left)
                setDirection(right); //changes direction when hits ground
            else
                setDirection(left);
            return;
        }
        moveTo(getX()+dir, getY());
    }
}
void Kong::doSomething() {
    barrelTime++;
    
    numTicks++;
    if(isAlive() == false) {
        return;
    }
    
    increaseAnimationNumber(); //uses formula to determine kong distance from player
    int a = std::sqrt(std::pow(getX() - getWorld()->getPlayer()->getX(), 2) + std::pow(getY() - getWorld()->getPlayer()->getY(), 2));
    if(a <= 2) { //if near player kong must flee
        fleeingState = true;
    }
    int dir;
    if(getDirection() == left) {

        dir = -1;
    }
    else {

        dir = 1;
    }
    if(fleeingState == false && barrelTime == max(200 - 50 * getWorld()->getLevel(), 50)) { //if can summon barrel then summon barrel
        barrelTime = 0;
        getWorld()->addBarrel(getX()+dir, getY(), getDirection(), getWorld(), getLevel());
    }
    if(numTicks == 5) {
        numTicks = 0;
        if(fleeingState) { //this is when kong dies
            moveTo(getX(), getY()+1);
            if(getLevel().getContentsOf(getX(), getY()) == Level::empty) {
                getWorld()->increaseScore(1000);
                getWorld()->playSound(SOUND_FINISHED_LEVEL);
                getWorld()->kongDead();
            }
        }
    }
}
//    if(numTicks == n) {
//    if(fleeingState == false && )
//    
//}
//simulates if player attacked, wants to lose life and kill it
void Player::isAttacked() {getWorld()->decLives(); getWorld()->playSound(SOUND_PLAYER_DIE); killObject();}
void Barrel::doSomething() {
    incrementTicks();
    if(isAlive() == false) {
        return;
    }
    //when the player is same square as barrel attack it
    if(playerHere()) {
        getWorld()->getPlayer()->isAttacked();
        return;
    }
    if(getLevel().getContentsOf(getX(), getY()) == Level::bonfire) { //when same square as bonfire barrel dies
        killObject();
        return;
    }
    if(getLevel().getContentsOf(getX(), getY()-1) != Level::floor) { //simulate barrel following until hits floor and then changes direction
        moveTo(getX(), getY()-1);
        if(getLevel().getContentsOf(getX(), getY()-1) == Level::floor) {
            if(getDirection() == right) {
                setDirection(left);
            }
            else {
                setDirection(right);
            }
        }
    }
    menacingRoll();
    if(playerHere()) {
        getWorld()->getPlayer()->isAttacked();
        return;
    }
    
}

void Barrel::doDifferent() {}

Fireball::Fireball(int imageID, int startX, int startY, int startDirection, StudentWorld* worl, Level lev) : Villain(imageID, startX, startY, randDirection(), worl, lev)  {

}

void Burp::doSomething() {

    if(isAlive() == false) {
        return;
    }
    lifeTicks--;
    if(lifeTicks == 0) {
        killObject();
        return;
    }
    //this gets the villain for the barrel that it is attacking and then kills it
    Actor* temp = getWorld()->getVillain(getX(), getY());
    if(temp != nullptr) {
        temp->isAttacked();
    }
    
    
}
void Fireball::doSomething() {

    int skipper = 0;
    if(isAlive() == false) {
        return;
    }
    //kills plater if same square as fireball
    if(playerHere()) {
        
        getWorld()->getPlayer()->isAttacked();
        return;
    }
    incrementTicks();
    if(getTicks() == 10) {
        int x = randInt(1, 3);
        //sometimes the fireball will climb up the ladder
        if(getLevel().getContentsOf(getX(), getY()) == Level::ladder && getLevel().getContentsOf(getX(), getY()+1) != Level::floor && climbingDown == false) {
            if(climbingUp || x == 1) {
                climbingUp = true;
                moveTo(getX(), getY()+1);
                skipper = 1;
            }
        }
        //sometimes fireball will climb down the ladder
        else if(getLevel().getContentsOf(getX(), getY()-1) == Level::ladder && climbingUp == false) {
            x = randInt(1, 3);
            if(climbingDown || x == 1) {
                climbingDown = true;
                moveTo(getX(), getY()-1);
                skipper = 1;
                
            }
        }
        if(climbingUp == true && skipper != 1) {
            if(getLevel().getContentsOf(getX(), getY()+1) != Level::ladder || getLevel().getContentsOf(getX(), getY()+1) == Level::floor) {
                climbingUp = false;
            }
        }
        if(climbingDown == true && skipper != 1) {
            if(getLevel().getContentsOf(getX(), getY()-1) != Level::ladder || getLevel().getContentsOf(getX(), getY()-1) == Level::floor) {
                climbingDown = false;
            }
        }

        //when fireball reaches ground it wants to just start walking

        if(skipper != 1) {
            menacingWalk();
        }
        if(playerHere()) {
            getWorld()->getPlayer()->isAttacked();
        }
        destroyTicks();
        
    }
}
//kills player if on bonfire
void Bonfire::doSomething() {
    increaseAnimationNumber();
    if(playerHere()) {
        getWorld()->getPlayer()->isAttacked();
    }
}
//controls what all goodies do, die when collected
void Goodie::doSomething() {
    if(isAlive() == false) {
        return;
    }
    if(playerHere()) {
        doDifferent();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        killObject();
    }
}
//garlic specficially gives points and burps
void GarlicGoodie::doDifferent() {
    getWorld()->increaseScore(25);
    getWorld()->getPlayer()->giveBurps();
//    if(isAlive() == false) {
//        return;
//    }
//    
//    if(getX() == getWorld()->getPlayer()->getX() && getY() == getWorld()->getPlayer()->getY()) {
        
//     //   givePower(Player player);
//        getWorld()->playSound(SOUND_GOT_GOODIE);
//
//        killObject();
    }
//extralife goodies specifically give 50 points and increase lives 
void ExtraLifeGoodie::doDifferent() {
    getWorld()->increaseScore(50);
    getWorld()->incLives();
//    if(isAlive() == false) {
//        return;
//    }
    
//    if(getX() == getWorld()->getPlayer()->getX() && getY() == getWorld()->getPlayer()->getY()) {

//        getWorld()->playSound(SOUND_GOT_GOODIE);
//     //   givePower(Player player);
//        killObject();
//       // getWorld()->getPlayer()->giveLife();
//    }
}
void Koopa::doSomething() {
    
    if(isAlive() == false) {

        return;
    }
    //if the koopa finds the plater freeze the player and make sure koopa doesnt keep freezing it in a row
    if(playerHere()) {
        if(freezeTimer == 0) {
            freezeTimer = 50;
            getWorld()->getPlayer()->freeze();
            return;
        }
    }
    incrementTicks();
    if(freezeTimer > 0) {
        freezeTimer--;
    }

//if ticks/10 then do the menacing walk and then if player is there freeze it
    if(getTicks() == 10) {

        menacingWalk();
        koopaTime--;
        if(koopaTime == 0) {
            koopaTime = 10;
            if(playerHere()) {
                if(freezeTimer == 0) {
                    freezeTimer = 50;
                    getWorld()->getPlayer()->freeze();
                    
                    return;
                }
            }
        }
    }
    
}
void Koopa::power() {
    if(playerHere() && freezeTimer == 0) {
        getWorld()->getPlayer()->freeze();
        freezeTimer = 50;
        return;
    }
}
//void Player::increaseBurps(int burp) {
//    
//    burps += burps;
//}
void Player::doSomething()
{

    if(isAlive() == false) {
        return;
    }
    
    int dir;
    //finds directiion player is facing to know which square it wants to move to
    if(getDirection() == left) {
        dir = -1;
    }
    else {
        dir = 1;
    } //note: inefficent code, needs to be fixed 
    //            if(getLevel().getContentsOf(getX()+dir, getY()) == Level::empty || getLevel().getContentsOf(getX()+dir, getY()) == Level::ladder || getLevel().getContentsOf(getX()+dir, getY()) == Level::koopa) {
    //jump has 4 stages, it checks if it can move there, moves horiziontally 3 spaces
    switch(jumping) {
        case(1): {
            if(getLevel().getContentsOf(getX()+dir, getY()) != Level::floor) {

                moveTo(getX()+dir, getY());
            }
            if(getLevel().getContentsOf(getX(), getY()) == Level::ladder) {
                jumping = 0;
                return;
            }
            jumping++;
            break;
        }
        case(2): {
            if(getLevel().getContentsOf(getX()+dir, getY()) != Level::floor) {

                moveTo(getX()+dir, getY());
            }
            if(getLevel().getContentsOf(getX(), getY()) == Level::ladder) {
                jumping = 0;
                return;
            }
            jumping++;
            break;
        }
        case(3): {

            if(getLevel().getContentsOf(getX()+dir, getY()) != Level::floor/*getLevel().getContentsOf(getX()+dir, getY()) == Level::empty || getLevel().getContentsOf(getX()+dir, getY()) == Level::ladder|| getLevel().getContentsOf(getX()+dir, getY()) == Level::koopa*/) {

                moveTo(getX()+dir, getY());
            }
            if(getLevel().getContentsOf(getX(), getY()) == Level::ladder) {
                jumping = 0;
                return;
            }

            jumping = 0;
            return;
            break;
        }
    }
    if(jumping != 0) {
        return;
    }
    //if the polayer is frozen or in a jump phase don't move
    if(frozen == true) {
        frozenSeconds--;
        if(frozenSeconds <= 0) {
            frozenSeconds = 50;
            frozen = false;
        }
        return;
    }
    
    
    if(getLevel().getContentsOf(getX(), getY()-1) != Level::floor && getLevel().getContentsOf(getX(), getY()-1) != Level::ladder
       && getLevel().getContentsOf(getX(), getY()) != Level::ladder) {

        moveTo(getX(), getY()-1);
        return;
        
    }
int ch;
if (getWorld()->getKey(ch))
{
// user hit a key this tick!
switch (ch)
{
case KEY_PRESS_LEFT:
        

        if(getDirection() != left) {
            setDirection(left);
            break;
        }
        
        //make sure moving that way is valid (there is not a floor there)
        if(getLevel().getContentsOf(getX()-1, getY()) == Level::floor) {
            break;
        }
        moveTo(getX()-1, getY());

break;
case KEY_PRESS_RIGHT:
        if(getDirection() != right) {
            setDirection(right);
            break;
        }
        //make sure moving that way is valid (there is not a floor there)
        if(getLevel().getContentsOf(getX()+1, getY()) == Level::floor) {
            break;
        }

        moveTo(getX()+1, getY());

break;
    case KEY_PRESS_DOWN: {
        //checks if there is a ladder that would allow palyer to move down
        if(getLevel().getContentsOf(getX(), getY()-1) == Level::ladder || getLevel().getContentsOf(getX(), getY()-1) == Level::empty/* && getLevel().getContentsOf(getX(), getY()-1) != Level::floor)|| getLevel().getContentsOf(getX(), getY()-1) == Level::ladder*/) {
            moveTo(getX(), getY()-1);

        }
        break;
    }
        //press up and move up if there is a lladder to be moved up -
    case KEY_PRESS_UP: {
        if(getLevel().getContentsOf(getX(), getY()) == Level::ladder && getLevel().getContentsOf(getX(), getY()) != Level::floor && getLevel().getContentsOf(getX(), getY()+1) != Level::floor) {
            moveTo(getX(), getY()+1);
        }
        break;
    }
        //move up if can move up and begin jump phase by setting it to 1
    case KEY_PRESS_SPACE: {
        getWorld()->playSound(SOUND_JUMP);
        if(getLevel().getContentsOf(getX(), getY()+1) == Level::floor) {
            return;
        }
        //getLevel().getContentsOf(getX(), getY()-1) != Level::ladder
        if(getLevel().getContentsOf(getX(), getY()+1) == Level::ladder) {
            moveTo(getX(), getY()+1);
            return;
        }
        
        jumping++;
        moveTo(getX(), getY()+1);
        break;
    }
case KEY_PRESS_TAB:
        //add burp to the world and then plater lovses a burp
        
        
        
        if(burps > 0) {
            getWorld()->playSound(SOUND_BURP);
            getWorld()->addBurp(getX()+dir, getY(), getDirection(), getWorld(), getLevel());
            burps--;
        }
break;

}
}

}
