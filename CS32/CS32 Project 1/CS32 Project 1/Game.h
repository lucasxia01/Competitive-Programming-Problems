//
//  Game.h
//  CS32 Project 1
//
//  Created by Lucas Xia on 1/9/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//



#ifndef Game_h
#define Game_h

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};
#endif

