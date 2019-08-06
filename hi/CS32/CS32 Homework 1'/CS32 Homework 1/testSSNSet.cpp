//
//  testSSNSet.cpp
//  CS32 Project 2
//
//  Created by Lucas Xia on 1/17/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//
#include "SSNSet.h"

#include <stdio.h>
#include <cassert>

using namespace std;

int main() {
    SSNSet s;
    assert(s.size() == 0);
    s.add(4);
    s.add(20);
    s.add(69);
    assert(s.add(4) == false);
    s.print();
    return 0;
}
