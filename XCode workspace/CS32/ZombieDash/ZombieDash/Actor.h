#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class BaseActor: public GraphObject {
public:
    BaseActor(int imageID, double startX, double startY, Direction dir = 0, int depth = 0, double size = 1.0);
    virtual void doSomething() = 0;    
    
    // traits of actor
    virtual bool blocksMovement() const { return false;}
    virtual bool blocksFlame() const { return false;}
    virtual bool canExit() const { return false;}
    virtual bool isKilledByFlamePit() const { return false;}
    virtual bool canBeInfected() const { return false;}
    virtual bool explodesLM() const { return false;}
    virtual bool isPerson() const { return false;}
    virtual bool isZombie() const { return false;}
    
    // possible actions
    
    int checkAlive() const {return m_isAlive;}
    void setAlive(int newAlive) { m_isAlive = newAlive;}
    int infectionCount() const {return m_infectionCount;}
    void setInfectionCount(int next) { m_infectionCount = next;}
    bool isSaved() const { return m_saved;}
    void setSaved(bool next) { m_saved = next;}
    bool isInfected() const { return m_isInfected;}
    void setInfected(bool next) { m_isInfected = next;}
    bool isParalyzed() const { return m_isParalyzed;}
    void setParalysis(bool next) { m_isParalyzed = next;}
    StudentWorld* getWorld() const { return gw;}
    void setWorld(StudentWorld* newGW) { gw = newGW;}
    
    virtual void doWhenDead() const {};
    void checkMove(int& x, int& y, Direction dir, int moves) const;
private:
    int m_isAlive;
    bool m_isParalyzed;
    bool m_isInfected;
    int m_infectionCount;
    bool m_saved;
    StudentWorld* gw;
};

class Penelope: public BaseActor {
public:
    Penelope(int x, int y, StudentWorld* gw);
    virtual void doSomething();
    virtual bool blocksMovement() const { return true;}
    virtual bool canExit() const { return true;}
    virtual bool isKilledByFlamePit() const { return true;}
    virtual bool canBeInfected() const { return true;}
    virtual bool explodesLM() const { return true;}
    virtual bool isPerson() const { return true;}
    virtual void doWhenDead() const;
};

class Wall: public BaseActor {
public:
    Wall(int x, int y, StudentWorld* gw);
    virtual void doSomething();
    virtual bool blocksMovement() const { return true;}
    virtual bool blocksFlame() const { return true;}
};
class Exit: public BaseActor {
public:
    Exit(int x, int y, StudentWorld* gw);
    virtual void doSomething();
    virtual bool blocksFlame() const { return true;}
};
class Pit: public BaseActor {
public:
    Pit(int x, int y, StudentWorld* gw);
    virtual void doSomething();
};

class Flame: public BaseActor {
public:
    Flame(int x, int y, StudentWorld* gw, Direction dir);
    virtual void doSomething();
    void ifOverlap(int x, int y);
    virtual bool explodesLM() const { return true;}
};

class Vomit: public BaseActor {
public:
    Vomit(int x, int y, StudentWorld* gw);
    virtual void doSomething();
};

class BaseGoodie: public BaseActor {
public:
    BaseGoodie(int imageID, int x, int y, StudentWorld* gw);
    virtual void doSomething();
    virtual bool isKilledByFlamePit() const { return true;}
    virtual void doIfOverlap() = 0;
private:
};

class VaccineGoodie: public BaseGoodie {
public:
    VaccineGoodie(int x, int y, StudentWorld* gw);
    virtual void doIfOverlap();
};

class LandmineGoodie: public BaseGoodie {
public:
    LandmineGoodie(int x, int y, StudentWorld* gw);
    virtual void doIfOverlap();
};

class GasCanGoodie: public BaseGoodie {
public:
    GasCanGoodie(int x, int y, StudentWorld* gw);
    virtual void doIfOverlap();
};

class Landmine: public BaseActor {
public:
    Landmine(int x, int y, StudentWorld* gw);
    virtual void doSomething();
    virtual void doWhenDead() const;
private:
    int m_inactiveTicks;
};

class BaseZombie: public BaseActor {
public:
    BaseZombie(int x, int y, StudentWorld* gw);
    virtual void doSomething();
    virtual bool blocksMovement() const { return true;}
    virtual bool isKilledByFlamePit() const { return true;}
    virtual bool explodesLM() const { return true;}
    virtual bool isZombie() const { return true;}
    virtual void doWhenDead() const;
    virtual void smartPlan() {}
private:
    int m_distancePlan;
};

class DumbZombie: public BaseZombie {
public:
    DumbZombie(int x, int y, StudentWorld* gw);
    virtual void doWhenDead() const;
};

class SmartZombie: public BaseZombie {
public:
    SmartZombie(int x, int y, StudentWorld* gw);
    virtual void doWhenDead() const;
    virtual void smartPlan();
};

class Citizen: public BaseActor {
public:
    Citizen(int imageID, int x, int y, StudentWorld* gw);
    virtual ~Citizen();
    virtual void doSomething();
    virtual bool blocksMovement() const { return true;}
    virtual bool canExit() const { return true;}
    virtual bool isKilledByFlamePit() const { return true;}
    virtual bool canBeInfected() const { return true;}
    virtual bool explodesLM() const { return true;}
    virtual bool isPerson() const { return true;}
    virtual void doWhenDead() const;
};
#endif // ACTOR_H_
