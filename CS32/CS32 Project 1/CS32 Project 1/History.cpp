//
//  History.cpp
//  CS32 Project 1
//
//  Created by Lucas Xia on 1/9/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "globals.h"
#include "History.h"

using namespace std;

History::History(int nRows, int nCols)
{
    rows = nRows;
    cols = nCols;
    deaths = 0;
    for (int i = 0; i < MAXZOMBIES; i++)
    {
        death_pos[i][0] = 0;
        death_pos[i][1] = 0;
    }
}
bool History::record(int r, int c)
{
    if (r > rows || r < 1 || c > cols || c < 1) return false;
    death_pos[deaths][0] = r;
    death_pos[deaths][1] = c;
    deaths++;
    return true;
}
void History::display() const
{
    clearScreen();
    int grid[MAXROWS][MAXCOLS];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = 0;
        }
    }
    for (int i = 0; i < deaths; i++)
    {
        grid[death_pos[i][0] - 1][death_pos[i][1] - 1]++;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 0) cout << '.';
            else if (grid[i][j] >= 26) cout << 'Z';
            else cout << (char) (grid[i][j] - 1 + 'A');
        }
        cout << endl;
    }
    cout << endl;
}
