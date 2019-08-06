//
//  main.cpp
//  CF589 A
//
//  Created by Lucas Xia on 3/30/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n][2];
    int remove[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][0]--;
        remove[i] = 1;
    }
    for (int i = 0; i < n; i++) {
        remove[i] *= a[i][1];
        if (a[i][0] != -2) {
            remove[a[i][0]] *= a[i][1];
        }
    }
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        if (remove[i]) pq.push(-i);
    }
    int id;
    if (pq.empty()) {
        cout << -1 << endl;
        return 0;
    }
    while (!pq.empty()) {
        id = pq.top();
        pq.pop();
        cout << -id + 1 << " ";
    }
    cout << endl;
    return 0;
}
