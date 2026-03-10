
#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp


StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    livesLeft = 3;
}
StudentWorld::~StudentWorld() {
    cleanUp();
}
//void StudentWorld::simulateAttack(Actor* act) {
//    
//}
int StudentWorld::init()
{
    int y = 0;
    Level lev(assetPath());
//    if(getLevel() > tracker) {
//
//    }
//    tracker = 4;

        ostringstream levelStream; //level stream
        levelStream << "level" << setw(2) << setfill('0') << tracker << ".txt"; //fills it with 0s
        std::string levelFile = levelStream.str(); //convert to string
//        levelFile = "level" + to_string(y) + "" + to_string(tracker) + ".txt";
//    levelFile = "level" + to_string(y) + "" + to_string(tracker) + ".txt";
//    if(gameStatus == 50) {
//        tracker++;
//    }
    Level::LoadResult result = lev.loadLevel(levelFile); //load level
    
   //if there is no next level to load the plater won
    if (result == Level::load_fail_file_not_found || result == Level::load_fail_bad_format) {
        return GWSTATUS_PLAYER_WON;
    } //if level not found then player won
    else if (result == Level::load_success)
    {
        for(int i = 0; i < 20; i++) {
            for(int k = 0; k < 20; k++) {
                
                Level::MazeEntry me = lev.getContentsOf(i,k); // x=5, y=10
                switch (me)
                { //adds add of our players to the screen to this world
                    case Level::player: {
                        
                        Player* players = new Player(IID_PLAYER, i, k, 0, this, lev);
                        playerPointer = players;
                        actors.push_back(players);
                        break;
                    }
                    case Level::floor: {
                        Actor* floors = new Floor(IID_FLOOR, i, k, 0, this, lev);
                        actors.push_back(floors);
                        break;
                    }
                    case Level::garlic: {
                        Actor* garlicGoodie = new GarlicGoodie(IID_GARLIC_GOODIE, i, k, 0, this, lev);
                        actors.push_back(garlicGoodie);
                        break;
                    }
                    case Level::extra_life: {
                        ExtraLifeGoodie* extraLifeGoodie = new ExtraLifeGoodie(IID_EXTRA_LIFE_GOODIE, i, k, 0, this, lev);
                        actors.push_back(extraLifeGoodie);
                        break;
                    }
                    case Level::ladder: {
                        Actor* ladder = new Ladder(IID_LADDER, i, k, 0, this, lev);
                        actors.push_back(ladder);
                        break;
                    }
                    case Level::left_kong: {
                        Actor* leftKong = new Kong(IID_KONG, i, k, 180, this, lev);
                        actors.push_back(leftKong);
                        break;
                    }
                    case Level::right_kong: {
                        Actor* rightKong = new Kong(IID_KONG, i, k, 0, this, lev);
                        actors.push_back(rightKong);
                        break;
                    }
                    case Level::fireball: {
                        Fireball* fireball = new Fireball(IID_FIREBALL, i, k, 0, this, lev);
                        actors.push_back(fireball);
                        break;
                    }
                    case Level::bonfire: {
                        Bonfire* bonfire = new Bonfire(IID_BONFIRE, i, k, 0, this, lev);
                        actors.push_back(bonfire);
                        break;
                    }
                    case Level::koopa: {
                        Koopa* koopa = new Koopa(IID_KOOPA, i, k, 0, this, lev);
                        actors.push_back(koopa);
                        break;
                    }

                    case Level::empty:
                        break;
                }

            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}
//these functions ensure that things are created in the world properly and added to the stack
void StudentWorld::addBurp(int i, int k, int dir, StudentWorld* world, Level lev) {
    Burp* burp = new Burp(IID_BURP, i, k, dir, world, lev);
    actors.push_back(burp);
}
void StudentWorld::addGarlicGoodie(int i, int k, int dir, StudentWorld* world, Level lev) {
    GarlicGoodie* garlicGoodie = new GarlicGoodie(IID_BURP, i, k, dir, world, lev);
    actors.push_back(garlicGoodie);
}
void StudentWorld::addExtraLifeGoodie(int i, int k, int dir, StudentWorld* world, Level lev) {
    ExtraLifeGoodie* extraLifeGoodie = new ExtraLifeGoodie(IID_EXTRA_LIFE_GOODIE, i, k, dir, world, lev);
    actors.push_back(extraLifeGoodie);
}
void StudentWorld::addBarrel(int i, int k, int dir, StudentWorld* world, Level lev) {
    Barrel* barrel = new Barrel(IID_BARREL, i, k, dir, world, lev);
    actors.push_back(barrel);
}
//this handles the finding of the villain
Actor* StudentWorld::getVillain(int x, int y) {
    for(vector<Actor*>::iterator q = actors.begin(); q != actors.end(); q++) {
        if((*q)->isVillain() == true && (*q)->getX() == x && (*q)->getY() == y) {
            return (*q);
        }
    }
    return nullptr;
}
//when kong dies we want to know to advance to next level
void StudentWorld::kongDead() {
    gameStatus = 50;
}
int StudentWorld::move()
{
    
    int score = getScore();
    int level = getLevel();
    int lives = getLives();
//intitiates score board with lves, level, burps score
    int burps = playerPointer->numBurps();
    ostringstream display;
    display << "Score: " << setw(7) << setfill('0') << score << " Level: " << setw(2) << setfill('0') << level << " Lives: " << setw(2) << setfill('0') << lives << " Burps: " << setw(2) << setfill('0') << burps;
    string s = display.str();
    setGameStatText(s);
    // This code is here merely to allow the game to build, run, and terminate after you type q
 //   int i = 0;
    for(vector<Actor*>::iterator q = actors.begin(); q != actors.end();) {
        if(playerPointer->isAlive() == false) {
            return GWSTATUS_PLAYER_DIED;
        }
        
        if(gameStatus == 50) {
            tracker++;
            gameStatus = 10;
            return GWSTATUS_FINISHED_LEVEL;
        }
        //for(int k = 0; k < actors.size(); k++) {
        //call dosomething on all of our actors to do somethign during tick
            (*q)->doSomething();

//            if(actors.at(k)->isAlive() == false) {
        //when an actor dies we want to remove it from the array using an iterator
        if((*q)->isAlive() == false) {

            delete (*q);
            q = actors.erase(q);
            

            }
        else {
            q++;
        }

      //      i++;
    //    }
        
    }
  //      setGameStatText("Game will end when you type q");
        //assuming game is not finished continue the game
        return GWSTATUS_CONTINUE_GAME;
    }


void StudentWorld::cleanUp()
{
    //delete all actors 
    for (Actor* actor : actors) {
        delete actor;
    }
    actors.clear();
    
}
