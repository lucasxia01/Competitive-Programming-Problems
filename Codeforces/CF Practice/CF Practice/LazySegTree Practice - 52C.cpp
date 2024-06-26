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

const char nl = '\n';
const int MAX_N = 200011;
const ll INF = (1LL<<50) + 123;
const ll LLINF = (1LL<<50) + 777;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

/*
 * Lazy Segment Tree
 * Range Increment Modification
 * Range Min Query
 * Supports ints and long longs
 */
template <class T>
struct LazySegTree {
    int SZ;
    vector<T> segTree;
    vector<T> lazy;
    int height;
    LazySegTree(int n) {
        SZ = n;
        F0R(i, SZ) segTree.pb(INF);
        F0R(i, SZ) {
            lazy.pb(0);
            segTree.pb(INF);
        }
        height = 0;
        ll pow = 1;
        while (pow<SZ) {
            height++;
            pow*=2;
        }
    }
    void apply(int p, T v) { // applies update to node in single function
        //cout << "applying " << v << " to " << p << endl;
        segTree[p] = segTree[p] + v;
        if (p < SZ) lazy[p] = lazy[p] + v;
    }
    void push(int p) { // pushes lazy down the tree
        for (int lev = height; lev > 0; lev--) {
            int idx = p >> lev; // get level of the parent
            if (lazy[idx] != 0) { // if there's actually something to push down
                apply(idx<<1, lazy[idx]); // push down lazy to child
                apply(idx<<1|1, lazy[idx]); // push down lazy to other child
                lazy[idx] = 0; // set lazy to 0 since you're done
            }
        }
    }
    void pull(int p) { // updates parents of node with correct values while also applying the lazy
        while (p > 1) p>>=1, segTree[p] = combine(segTree[2*p], segTree[2*p+1]) + lazy[p];
    }
    void upd(int p, T v) {
        upd(p, p+1, v);
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
    T query(int p) {
        return query(p, p+1);
    }
    T query(int l, int r) {
        l+=SZ; r+=SZ;
        push(l);
        push(r-1);
        T ans;
        ans = INF; // only for sums, also can do: ans = -INF;
        for (; l<r; l>>=1, r>>=1) {
            if (l&1) ans = combine(ans, segTree[l++]);
            if (r&1) ans = combine(ans, segTree[--r]);
        }
        return ans;
    }
    T combine(T a, T b) const { // template for other associative functions
        return a > b ? b : a; // default is sum, also can do: max(a, b); or a > b ? a : b;
    }
};

int main() {
    int n;
    cin >> n;
    LazySegTree<ll> t(n);
    F0R(i, n) cin >> t.segTree[i+n];
    F0R(i, n) t.pull(i+n);
    int m, l, r;
    cin >> m;
    string s;
    getline(cin, s);
    while (m--) {
        getline(cin, s);
        istringstream is(s);
        vector<int> v = vector<int>(istream_iterator<int>(is), istream_iterator<int>());
        l = v[0]; r = v[1];
        // cout << l << " " << r << endl;
        if (l <= r) {
            if (sz(v) == 2) cout << t.query(l, r+1) << nl;
            else t.upd(l, r+1, v[2]);
        } else {
            if (sz(v) == 2) {
                cout << min(t.query(l, n), t.query(0, r+1)) << nl;
            } else {
                t.upd(l, n, v[2]);
                t.upd(0, r+1, v[2]);
            }
        }
    }
    return 0;
}
