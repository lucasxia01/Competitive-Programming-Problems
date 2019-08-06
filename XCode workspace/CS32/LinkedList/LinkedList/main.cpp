//
//  main.cpp
//  LinkedList
//
//  Created by Lucas Xia on 1/22/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "LinkedList.h"

using namespace std;
int main(int argc, const char * argv[]) {
    LinkedList l;
    assert(!l.erase("no"));
    assert(l.insert(0, "hi", 0));
    assert(l.erase("hi"));
    assert(l.insert(0, "bye", 42));
    assert(l.insert(0, "hi", 0));
    assert(l.erase("hi"));
    assert(!l.erase("no"));
    assert(l.insert(1, "hi", 41));
    assert(l.find("bye") != nullptr);
    assert(l.find("hi") != nullptr);
    assert(l.find("yes") == nullptr);
    assert(l.erase("hi"));
    assert(l.insert(1, "A", 95));
    assert(l.insert(2, "B", 96));
    assert(l.insert(3, "C", 97));
    assert(l.erase("C"));
    assert(l.insert(0, "Vishal", 100));
    assert(l.erase("Vishal"));
    l.print();
    return 0;
}
