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
const ll INF = (1LL<<50) + 123;
const ll LLINF = (1LL<<50) + 777;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

const int MX = 2e5+5;
/*
 * Lazy Segment Tree
 * Range Invert Modification
 * Range Sum Query
 */
template <class T>
struct LazySegTree {
    int SZ;
    vector<T> segTree;
    vector<T> lazy;
    vector<T> len;
    int height;
    LazySegTree(int n) {
        SZ = n;
        F0R(i, 2*SZ) segTree.pb(0);
        F0R(i, SZ) lazy.pb(0);
        F0R(i, 2*SZ) len.pb(0);
        height = 0;
        for (ll pow = 1; pow<SZ; pow*=2) height++;
        F0R(i, SZ) len[i+SZ] = 1;
        FORd(i, 1, SZ-1) len[i] = len[i<<1]+len[i<<1|1];
    }
    void apply(int p) { // applies update to node in single function
        // cerr << "applying to " << p << endl;
        segTree[p] = len[p]-segTree[p];
        if (p < SZ) lazy[p] = !lazy[p];
    }
    void push(int p) { // pushes lazy down the tree
        for (int lev = height; lev > 0; lev--) {
            int idx = p >> lev; // get level of the parent
            if (lazy[idx] != 0) { // if there's actually something to push down
                apply(idx<<1); // push down lazy to child
                apply(idx<<1|1); // push down lazy to other child
                lazy[idx] = 0; // set lazy to 0 since you're done
            }
        }
    }
    void pull(int p) { // updates parents of node with correct values while also applying the lazy
        while (p > 1) {
            p>>=1;
            if (lazy[p]) segTree[p] = len[p] - combine(segTree[2*p], segTree[2*p+1]);
            else segTree[p] = combine(segTree[2*p], segTree[2*p+1]);
        }
    }
    void invert(int l, int r) {
        int l0 = l+SZ, r0 = r+SZ;
        for (l+=SZ, r+=SZ; l<r; l>>=1, r>>=1) {
            if (l&1) apply(l++);
            if (r&1) apply(--r);
        }
        pull(l0);
        pull(r0-1);
    }
    T query(int l, int r) {
        l+=SZ; r+=SZ;
        push(l);
        push(r-1);
        T ans = 0; // only for sums, also can do: ans = -INF;
        for (; l<r; l>>=1, r>>=1) {
            if (l&1) ans = combine(ans, segTree[l++]);
            if (r&1) ans = combine(ans, segTree[--r]);
        }
        return ans;
    }
    T combine(T a, T b) const { // template for other associative functions
        return a+b; // default is sum, also can do: max(a, b); or a > b ? a : b;
    }
    void printTree() {
        FOR(i, 1, 2*SZ-1) cerr << segTree[i] << " ";
        cerr << nl;
    }
    void printLazy() {
        FOR(i, 1, SZ-1) cerr << lazy[i] << " ";
        cerr << nl;
    }
};

vi edges[MX];
int ti[MX], to[MX];
int t = 0;
vi order; // create the preorder traversal to create the segtree on

void dfs(int v = 1) {
    ti[v] = t++;
    order.pb(v);
    trav(u, edges[v]) dfs(u);
    to[v] = t;
}
int main() {
    int n, p;
    cin >> n;
    F0R(i, n-1) {
        cin >> p;
        edges[p].pb(i+2);
    }
    dfs();
    LazySegTree<ll> t(n);
    F0R(i, n) cin >> t.segTree[ti[i+1]+n];
    F0R(i, n) t.pull(i+n);
    int q; cin >> q;
    string s; int v;
    while (q--) {
        cin >> s >> v;
        // the range is [ti[v], to[v]]
        if (s == "pow") t.invert(ti[v], to[v]);
        else cout << t.query(ti[v], to[v]) << nl;
    }
    return 0;
}
