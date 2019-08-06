//
//  SSNSet.cpp
//  CS32 Project 2
//
//  Created by Lucas Xia on 1/17/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//
#include <iostream>
#include "SSNSet.h"

SSNSet::SSNSet() {}

bool SSNSet::add(unsigned long ssn) {
    return s.insert(ssn);
}

int SSNSet::size() const {
    return s.size();
}

void SSNSet::print() const {
    unsigned long l;
    for (int i = 0; i < this->size(); i++) {
        std::cout << s.get(i, l) << std::endl;
    }
}
