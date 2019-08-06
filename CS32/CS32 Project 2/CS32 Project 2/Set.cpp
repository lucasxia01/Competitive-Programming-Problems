//
//  Set.cpp
//  CS32 Project 2
//
//  Created by Lucas Xia on 1/25/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Set.h"
using namespace std;

/* implementing the Set functions */
Set::Set() { // set everything to nullptr or 0
    head = nullptr;
    tail = nullptr;
    n_items = 0;
}

Set::~Set() { // destructor
    Node* temp = head;
    while (temp != nullptr) { // go through the list
        Node * temp2 = temp->next; // save the next node
        //cerr << "d'tor delete " << temp->value << " " << temp << endl;
        delete temp; // delete current node
        temp = temp2; // move on to next node
    }
    head = nullptr; // reset head and tail
    tail = nullptr;
}

Set::Set(const Set& other) { // copy constructor
    head = nullptr; // set everything like normal constructor
    tail = nullptr;
    this->n_items = 0;
    Node * temp = other.head;
    while (temp != nullptr) { // iterate through the other set
        this->insert(temp->value); // insert same values into set
        temp = temp->next; // increment
    }
}

Set& Set::operator = (const Set& other) { // assignment operator
    if (this == &other) return *this; // if same thing, don't reassign
    Node* temp = this->head;
    while (temp != nullptr) { // delete all nodes (same as destructor)
        Node * temp2 = temp->next;
        //cerr << "ao delete " << temp->value << " " << temp << endl;
        delete temp;
        temp = temp2;
    }
    head = nullptr; // reset everything and insert nodes (same as assignment operator)
    tail = nullptr;
    this->n_items = 0;
    temp = other.head;
    while (temp != nullptr) {
        this->insert(temp->value);
        temp = temp->next;
    }
    return *this; // return the set
}

bool Set::empty() const {
    return n_items == 0; // if n_items is zero or not
}

int Set::size() const {
    return n_items; // n_items tracks size
}

bool Set::insert(const ItemType& value) { // insert always adds to front for simplicity
    if (contains(value)) return false; // don't add if set already has it
    Node* n = new Node; // make new node
    //cerr << "make " << value << " " << n << endl;
    n->value = value; // set the node's values
    n->next = head;
    n->prev = nullptr;
    head = n; // reassign head to new node
    if (n->next != nullptr) n->next->prev = n; // change next node's prev pointer if there is next node
    if (n_items == 0) tail = n; // if this is first item, set tail
    n_items++; // increase number of items
    return true;
}
bool Set::erase(const ItemType& value) {
    Node * temp = head;
    while (temp != nullptr) { // iterate through set
        if (temp->value == value) { // if value matches
            Node * save = temp; // save the current node
            if (temp->prev != nullptr) temp->prev->next = temp->next; // if previous node exists, update its next pointer to the next pointer of current node
            else head = temp->next; // otherwise, previous node is head
            if (temp->next != nullptr) temp->next->prev = temp->prev; // if next node exists, update its next pointer to the next pointer of current node
            else tail = temp->prev; // otherwise, next node is tail
            //cerr << "erase delete " << value << " " << save << endl;
            delete save; // delete current node
            n_items--; // decrease number of items
            return true; // we erased so we are done
        }
        temp = temp->next; // increment temp
    }
    return false;
}

bool Set::contains(const ItemType& value) const {
    Node *temp = head;
    while (temp != nullptr) { // iterate through set
        if (temp->value == value) return true; // if value matches, we are done
        temp = temp->next; // increment
    }
    return false; // no matches so return false
}

bool Set::get(int i, ItemType& value) const {
    if (i < 0 || i >= size()) return false; // if i is out of bounds, false
    for (Node * j = head; j != nullptr; j = j->next) { // iterate through each node
        int smaller = 0; // count for how many nodes have smaller value
        for (Node * k = head; k != nullptr; k = k->next) { // iterate through the nodes
            if (j->value > k->value) smaller++; // check if smaller than ith node
        }
        if (smaller == i) { // if it matches
            value = j->value; // update value
            return true; // end
        }
    }
    return true; // this is never reached
}

void Set::swap(Set& other) {
    Node * temp = other.head; // swapping the head pointers
    other.head = this->head;
    this->head = temp;
    
    temp = other.tail; // swapping the tail pointers
    other.tail = this->tail;
    this->tail = temp;
    
    int temp1 = other.n_items; // swapping the n_items
    other.n_items = this->n_items;
    this->n_items = temp1;
    
}

void Set::dump() const {
    ItemType x;
    for (int i = 0; i < n_items; i++) {
        get(i, x);
        cerr << x << " ";
    }
    cerr << endl;
}

void unite(const Set& s1, const Set& s2, Set& result) {
    Set temp; // contains union of s1 and s2
    ItemType x;
    for (int i = 0; i < s1.size(); i++) {
        s1.get(i, x); // get the ith largest node in s1
        temp.insert(x); // add it in
    }
    for (int i = 0; i < s2.size(); i++) {
        s2.get(i, x); // get the ith largest node in s2
        temp.insert(x); // insert it in (if it was already inserted, it will not be inserted twice)
    }
    result = temp; // change result
}

void subtract(const Set& s1, const Set& s2, Set& result) {
    ItemType x;
    Set temp; // contains subtraction of s2 from s1
    for (int i = 0; i < s1.size(); i++) {
        s1.get(i, x); // get ith largest node in s1
        if (!s2.contains(x)) temp.insert(x); // if it is not in s2, insert into temp
    }
    result = temp;
}

