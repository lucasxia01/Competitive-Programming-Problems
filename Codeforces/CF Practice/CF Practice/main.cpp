//
//  main.cpp
//  CF Practice
//
//  Created by Lucas Xia on 9/4/18.
//  Copyright © 2018 Lucas Xia. All rights reserved.
//

#include <iostream>
using namespace std;
#define MAX 1000000
#define F0R(i, n) for (int i = 0, i < n; i++)

struct SegTree {
    int a[MAX];
    int n;
    SegTree(int array[], int size) {
        n = size;
        for (int i = 0; i < n; i++) {
            update(i, array[i]);
        }
    }
    int update(int pos, int v) {
        int i = pos + n;
        a[i] = v;
        int count = 0;
        while (i > 1) {
            i /= 2;
            if (count % 2 == 0) a[i] = a[2 * i] | a[2 * i + 1];
            else a[i] = a[2 * i] ^ a[2 * i + 1];
            count++;
        }
        return a[1];
    }
};
int main(int argc, const char * argv[]) {
    int n, m;
    cin >> n >> m;
    int size = (1 << n);
    int a[size];
    for (int i = 0; i < size; i++) {
        cin >> a[i];
    }
    SegTree st(a, size);
    int p, b;
    for (int i = 0; i < m; i++) {
        cin >> p >> b;
        cout << st.update(p - 1, b) << endl;
    }
    return 0;
}
