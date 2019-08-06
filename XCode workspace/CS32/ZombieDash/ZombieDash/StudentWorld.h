#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

#include <list>
#include <iostream>
#include <sstream>
#include <iomanip>

class Penelope;
class BaseActor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    int getSquaredDist(int x1, int y1, int x2, int y2) const;
    bool checkBlock(int x, int y, const BaseActor* cur) const;
    bool checkBlocks(int x, int y, const BaseActor* cur) const;
    bool checkBlocksFlame(int x, int y) const;
    
    bool checkOverlap(int x1, int y1, int x2, int y2) const;
    bool checkOverlapAll(int x, int y) const;
    bool checkOverlapPenelope(int x, int y) const;
    bool checkOverlapCitizen(int x, int y) const;
    bool checkOverlapPeople(int x, int y) const;
    bool checkLandmineOverlap(int x, int y) const;
    
    void flamepitOverlapActors(int x, int y);
    void infectOverlapActors(int x, int y);
    void exitCitizens(int x, int y);
    void findPenelope(int& x, int& y);
    void findNearestPerson(int& x, int& y);
    void findNearestZombie(int& x, int& y);
    
    void addActor(BaseActor* act);

    int getFlameCount() const { return m_flameCount;}
    void setFlameCount(int next) { m_flameCount = next;}
    int getVaccineCount() const { return m_vaccineCount;}
    void setVaccineCount(int next) { m_vaccineCount = next;}
    int getLandmineCount() const { return m_landmineCount;}
    void setLandmineCount(int next) { m_landmineCount = next;}
    int getCitizenCount() const { return m_citizenCount;}
    void setCitizenCount(int next) { m_citizenCount = next;}

    void setFinishedLevel(bool next) { m_finishedLevel = next;}
private:
    Penelope * p;
    std::list<BaseActor*> actors;
    int m_flameCount;
    int m_vaccineCount;
    int m_landmineCount;
    int m_citizenCount;
    bool m_finishedLevel;
    std::ostringstream oss;
};

#endif // STUDENTWORLD_H_
