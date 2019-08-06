#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <list>
#include <iostream>
template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    struct Node {
        char label;
        std::vector<ValueType> values;
        std::vector<Node*> children;
    };
    Node* root;
    void removeAllNodes(Node* cur);
    std::vector<ValueType> findHelper(Node* cur, char* key, bool exactMatchOnly, int size) const;
//    void printAllPaths(std::string labels, Node* cur) const {
//        labels += cur->label;
//        if (cur->children.size() == 0) std::cout << labels << std::endl;
//        for (int i = 0; i < cur->children.size(); i++) {
//            printAllPaths(labels, cur->children[i]);
//        }
//    }
};
template<typename ValueType>
Trie<ValueType>::Trie() { // O(1)
    root = new Node; // O(1)
}

template<typename ValueType>
void Trie<ValueType>::removeAllNodes(Node* cur) { // O(N) goes through each node once
    if (cur == nullptr) return;
    for (typename std::vector<Node*>::iterator it = cur->children.begin(); it != cur->children.end(); it++) {
        removeAllNodes(*it);
    }
    delete cur;
}

template<typename ValueType>
Trie<ValueType>::~Trie() { // O(N)
    removeAllNodes(root); // O(N)
}

template<typename ValueType>
void Trie<ValueType>::reset() { // O(N)
    removeAllNodes(root); // O(N)
    root = new Node; // O(1)
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string &key, const ValueType &value) { // O(LC), L is length, C is average amount of children
    Node* cur = root;
    // check if already exists
    for (int i = 0; i < key.length(); i++) { // O(L)
        typename std::vector<Node*>::iterator it;
        for (it = cur->children.begin(); it != cur->children.end(); it++) { // O(C)
            if (key[i] == (*it)->label) {
                cur = (*it);
                break;
            }
        }
        // insert node
        if (it == cur->children.end()) {
            Node* temp = new Node;
            temp->label = key[i];
            cur->children.push_back(temp);
            cur = temp;
        }
    }
    cur->values.push_back(value);
}
template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::findHelper(Node* cur, char* key, bool exactMatchOnly, int size) const { // O(LC) or O(L^2 C^2)
    std::vector<ValueType> v, temp;
    if (size == 0) {
        for (int i = 0; i < cur->values.size(); i++) v.push_back(cur->values[i]);
        return v;
    }
    typename std::vector<Node*>::iterator it;
    for (it = cur->children.begin(); it != cur->children.end(); it++) {
        if (cur != root && !exactMatchOnly && key[0] != (*it)->label) { // worst case there are all L changes, for each one it takes LC * C
            temp = findHelper(*it, key + 1, !exactMatchOnly, size - 1); // O(L)
            for (int i = 0; i < temp.size(); i++) v.push_back(temp[i]);
            temp.clear();
        }
        if (key[0] == (*it)->label) { // easy to show it is O(LC + V)
            temp = findHelper(*it, key + 1, exactMatchOnly, size - 1);
            for (int i = 0; i < temp.size(); i++) v.push_back(temp[i]);
            temp.clear();
        }
    }
    return v;
}
template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const {
    char* k = new char[key.size()];
    for (int i = 0; i < key.size(); i++) k[i] = key[i];
    return findHelper(root, k, exactMatchOnly, key.size());
    delete [] k;
}

#endif // TRIE_INCLUDED
