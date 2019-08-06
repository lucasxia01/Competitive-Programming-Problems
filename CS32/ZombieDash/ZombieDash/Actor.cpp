#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

#include <vector>
BaseActor::BaseActor(int imageID, double startX, double startY, Direction dir, int depth, double size): GraphObject(imageID, startX, startY, dir, depth, size), m_isAlive(1), m_isParalyzed(0), m_isInfected(0), m_infectionCount(0), m_saved(false) {
}

void BaseActor::checkMove(int& x, int& y, Direction dir, int moves) const{
    for (int i = 0; i < moves; i++) {
        switch(dir) {
            case right:
                if (getWorld()->checkBlocks(x + 1, y, this)) return;
                x++; break;
            case up:
                if (getWorld()->checkBlocks(x, y + 1, this)) return;
                y++; break;
            case left:
                if (getWorld()->checkBlocks(x - 1, y, this)) return;
                x--; break;
            case down:
                if (getWorld()->checkBlocks(x, y - 1, this)) return;
                y--; break;
        }
    }
}

Penelope::Penelope(int x, int y, StudentWorld * gw): BaseActor(IID_PLAYER, x, y) {
    setWorld(gw);}
void Penelope::doSomething() {
    if (!checkAlive()) return;
    if (isInfected()) setInfectionCount(infectionCount() + 1);
    if (infectionCount() == 500) {
        setAlive(false);
        return; // student world has to see she's dead
    }
    int ch;
    if (!getWorld()->getKey(ch)) return;
    int x = getX(), y = getY();
    if (ch == KEY_PRESS_SPACE && getWorld()->getFlameCount()) {
        getWorld()->playSound(SOUND_PLAYER_FIRE);
        getWorld()->setFlameCount(getWorld()->getFlameCount() - 1);
        for (int i = 0; i < 3; i++) {
            switch(getDirection()) {
                case right:
                    if (getWorld()->checkBlocksFlame(x + SPRITE_WIDTH, y)) return;
                    x+=SPRITE_WIDTH; break;
                case up:
                    if (getWorld()->checkBlocksFlame(x, y + SPRITE_HEIGHT)) return;
                    y+=SPRITE_HEIGHT; break;
                case left:
                    if (getWorld()->checkBlocksFlame(x - SPRITE_WIDTH, y)) return;
                    x-=SPRITE_WIDTH; break;
                case down:
                    if (getWorld()->checkBlocksFlame(x, y - SPRITE_HEIGHT)) return;
                    y-=SPRITE_HEIGHT; break;
            }
            if (!getWorld()->checkBlocksFlame(x, y)) {
                BaseActor* temp = new Flame(x, y, getWorld(), getDirection());
                getWorld()->addActor(temp);
            }
        }
    } else if (ch == KEY_PRESS_TAB && getWorld()->getLandmineCount()) { // what is a tab
        getWorld()->setLandmineCount(getWorld()->getLandmineCount() - 1);
        BaseActor* temp = new Landmine(x, y, getWorld());
        getWorld()->addActor(temp);
    } else if (ch == KEY_PRESS_ENTER && getWorld()->getVaccineCount()) {
        getWorld()->setVaccineCount(getWorld()->getVaccineCount() - 1);
        setInfectionCount(0);
        setInfected(false);
    }
    // direction keys
    if (ch == KEY_PRESS_RIGHT) setDirection(right);
    else if (ch == KEY_PRESS_UP) setDirection(up);
    else if (ch == KEY_PRESS_LEFT) setDirection(left);
    else if (ch == KEY_PRESS_DOWN) setDirection(down);
    else return;
    this->checkMove(x, y, getDirection(), 4);
    if (x != getX() || y != getY()) this->moveTo(x, y);
}

void Penelope::doWhenDead() const {
    getWorld()->playSound(SOUND_PLAYER_DIE);
}

Wall::Wall(int x, int y, StudentWorld* gw): BaseActor(IID_WALL, x, y) {
    setWorld(gw);
}

void Wall::doSomething() {}

Exit::Exit(int x, int y, StudentWorld* gw): BaseActor(IID_EXIT, x, y, right, 1) {
    setWorld(gw);
}
void Exit::doSomething() {
    getWorld()->exitCitizens(getX(), getY());
    if (!getWorld()->getCitizenCount() && getWorld()->checkOverlapPenelope(getX(), getY()))
        getWorld()->setFinishedLevel(true);
}

Pit::Pit(int x, int y, StudentWorld* gw): BaseActor(IID_PIT, x, y) {
    setWorld(gw);
}

void Pit::doSomething() {
    getWorld()->flamepitOverlapActors(getX(), getY());
}

Flame::Flame(int x, int y, StudentWorld* gw, Direction dir): BaseActor(IID_FLAME, x, y, dir) {
    setWorld(gw);
}

void Flame::doSomething() {
    if (!checkAlive()) return;
    setAlive((checkAlive() + 1) % 3);
    getWorld()->flamepitOverlapActors(this->getX(), this->getY());
}

Vomit::Vomit(int x, int y, StudentWorld* gw): BaseActor(IID_VOMIT, x, y) {
    setWorld(gw);
    gw->playSound(SOUND_ZOMBIE_VOMIT);
}

void Vomit::doSomething() {
    if (!checkAlive()) return;
    setAlive((checkAlive() + 1) % 3);
    getWorld()->infectOverlapActors(getX(), getY());
}

BaseGoodie::BaseGoodie(int imageID, int x, int y, StudentWorld* gw): BaseActor(imageID, x, y, right, 1) {
    setWorld(gw);
}

void BaseGoodie::doSomething() {
    if (!checkAlive()) return;
    if (getWorld()->checkOverlapPenelope(this->getX(), this->getY())) {
        getWorld()->increaseScore(50);
        setAlive(0);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        doIfOverlap();
    }
}

VaccineGoodie::VaccineGoodie(int x, int y, StudentWorld* gw): BaseGoodie(IID_VACCINE_GOODIE, x, y, gw) {}
void VaccineGoodie::doIfOverlap() {
    getWorld()->setVaccineCount(getWorld()->getVaccineCount() + 1);
}

LandmineGoodie::LandmineGoodie(int x, int y, StudentWorld* gw): BaseGoodie(IID_LANDMINE_GOODIE, x, y, gw) {}
void LandmineGoodie::doIfOverlap() {
    getWorld()->setLandmineCount(getWorld()->getLandmineCount() + 2);
}

GasCanGoodie::GasCanGoodie(int x, int y, StudentWorld* gw): BaseGoodie(IID_GAS_CAN_GOODIE, x, y, gw) {}
void GasCanGoodie::doIfOverlap() {
    getWorld()->setFlameCount(getWorld()->getFlameCount() + 5);
}

Landmine::Landmine(int x, int y, StudentWorld* gw): BaseActor(IID_LANDMINE, x, y, right, 1), m_inactiveTicks(30) {
    setWorld(gw);
}

void Landmine::doSomething() {
    if (!checkAlive()) return;
    if (m_inactiveTicks) m_inactiveTicks--;
    else if (getWorld()->checkLandmineOverlap(getX(), getY())) setAlive(false);
}

void Landmine::doWhenDead() const {
    getWorld()->playSound(SOUND_LANDMINE_EXPLODE);
    int x, y;
    for (int i = -1; i <= 1; i++) for (int j = -1; j <= 1; j++) {
        x = getX() + i * SPRITE_WIDTH; y = getY() + j * SPRITE_HEIGHT;
        if (!getWorld()->checkBlocksFlame(x, y)) {
            BaseActor* temp = new Flame(x, y, getWorld(), up);
            getWorld()->addActor(temp);
        }
    }
    BaseActor* temp = new Pit(getX(), getY(), getWorld());
    getWorld()->addActor(temp);
}

BaseZombie::BaseZombie(int x, int y, StudentWorld* gw): BaseActor(IID_ZOMBIE, x, y), m_distancePlan(0) {
    setWorld(gw);
}

void BaseZombie::doSomething() {
    if (!checkAlive()) return;
    if (!isParalyzed()) {
        int x = getX(), y = getY();
        switch(getDirection()) {
            case right:
                if (getWorld()->checkOverlapPeople(x + SPRITE_WIDTH, y)) x+=SPRITE_WIDTH;
                break;
            case up:
                if (getWorld()->checkOverlapPeople(x, y + SPRITE_HEIGHT)) y+=SPRITE_HEIGHT;
                break;
            case left:
                if (getWorld()->checkOverlapPeople(x - SPRITE_WIDTH, y)) x-=SPRITE_WIDTH;
                break;
            case down:
                if (getWorld()->checkOverlapPeople(x, y - SPRITE_HEIGHT)) y-=SPRITE_HEIGHT;
                break;
        }
        if ((x != getX() || y != getY()) && !randInt(0, 2)) {
            Vomit* temp = new Vomit(x, y, getWorld());
            getWorld()->addActor(temp);
            return;
        }
        if (!m_distancePlan) {
            m_distancePlan = randInt(3, 10);
            setDirection(randInt(0, 3) * 90);
            smartPlan();
        }
        int destX = getX(), destY = getY();
        this->checkMove(destX, destY, getDirection(), 1);
        if (destX == getX() && destY == getY()) m_distancePlan = 0; // zombie did not move
        else {
            this->moveTo(destX, destY);
            m_distancePlan--;
        }
    }
    setParalysis(!isParalyzed());
}

void BaseZombie::doWhenDead() const {
    getWorld()->playSound(SOUND_ZOMBIE_DIE);
}

DumbZombie::DumbZombie(int x, int y, StudentWorld* gw): BaseZombie(x, y, gw) {}
void DumbZombie::doWhenDead() const {
    BaseZombie::doWhenDead();
    getWorld()->increaseScore(1000);
    if (randInt(0, 9) <= 0) {
        int x = getX(), y = getY();
        BaseActor* temp = new VaccineGoodie(x, y, getWorld());
        Direction dir = randInt(0, 3) * 90;
        temp->setDirection(dir);
        if (dir == 0 || dir == 180) temp->moveTo(x + (90 - dir)/90 * SPRITE_WIDTH, y);
        else temp->moveTo(x, y + (180 - dir)/90 * SPRITE_HEIGHT);
        temp->setDirection(0);
        if (!getWorld()->checkOverlapAll(temp->getX(), temp->getY())) getWorld()->addActor(temp);
        else delete temp;
    }
}
SmartZombie::SmartZombie(int x, int y, StudentWorld* gw): BaseZombie(x, y, gw) {}
void SmartZombie::doWhenDead() const { BaseZombie::doWhenDead(); getWorld()->increaseScore(2000);}
void SmartZombie::smartPlan() {
    int x = getX(), y = getY();
    getWorld()->findNearestPerson(x, y);
    std::vector<Direction> possDir;
    if (x < VIEW_HEIGHT && y < VIEW_HEIGHT) {
        if (x - getX() > 0) possDir.push_back(0);
        if (x - getX() < 0) possDir.push_back(180);
        if (y - getY() > 0) possDir.push_back(90);
        if (y - getY() < 0) possDir.push_back(270);
    }
    if (possDir.size() == 0) {
        possDir.push_back(0);
        possDir.push_back(90);
        possDir.push_back(180);
        possDir.push_back(270);
    }
    setDirection(possDir.at(randInt(0, int(possDir.size() - 1))));
}

Citizen::Citizen(int imageID, int x, int y, StudentWorld* gw): BaseActor(imageID, x, y){
    setWorld(gw);
}

Citizen::~Citizen() {
    getWorld()->setCitizenCount(getWorld()->getCitizenCount() - 1);
}

void Citizen::doSomething() {
    if (!checkAlive()) return;
    if (isInfected()) setInfectionCount(infectionCount() + 1);
    if (infectionCount() == 500) {
        setAlive(false);
        return; // student world has to see she's dead
    }
    if (!isParalyzed()) {
        int pX = getX(), pY = getY(), zX = getX(), zY = getY(), curX = getX(), curY = getY();
        getWorld()->findPenelope(pX, pY);
        getWorld()->findNearestZombie(zX, zY);
        int dist_p = getWorld()->getSquaredDist(curX, curY, pX, pY);
        int dist_z = getWorld()->getSquaredDist(curX, curY, zX, zY);
        std::vector<Direction> possDir;
        if (dist_p < dist_z && dist_p <= 80*80) {
            if (pX - curX > 0) possDir.push_back(0);
            if (pX - curX < 0) possDir.push_back(180);
            if (pY - curY > 0) possDir.push_back(90);
            if (pY - curY < 0) possDir.push_back(270);
            Direction dir = possDir.at(randInt(0, int(possDir.size() - 1)));
            checkMove(curX, curY, dir, 2);
            if (abs(curX + curY - getX() - getY()) < 2) return;
            setDirection(dir);
            moveTo(curX, curY);
        } else if (dist_z <= 80*80) {
            int newX, newY, newPX, newPY, newDistZ;
            for (int i = 0; i < 4; i++) {
                newX = curX; newY = curY;
                newPX = curX; newPY = curY;
                checkMove(newX, newY, i * 90, 2);
                if (abs(newX + newY - curX - curY) < 2) continue;
                getWorld()->findNearestZombie(newPX, newPY);
                newDistZ = getWorld()->getSquaredDist(newX, newY, newPX, newPY);
                if (newDistZ > dist_z && newDistZ <= 80*80) {
                    dist_p = newDistZ;
                    setDirection(i * 90);
                }
            }
            checkMove(curX, curY, getDirection(), 2);
            if (abs(curX + curY - getX() - getY()) < 2) return;
            moveTo(curX, curY);
        }
    }
    setParalysis(!isParalyzed());
}

void Citizen::doWhenDead() const {
    if (infectionCount() == 500) {
        getWorld()->playSound(SOUND_ZOMBIE_BORN);
        getWorld()->increaseScore(-1000);
        BaseZombie* temp;
        if (randInt(0, 9) < 7) temp = new DumbZombie(getX(), getY(), getWorld());
        else temp = new SmartZombie(getX(), getY(), getWorld());
        getWorld()->addActor(temp);
    } else if (!isSaved()) {
        getWorld()->playSound(SOUND_CITIZEN_DIE);
        getWorld()->increaseScore(-1000);
    } else {
        getWorld()->playSound(SOUND_CITIZEN_SAVED);
        getWorld()->increaseScore(500);
    }
}
