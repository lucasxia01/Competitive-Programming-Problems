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
const int MX = 1<<20;
const ll INF = (1LL<<40) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <class T> bool ckmin(T& a, const T& b) {
    return a < b ? 0 : a=b, 1;
}
template <class T> bool ckmax(T& a, const T& b) {
    return a > b ? 0 : a=b, 1;
}

/*
 * Lazy Segment Tree
 * Range Increment Modification
 * Range Max and Sum Query
 * Supports ints and long longs
 */
template <class T, int SZ>
struct LazySegTree {
    T t[2*SZ];
    T d[SZ];
    int h;
    int n;
    LazySegTree() {
        F0R(i, 2*SZ) t[i] = 0;
        F0R(i, SZ) d[i] = 0;
        h = 0;
        ll pow = 1;
        while (pow<SZ) {
            h++;
            pow*=2;
        }
        n = SZ;
    }
    void apply(int p, T value) {
      t[p] += value;
      if (p < n) d[p] += value;
    }

    void build(int p) {
      while (p > 1) p >>= 1, t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
    }

    void push(int p) {
      for (int s = h; s > 0; --s) {
        int i = p >> s;
        if (d[i] != 0) {
          apply(i<<1, d[i]);
          apply(i<<1|1, d[i]);
          d[i] = 0;
        }
      }
    }

    void inc(int l, int r, T value) {
      l += n, r += n;
      int l0 = l, r0 = r;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) apply(l++, value);
        if (r&1) apply(--r, value);
      }
      build(l0);
      build(r0 - 1);
    }

    ll query(int l, int r) {
      l += n, r += n;
      push(l);
      push(r - 1);
      ll res = -2e9;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) ckmax(res, t[l++]);
        if (r&1) ckmax(res, t[--r]);
      }
      return res;
    }
};

LazySegTree<ll, MX> lst;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, p, x, y, z;
    cin >> n >> m >> p;
    pi att[n], def[m];
    F0R(i, n) cin >> att[i].f >> att[i].s;
    F0R(i, m) cin >> def[i].f >> def[i].s;
    sort(att, att+n);
    sort(def, def+n);
    ll cost[MX];
    F0R(i, MX) cost[i] = INF;
    trav(a, def) if (cost[a.f] > a.s) cost[a.f] = a.s;
    F0R(i, MX) if (cost[i] != INF) lst.inc(i, i+1, INF-cost[i]);
    ll ans = -INF;
    int curAtt = 0;
    vector<vector<int>> mn(p);
    F0R(i, p) {
        cin >> x >> y >> z;
        mn[i].pb(x);
        mn[i].pb(y);
        mn[i].pb(z);
    }
    sort(mn.begin(), mn.end());
    F0R(i, p+1) {
        ll hi = lst.query(0, MX);
//        FOR(i, 1, 10) {
//            cout << lst.query(i, i+1)-INF << " ";
//        } cout << endl;
        while (curAtt < n && (i == p || att[curAtt].f <= mn[i][0])) {
            ckmax(ans, hi-att[curAtt].s);
            //cout << hi-att[curAtt].s-INF << endl;
            curAtt++;
        }
        if (i < p) lst.inc(mn[i][1]+1, MX, mn[i][2]);
    }
    cout << ans-INF << endl;
    return 0;
}
