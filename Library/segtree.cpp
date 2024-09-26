#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define F0R(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b); i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 200011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

const int MX = 1<<20;

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
        F0R(i, 2*SZ) segTree[i] = 0;
    }
    void upd(int pos, T v) {
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

/*
 * Lazy Segment Tree
 * Range Increment Modification
 * Range Sum or Max Query
 * Supports ints and long longs
 
 * Range Min Query Verified 3/5/20 by https://codeforces.com/contest/1295/submission/72543936
 */
template <class T, bool sum>
struct LazySegTree {
    int SZ;
    vector<T> t;
    vector<T> d;
    vector<T> subTreeSize;
    int height = 0;
    LazySegTree(int n) {
        SZ = n;
        F0R(i, 2*SZ) if (sum) t.pb(0); else t.pb(-INF);
        F0R(i, SZ) {
            d.pb(0);
            t.pb(0);
        }
        for (ll pow = 1; pow<SZ; pow *= 2) height++;
        if (sum) {
            F0Rd(i, SZ) {
                int a = 1, b = 1;
                if (2*i < SZ) a = subTreeSize[2*i];
                if (2*i+1 < SZ) b = subTreeSize[2*i+1];
                subTreeSize[i] = a+b;
            }
        }
    }
    void apply(int p, T v) { // applies update to node in single function
        t[p] = t[p] + v;
        if (p < SZ) d[p] = d[p] + v;
    }
    void push(int p) { // pushes lazy down the tree
        for (int lev = height; lev > 0; lev--) {
            int idx = p >> lev; // get level of the parent
            if (d[idx] != 0) { // if there's actually something to push down
                apply(idx<<1, d[idx]); // push down lazy to child
                apply(idx<<1|1, d[idx]); // push down lazy to other child
                d[idx] = 0; // set lazy to 0 since you're done
            }
        }
    }
    void pull(int p) { // updates parents of node with correct values while also applying the lazy
        while (p > 1) p>>=1, t[p] = combine(t[2*p], t[2*p+1]) + subTreeSize[p]*d[p];
    }
    void upd(int l, int r, T v) {
        int l0 = l+SZ, r0 = r+SZ;
        for (l+=SZ, r+=SZ; l<r; l>>=1, r>>=1) {
            if (l&1) apply(l++, v);
            if (r&1) apply(--r, v);
        }
        pull(l0);
        pull(r0-1);
    }
    T query(int l, int r) {
        l+=SZ; r+=SZ;
        push(l);
        push(r-1);
        T ans;
        if (sum) ans = 0;
        else ans = -INF; // only for sums, also can do: ans = -INF;
        for (; l<r; l>>=1, r>>=1) {
            if (l&1) ans = combine(ans, t[l++]);
            if (r&1) ans = combine(ans, t[--r]);
        }
        return ans;
    }
    T combine(T a, T b) const { // template for other associative functions
        if (sum) return a + b;
        else return a > b ? a : b; // default is sum, also can do: max(a, b); or a > b ? a : b;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n = 6;
    int a[6] = {1, 2, 3, 4, 5, 6};
    LazySegTree<int, false> st(6);
    F0R(i, n) {
        st.upd(i, i+1, a[i]);
    }
    F0R(i, n) {
        cout << i << " " << st.lazy[i] << endl; //
        //FOR(j, i, n) cout << i << " " << j << " " << st.query(i, j) << endl;
    }
    F0R(i, 2*n) cout << i << " " << st.segTree[i] << endl;
    
    F0R(i, n) {
        FOR(j, i+1, n) cout << i << " " << j << " " << st.query(i, j) << endl; //
    }
    st.upd(0, 6, 1);
    F0R(i, n) {
        cout << i << " " << st.lazy[i] << endl; // << st.lazy[i] << " "
        //FOR(j, i, n) cout << i << " " << j << " " << st.query(i, j) << endl;
    }
    F0R(i, 2*n) cout << i << " " << st.segTree[i] << endl;
    cout << st.query(1, 6) << endl;
    F0R(i, n) {
        cout << i << " " << st.lazy[i] << endl; // << st.lazy[i] << " "
        //FOR(j, i, n) cout << i << " " << j << " " << st.query(i, j) << endl;
    }
    F0R(i, 2*n) cout << i << " " << st.segTree[i] << endl;
    
    return 0;
}
