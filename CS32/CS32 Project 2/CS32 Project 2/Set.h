//
//  Set.h
//  CS32 Project 2
//
//  Created by Lucas Xia on 1/25/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include <string>

using ItemType = std::string;

class Set
{
public:
    Set();
    ~Set();
    Set(const Set& old);
    Set& operator = (const Set& old);
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    void dump() const;
    
private:
    struct Node {
        ItemType value;
        Node * next;
        Node * prev;
    };
    Node* head, *tail;
    int n_items;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
