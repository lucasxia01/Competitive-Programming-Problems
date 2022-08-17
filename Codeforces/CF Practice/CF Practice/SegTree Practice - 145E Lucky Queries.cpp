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
const ll INF = (1<<29) + 123;
const ll LLINF = (1LL<<50) + 777;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

/*
 * Lazy Segment Tree
 * Range Increment Modification
 * Range Sum or Max Query
 * Supports ints and long longs
 
 * Range Min Query Verified 3/5/20 by https://codeforces.com/contest/1295/submission/72543936
 */
const int MX = 1<<20;
template <class T>
struct LazySegTree {
    int SZ;
    T t[2*MX][4], d[MX]; // 0 is longest inc subsequence, 1 is longest dec subsequence, 2 is number of 4s, 3 is number of 7s
    int height;
    LazySegTree(int n) {
        SZ = n;
        F0R(i, 2*SZ) F0R(j, 4) t[i][j] = -INF;
        F0R(i, SZ) d[i] = 0;
        height = 0;
        for (ll pow = 1; pow<SZ; pow*=2) height++;
    }
    void apply(int p) { // applies update to node in single function
        swap(t[p][0], t[p][1]);
        swap(t[p][2], t[p][3]);
        if (p < SZ) d[p] = !d[p];
    }
    void pull(int p) { // updates parents of node with correct values while also applying the lazy
        while (p > 1) {
            p>>=1;
            int fst = p<<1;
            int snd = fst|1;
            t[p][0] = max(t[fst][0]+t[snd][3], t[fst][2]+t[snd][0]);
            t[p][1] = max(t[fst][1]+t[snd][2], t[fst][3]+t[snd][1]);
            t[p][2] = t[fst][2] + t[snd][2];
            t[p][3] = t[fst][3] + t[snd][3];
            if (d[p]) {
                swap(t[p][0], t[p][1]);
                swap(t[p][2], t[p][3]);
            }
            
        }
    }
    void upd(int l, int r) {
        int l0 = l+SZ, r0 = r+SZ;
        for (l+=SZ, r+=SZ; l<r; l>>=1, r>>=1) {
            if (l&1) apply(l++);
            if (r&1) apply(--r);
        }
        pull(l0);
        pull(r0-1);
    }
    T query() {
        return t[1][0];
    }
};


int main() {
    int n, q; char s[MX];
    scanf("%d%d%s", &n, &q, s);
    int a[n]; F0R(i, n) if (s[i] == '7') a[i] = 1; else a[i] = 0;
    int pow = 1; for (; pow < n; pow*=2);
    LazySegTree<int> t(pow);
    F0R(i, pow) {
        if (i >= n) {
            F0R(j, 4) t.t[i+pow][j] = 0;
            continue;
        }
        t.t[i+pow][0] = t.t[i+pow][1] = 1;
        t.t[i+pow][2] = (a[i] == 0);
        t.t[i+pow][3] = (a[i] == 1);
    }
    F0R(i, pow) t.pull(i+pow);
    int l, r;
    char str[8];
    F0R(i, q) {
        scanf("%s", str);
        if (str[0] == 'c') printf("%d\n", t.query());
        else {
            scanf("%d%d", &l, &r);
            t.upd(l-1, r);
        }
    }
    return 0;
}

