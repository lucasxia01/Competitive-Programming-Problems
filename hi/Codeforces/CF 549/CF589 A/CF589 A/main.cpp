//
//  main.cpp
//  CF589 A
//
//  Created by Lucas Xia on 3/30/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
using namespace std;
int main(int argc, const char * argv[]) {
    int n, x;
    cin >> n;
    int lastL = -1, lastR = -1;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x == 1) lastR = i;
        if (x == 0) lastL = i;
    }
    cout << min(lastR, lastL) + 1 << endl;
    return 0;
}
