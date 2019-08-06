//
//  main.cpp
//  DoublyLinkedList
//
//  Created by Lucas Xia on 1/25/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include "DoublyLinkedList.h"
using namespace std;

int main() {
    DoublyLinkedList l;
    assert(!l.erase("no"));
    assert(l.insert(0, "hi")); // hi
    
    assert(l.erase("hi")); //
    assert(l.insert(0, "bye")); // bye
    
    assert(l.insert(0, "hi")); // hi bye
    
    assert(l.erase("hi")); // bye
    assert(!l.erase("no"));
    assert(l.insert(1, "hi")); // bye hi
    
    assert(l.find("bye") != nullptr);
    assert(l.find("hi") != nullptr);
    assert(l.find("yes") == nullptr);
    assert(l.erase("hi")); // bye
    assert(l.insert(1, "A")); // bye A
    
    assert(l.insert(2, "B")); // bye A B
    
    assert(l.insert(3, "C")); // bye A B C
    
    assert(l.erase("C")); // bye A B
    assert(l.insert(0, "Vishal")); // Vishal bye A B
    
    assert(l.erase("Vishal")); // bye A B
    assert(l.getSize() == 3);
    assert(l.insert(l.getSize(), "King")); // bye A B King
    
    assert(l.insert(l.getSize(), "James"));  // bye A B King James
    
    assert(l.insert(l.getSize(), "King"));  // bye A B King James King
    
    l.print();
    return 0;
}
