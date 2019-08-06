//
//  Set.cpp
//  CS32 Project 2
//
//  Created by Lucas Xia on 1/17/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <stdio.h>
#include "Set.h"

Set::Set() {
    n_items = 0;
}

bool Set::empty() const {
    return n_items == 0;
}

int Set::size() const {
    return n_items;
}

bool Set::insert(const ItemType& value) {
    if (!contains(value) && n_items != DEFAULT_MAX_ITEMS) {
        data[n_items] = value;
        n_items++;
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
    ItemType temp2;
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
        temp2 = other.data[i];
        other.data[i] = this->data[i];
        this->data[i] = temp2;
    }
}
