//
//  newSet.cpp
//  CS32 Homework 1.2
//
//  Created by Lucas Xia on 1/17/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "newSet.h"

Set::Set(int size) {
    if (size < 0) exit(1);
    n_items = 0;
    max_size = size;
    data = new ItemType[size];
    std::cerr << "DC" << max_size << std::endl;
}

Set::~Set() {
    std::cerr << "D" << std::endl;
    delete [] data;
}

Set::Set(const Set& old) {
    n_items = old.n_items;
    max_size = old.max_size;
    data = new ItemType[old.max_size];
    for (int i = 0; i < n_items; i++) {
        data[i] = old.data[i];
    }
    std::cerr << "CC " << n_items << " " << max_size << std::endl;
}

Set&Set::operator = (const Set& old) {
    if (this == &old) {
        
        return (*this);
    }
    delete [] this->data;
    this->n_items = old.n_items;
    this->data = new ItemType[old.max_size];
    for (int i = 0; i < n_items; i++) {
        this->data[i] = old.data[i];
    }
    std::cerr << "AO " << old.n_items << " " << max_size << std::endl;
    return (*this);
}

bool Set::empty() const {
    return n_items == 0;
}

int Set::size() const {
    //std::cerr << n_items << std::endl;
    return n_items;
}

bool Set::insert(const ItemType& value) {
    if (!contains(value) && n_items != max_size) {
        data[n_items] = value;
        n_items++;
        //std::cerr << n_items << "HIHIHI" << std::endl;
        return true;
    }
    return false;
}
bool Set::erase(const ItemType& value) {
    bool found = false;
    for (int i = 0; i < n_items; i++) {
        if (found) {
            data[i - 1] = data[i];
        } else {
            if (data[i] == value) {
                found = true;
            }
        }
    }
    if (found) n_items--;
    return found;
}

bool Set::contains(const ItemType& value) const {
    for (int i = 0; i < n_items; i++) {
        if (data[i] == value) return true;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const {
    if (i < 0 || i >= n_items) return false;
    for (int j = 0; j < n_items; j++) {
        int smaller = 0;
        for (int k = 0; k < n_items; k++) {
            if (data[j] > data[k]) smaller++;
        }
        if (smaller == i) {
            value = data[j];
            return true;
        }
    }
    return false;
}

void Set::swap(Set& other) {
    int temp = other.n_items;
    other.n_items = this->n_items;
    this->n_items = temp;
    int temp1 = other.max_size;
    other.max_size = this->max_size;
    this->max_size = temp1;
    ItemType* temp2 = other.data;
    other.data = this->data;
    this->data = temp2;
}
