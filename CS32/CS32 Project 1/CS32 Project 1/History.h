//
//  History.h
//  CS32 Project 1
//
//  Created by Lucas Xia on 1/9/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//


#ifndef History_h
#define History_h

#include "globals.h"

using namespace std;

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int rows, cols, deaths;
    int death_pos[MAXZOMBIES][2];
};

#endif /* History_h */
