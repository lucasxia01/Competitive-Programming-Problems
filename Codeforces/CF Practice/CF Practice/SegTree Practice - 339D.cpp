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

/*
 * Segment Tree
 * Single Element Modification
 * Range Query
 * Supports ints and long longs
 */
template <class T, int SZ>
struct SegTree {
    T segTree[2*SZ];
    SegTree() {
        F0R(i, 2*SZ) segTree.pb(0);
    }
    void build(int pos, T v) {
        for (segTree[pos += SZ] = v; pos > 1; pos >>= 1) {
            segTree[pos>>1] = combine(segTree[pos], segTree[pos^1]);
        }
    }
    T query(int l, int r) {
        T ans = 0;
        for (l+=SZ, r+=SZ; l<r; l>>=1, r>>=1) {
            if (l&1) ans = combine(ans, segTree[l++]);
            if (r&1) ans = combine(ans, segTree[--r]);
        }
        return ans;
    }
    T combine(T a, T b) const {
        return a + b;
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
