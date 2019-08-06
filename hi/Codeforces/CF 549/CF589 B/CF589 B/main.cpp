//
//  main.cpp
//  CF589 A
//
//  Created by Lucas Xia on 3/30/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    int maxProd = 1, prod = 1;
    string s = to_string(n);
    for (int i = 0; i < s.length(); i++) maxProd *= (s[i] - '0');
    for (int i = 0; i < s.length(); i++) {
        prod = 1;
        for (int j = 0; j < i; j++) {
            prod *= (s[j] - '0');
        }
        if (s[i] == '0') {
            continue;
        }
        if (i != 0 || s[i] != '1') prod *= (s[i] - '0' - 1);
        for (int j = i + 1; j < s.length(); j++) {
            prod *= 9;
        }
        maxProd = max(maxProd, prod);
    }
    cout << maxProd << endl;
    return 0;
}
