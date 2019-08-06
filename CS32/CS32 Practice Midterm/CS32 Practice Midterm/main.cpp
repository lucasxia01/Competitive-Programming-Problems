#include <iostream>
using namespace std;

class LinkedList
{
public:
    LinkedList(): head(nullptr) { } ~LinkedList();
    void addToList(int value); void reverse();
    void output();
    bool findNthFromLast(int N, int &value);
private:
    struct Node
    {
        int num;
        Node *next;
    };
    Node *head;
};
void LinkedList::output() {
    Node *ptr = head;
    cout << head << endl;
    cout << "The elements in the list are: ";
    while(ptr!=nullptr) {
        cout << ptr->num << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

LinkedList::~LinkedList() {
    Node * p = head;
    while (p != nullptr) {
        Node * temp = p->next;
        delete p;
        p = temp;
    }
}

void LinkedList::addToList(int value) {
    Node * p = head;
    Node * newNode = new Node;
    newNode->num = value;
    newNode->next = nullptr;
    if (head == nullptr) head = newNode;
    else {
        while (p->next != nullptr) p = p->next;
        //cout << p << " " << head << " " << newNode << endl;
        p->next = newNode;
    }
}

void LinkedList::reverse() {
    Node *nextNode = nullptr, *prevNode = nullptr, *current = head;
    while (current) {
        nextNode = current->next;
        current->next = prevNode;
        prevNode = current;
        current = nextNode;
    }
    head = prevNode;
}

//bool LinkedList::findNthFromLast(int N, int &value) {
//    reverse();
//    Node * temp = head;
//    for (int i = 0; i < N - 1; i++) {
//        if (temp == nullptr) return false;
//        temp = temp->next;
//    }
//    if (temp == nullptr) return false;
//    value = temp->num;
//    reverse();
//    return true;
//}

bool LinkedList::findNthFromLast(int N, int &value) {
    int size = 0;
    Node * p = head;
    while (p != nullptr) {
        p = p->next;
        size++;
    }
    if (N > size) return false;
    p = head;
    for (int i = 0; i < size - N; i++) p = p->next;
    value = p->num;
    return true;
}

int main() {
    LinkedList list;
    for(int i=1;i<=10;i++) list.addToList(i);
    list.output();
    list.reverse();
    list.output();
    int v = 0;
    list.findNthFromLast(10, v);
    cout << v << endl;
}
