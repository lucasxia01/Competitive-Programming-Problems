//
//  main.cpp
//  Heap
//
//  Created by Lucas Xia on 3/7/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <stack>
#include <unordered_map>
#include <utility>
using namespace std;

struct Node {
    int val;
    Node* left, *right;
};

void postorderTraversal(Node* root) {
    stack<Node*> s, s2;
    s.push(root);
    Node * cur;
    unordered_map<Node*, bool> m;
    while (!s.empty()) {
        cur = s.top();
        s.pop();
        if (cur == nullptr) continue;
        s2.push(cur);
        m.insert(make_pair(cur, false));
        if (cur->right == nullptr && cur->left == nullptr) {
            m[cur] = true;
            do {
                m[s2.top()] = true;
                cout << s2.top()->val << " ";
                s2.pop();
            } while (s2.top()->left != nullptr && m.count(s2.top()->left) && m[s2.top()->left] && s2.top()->right != nullptr && m.count(s2.top()->right) && m[s2.top()->right]);
        }
        s.push(cur->right);
        s.push(cur->left);
    }
}
int main(int argc, const char * argv[]) {
    Node *nodes = new Node[7];
    for (int i = 0; i < 7; i++) {
        nodes[i].val = i + 1;
        if (i >= 3) {
            nodes[i].left = nullptr;
            nodes[i].right = nullptr;
        } else {
            nodes[i].left = nodes + (2*i + 1);
            nodes[i].right = nodes + (2*i + 2);
        }
    }
    postorderTraversal(nodes);
    delete [] nodes;
    return 0;
}
