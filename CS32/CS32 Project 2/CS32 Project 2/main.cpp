//
//  main.cpp
//  CS32 Project 2
//
//  Created by Lucas Xia on 1/25/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "Set.h"

using namespace std;

int main() {
    Set X, Y, Z; // testing default constructor
    assert(X.empty()); // testing empty
    
    assert(Z.insert("B")); // testing insertion into empty set
    unite(Z, X, Z); // testing unite for empty set and nonempty third set
    assert(Z.size() == 1); // testing size
    
    assert(X.insert("1") && X.insert("2") && X.insert("3")); // testing multiply inserts
    assert(Y.insert("3") && Y.insert("4") && Y.insert("5"));
    
    unite(X, Y, Z); // testing unite with a matching element
    assert(Z.size() == 5);
    subtract(X, Y, Z); // testing subtract with a matching element
    assert(Z.size() == 2);
    Set W = Z; // copy constructor test
    assert(W.size() == 2);
    
    assert(W.contains("1") && W.contains("2")); // testing working contains
    assert(W.erase("1") && W.erase("2")); // testing working erase
    assert(!W.erase("3")); // testing not working erase
    assert(!W.contains("B")); // testing failed contains
    assert(W.size() == 0);
    
    W = Z; // testing copy constructor
    assert(W.size() == 2);
    
    W = X; // testing assignment operator
    assert(W.size() == 3);
    
    ItemType temp;
    for (int i = 0; i < 3; i++) assert(W.get(i, temp)); // testing get for valid i
    assert(!W.get(3, temp)); // testing get for invalid i
    assert(!W.get(-1, temp));
    
    assert(W.size() == 3 && Z.size() == 2); // testing swap
    swap(W, Z);
    assert(W.size() == 2 && Z.size() == 3);
    
    // all functions in Set have been testing :D
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
