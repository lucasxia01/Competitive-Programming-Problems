//
//  main.cpp
//  CF 573
//
//  Created by Lucas Xia on 7/12/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int x;
    cin >> x;
    if (x % 4 == 0) cout << 1 << " A" << endl;
    if (x % 4 == 1) cout << 0 << " A" << endl;
    if (x % 4 == 2) cout << 1 << " B" << endl;
    if (x % 4 == 3) cout << 2 << " A" << endl;
    return 0;
}
