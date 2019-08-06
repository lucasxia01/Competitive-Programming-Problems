//
//  main.cpp
//  CF508C
//
//  Created by Lucas Xia on 9/6/18.
//  Copyright © 2018 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    vector<int> a, b;
    long long count = 0;
    int x;
    for (int i = 0; i < n; i++) {cin >> x; a.push_back(-1 * x);}
    for (int i = 0; i < n; i++) {cin >> x; b.push_back(-1 * x);}
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    a.push_back(1);
    b.push_back(1);
    while (a.size() > 1 || b.size() > 1) {
        if (a.front() < b.front()) {
            x = -1 * a.front();
            a.erase(a.begin());
            count += x;
        } else {
            x = -1 * b.front();
            b.erase(b.begin());
        }
        
        if (a.front() > b.front()) {
            x = -1 * b.front();
            b.erase(b.begin());
            count -= x;
        } else {
            x = -1 * a.front();
            a.erase(a.begin());
        }
    }
    cout << count << endl;
    return 0;
}
