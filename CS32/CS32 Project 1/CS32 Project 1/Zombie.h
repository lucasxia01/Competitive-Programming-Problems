//
//  Zombie.h
//  CS32 Project 1
//
//  Created by Lucas Xia on 1/9/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//
#ifndef Zombie_h
#define Zombie_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>

class Arena;

class Zombie
{
public:
    // Constructor
    Zombie(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool getAttacked(int dir);
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
};
#endif
