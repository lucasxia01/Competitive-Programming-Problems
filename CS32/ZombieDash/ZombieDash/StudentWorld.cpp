#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

#include "Actor.h"
#include "Level.h"

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_flameCount(100), m_vaccineCount(100), m_landmineCount(100), m_citizenCount(0), m_finishedLevel(false)
{
}

int StudentWorld::init()
{
    Level lev(assetPath());
    string levelFile = "level00.txt";
    levelFile[5] = '0' + getLevel() / 10;
    levelFile[6] = '0' + getLevel() % 10;
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found) {
        return GWSTATUS_PLAYER_WON;
    } else if (result == Level::load_fail_bad_format) {
        cerr << "Your level was improperly formatted" << endl;
        return GWSTATUS_LEVEL_ERROR;
    } else if (result == Level::load_success) {
        for (int x = 0; x < 16; x++)
            for (int y = 0; y < 16; y++) {
                Level::MazeEntry ge = lev.getContentsOf(x, y);
                int tempX = SPRITE_WIDTH * x, tempY = SPRITE_HEIGHT * y;
                switch(ge) {
                    case Level::player:
                        p = new Penelope(tempX, tempY, this);
                        break;
                    case Level::wall:
                        actors.push_back(new Wall(tempX, tempY, this));
                        break;
                    case Level::exit:
                        actors.push_back(new Exit(tempX, tempY, this));
                        break;
                    case Level::pit:
                        actors.push_back(new Pit(tempX, tempY, this));
                        break;
                    case Level::vaccine_goodie:
                        actors.push_back(new VaccineGoodie(tempX, tempY, this));
                        break;
                    case Level::landmine_goodie:
                        actors.push_back(new LandmineGoodie(tempX, tempY, this));
                        break;
                    case Level::gas_can_goodie:
                        actors.push_back(new GasCanGoodie(tempX, tempY, this));
                        break;
                    case Level::dumb_zombie:
                        actors.push_back(new DumbZombie(tempX, tempY, this));
                        break;
                    case Level::smart_zombie:
                        actors.push_back(new SmartZombie(tempX, tempY, this));
                        break;
                    case Level::citizen:
                        m_citizenCount++;
                        actors.push_back(new Citizen(IID_CITIZEN, tempX, tempY, this));
                    case Level::empty:
                        break;
                }
            }
    }
    m_flameCount = 0;
    m_vaccineCount = 0;
    m_landmineCount = 0;
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    p->doSomething();
    if (!p->checkAlive()) {
        p->doWhenDead();
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    for (list<BaseActor*>::iterator it = actors.begin(); it != actors.end();) {
        (*it)->doSomething();
        if (!(*it)->checkAlive()) {
            (*it)->doWhenDead();
            delete (*it);
            it = actors.erase(it);
        } else it++;
    }
    if (m_finishedLevel) {
        playSound(SOUND_LEVEL_FINISHED);
        setFinishedLevel(false);
        if (getLevel() == 99) return GWSTATUS_PLAYER_WON;
        return GWSTATUS_FINISHED_LEVEL;
    }
    oss.str("");
    oss.fill('0');
    oss << "Score: " << setw(6) << getScore();
    oss << "  Level: " << getLevel();
    oss << "  Lives: " << getLives();
    oss << "  Vaccines: " << m_vaccineCount;
    oss << "  Flames: " << m_flameCount;
    oss << "  Mines: " << m_landmineCount;
    oss << "  Infected: " << p->infectionCount();
    setGameStatText(oss.str());
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    if (p != nullptr) delete p;
    p = nullptr;
    for (list<BaseActor*>::iterator it = actors.begin(); it != actors.end();) {
        delete (*it);
        it = actors.erase(it);
    }
}

int StudentWorld::getSquaredDist(int x1, int y1, int x2, int y2) const {
    return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

bool StudentWorld::checkOverlap(int x1, int y1, int x2, int y2) const {
    if (getSquaredDist(x1, y1, x2, y2) <= 100) return true;
    return false;
}

bool StudentWorld::checkOverlapPenelope(int x, int y) const {
    return checkOverlap(x, y, p->getX(), p->getY());
}

bool StudentWorld::checkOverlapCitizen(int x, int y) const {
    for (list<BaseActor*>::const_iterator it = actors.begin(); it != actors.end(); it++)
        if (checkOverlap(x, y, (*it)->getX(), (*it)->getY()) && (*it)->isPerson()) return true;
    return false;
}

bool StudentWorld::checkOverlapPeople(int x, int y) const {
    return (checkOverlapPenelope(x, y) || checkOverlapCitizen(x, y));
}

bool StudentWorld::checkLandmineOverlap(int x, int y) const {
    if (checkOverlapPenelope(x, y)) return true;
    for (list<BaseActor*>::const_iterator it = actors.begin(); it != actors.end(); it++)
        if (checkOverlap(x, y, (*it)->getX(), (*it)->getY()) && (*it)->explodesLM()) return true;
    return false;
}

bool StudentWorld::checkBlock(int x, int y, const BaseActor* act) const {
    return (x - act->getX())*(x - act->getX()) < SPRITE_WIDTH * SPRITE_WIDTH &&
    (y - act->getY())*(y - act->getY()) < SPRITE_HEIGHT * SPRITE_HEIGHT;
}
                                                                                
bool StudentWorld::checkBlocks(int x, int y, const BaseActor* cur) const {
    if (cur != p && checkBlock(x, y, p)) return true;
    for (list<BaseActor*>::const_iterator it = actors.begin(); it != actors.end(); it++) {
        if ((*it)->blocksMovement() && (*it) != cur)
            if (checkBlock(x, y, *it)) return true;
    }
    return false;
}

bool StudentWorld::checkBlocksFlame(int x, int y) const {
    for (list<BaseActor*>::const_iterator it = actors.begin(); it != actors.end(); it++) {
        if ((*it)->blocksFlame())
            if (checkOverlap(x, y, (*it)->getX(), (*it)->getY()))
                return true;
    }
    return false;
}

bool StudentWorld::checkOverlapAll(int x, int y) const {
    if (checkOverlap(x, y, p->getX(), p->getY())) return true;
    for (list<BaseActor*>::const_iterator it = actors.begin(); it != actors.end(); it++) {
        if (checkOverlap(x, y, (*it)->getX(), (*it)->getY())) {
            return true;
        }
    }
    return false;
}

void StudentWorld::flamepitOverlapActors(int x, int y){
    if (checkOverlapPenelope(x, y)) p->setAlive(false);
    for (list<BaseActor*>::iterator it = actors.begin(); it != actors.end(); it++) {
        if ((*it)->isKilledByFlamePit() && checkOverlap(x, y, (*it)->getX(), (*it)->getY()))
            (*it)->setAlive(false);
    }
}

void StudentWorld::infectOverlapActors(int x, int y) {
    if (checkOverlapPenelope(x, y)) p->setInfected(true);
    for (list<BaseActor*>::iterator it = actors.begin(); it != actors.end(); it++) {
        if ((*it)->isPerson() && checkOverlap(x, y, (*it)->getX(), (*it)->getY())) {
            (*it)->setInfected(true);
            playSound(SOUND_CITIZEN_INFECTED);
        }
    }
}

void StudentWorld::exitCitizens(int x, int y){
    for (list<BaseActor*>::iterator it = actors.begin(); it != actors.end(); it++)
        if (checkOverlap(x, y, (*it)->getX(), (*it)->getY()) && (*it)->isPerson()) {
            (*it)->setSaved(true);
            (*it)->setAlive(false);
        }
}
void StudentWorld::findPenelope(int &x, int &y) {
    x = p->getX();
    y = p->getY();
}
void StudentWorld::findNearestPerson(int& x, int& y) {
    int bestX = VIEW_WIDTH + 80, bestY = VIEW_HEIGHT + 80, curX, curY;
    curX = p->getX(); curY = p->getY();
    if (getSquaredDist(x, y, curX, curY) <= min(80*80, getSquaredDist(x, y, bestX, bestY))) {
        bestX = curX; bestY = curY;
    }
    for (list<BaseActor*>::iterator it = actors.begin(); it != actors.end(); it++)
        if ((*it)->isPerson()) {
            curX = (*it)->getX(); curY = (*it)->getY();
            if (getSquaredDist(x, y, curX, curY) <= min(80*80, getSquaredDist(x, y, bestX, bestY))) {
                bestX = curX; bestY = curY;
            }
        }
    x = bestX; y = bestY;
}

void StudentWorld::findNearestZombie(int& x, int& y){
    int bestX = VIEW_WIDTH + 80, bestY = VIEW_HEIGHT + 80, curX, curY;
    for (list<BaseActor*>::iterator it = actors.begin(); it != actors.end(); it++)
        if ((*it)->isZombie()) {
            curX = (*it)->getX(); curY = (*it)->getY();
            if (getSquaredDist(x, y, curX, curY) <= min(80*80, getSquaredDist(x, y, bestX, bestY))) {
                bestX = curX; bestY = curY;
            }
        }
    x = bestX; y = bestY;
}

void StudentWorld::addActor(BaseActor* act) {
    actors.push_back(act);
}

StudentWorld::~StudentWorld() {
    cleanUp();
}
