//
//  main.cpp
//  CS32 Practice Problem 1
//
//  Created by Lucas Xia on 1/29/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <string>
using ItemType = std::string;
using namespace std;

struct Node {
    ItemType value; Node* prev; Node *next;
};
class SortedLinkedList {
public:
    SortedLinkedList();
    bool insert(const ItemType& value);
    Node* search(const ItemType& value) const;
    void remove(Node* node);
    int size() const { return m_size; }
    void printIncreasingOrder() const;
private:
    Node* head;
    Node* tail;
    int m_size;
};

SortedLinkedList::SortedLinkedList() {
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

bool SortedLinkedList::insert(const ItemType& value) {
    Node * p = head;
    if (m_size == 0 || value < p->value) {
        Node * newNode = new Node;
        newNode->value = value;
        newNode->next = head;
        newNode->prev = nullptr;
        if (m_size == 0) tail = newNode;
        else newNode->next->prev = newNode;
        head = newNode;
        m_size++;
        cout << "start " << value << endl;
        return true;
    }
    while (p->next != nullptr) {
        if (value > p->value && value < p->next->value) {
            Node * newNode = new Node;
            newNode->value = value;
            newNode->next = p->next;
            newNode->prev = p;
            p->next->prev = newNode;
            p->next = newNode;
            m_size++;
            cout << "middle " << value << endl;
            return true;
        }
        p = p->next;
    }
    if (value > p->value) {
        Node * newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        newNode->prev = tail;
        newNode->prev->next = newNode;
        tail = newNode;
        m_size++;
        cout << "end " << value << endl;
        return true;
    }
    return false;
}

Node* SortedLinkedList::search(const ItemType& value) const {
    Node * p = head;
    while (p != nullptr) {
        if (p->value == value) return p;
        p = p->next;
    }
    return p;
}

void SortedLinkedList::remove(Node* node) {
    if (node == nullptr) return;
    if (node->next == nullptr) tail = node->prev;
    else node->next->prev = node->prev;
    if (node->prev == nullptr) head = node->next;
    else node->prev->next = node->next;
    delete node;
    m_size--;
}

void SortedLinkedList::printIncreasingOrder() const {
    Node * p = head;
    while (p != nullptr) {
        cout << p->value << endl;
        p = p->next;
    }
}


#include <iostream>

int main() {
    SortedLinkedList s;
    assert(s.insert("a") && s.insert("c") && s.insert("b") && s.insert("aa"));
    assert(!s.insert("a"));
    s.remove(s.search("aa"));
    assert(s.insert("z") && !s.insert("z") && s.insert("x"));
    s.remove(s.search("z"));
    s.insert("z");
    s.remove(s.search("z"));
    s.insert("0");
    cout << s.size() << endl;
    s.printIncreasingOrder();
    return 0;
}
