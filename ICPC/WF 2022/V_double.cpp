#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define trav(a, x) for(auto& a: x)
#define pb push_back
#define f first 
#define s second 
using ld = long double;
typedef long long ll;
#define int ll
typedef pair<int, int> pii;
typedef vector<int> vi;

const char nl = '\n';

#ifdef DBG
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const ld eps = 1e-12;
signed main() {
    int n; cin >> n;
    vi a(n); rep(i, 0, n) cin >> a[i];
    int m; cin >> m;
    vi b(m); rep(i, 0, m) cin >> b[i];
    sort(all(a));
    sort(all(b));
    int j = 0;
    ld p = 0;
    rep(i, 0, n) {
        auto it = lower_bound(all(b), a[i]);
        int less = it-b.begin();
        int equal = lower_bound(all(b), a[i]+1) - it;
        p += (ld)less/(1LL*m*n);
        p += (ld)equal/(2LL*m*n);
    }
    dbg("dice 1 prob", p);
    if (p < 0.5) {
        swap(n, m);
        swap(a, b);
    }
    int i = 0;
    j = 0;
    vector<pair<ld, ld>> pts;
    vi comb = a;
    trav(u, b) comb.pb(u);
    sort(all(comb));
    if (comb[0] != 1) pts.pb({0, 0});
    rep(k, 0, n+m) {
        if (k != n+m-1 && comb[k] == comb[k+1]) continue;
        int previ = i, prevj = j;
        while (i < n && a[i]==comb[k]) {
            i++;
        }
        while (j < m && b[j]==comb[k]) j++;
        ld curp1 = (ld)previ/n + (ld)(i-previ)/(2*n);
        ld curp2 = (ld)prevj/m + (ld)(j-prevj)/(2*m);
        pts.pb({curp1, curp2});
        dbg("pts equal", comb[k], curp1, curp2);
        // see if we can beat comb[k]
        if (k == n+m-1 || comb[k]+1 < comb[k+1]) {
            curp1 = (ld)i/n;
            curp2 = (ld)j/m;
            pts.pb({curp1, curp2});
            dbg("pts over", comb[k], curp1, curp2);
        }
    }
    sort(all(pts));
    vector<array<ld, 3>> hull;
    trav(p, pts) {
        if (hull.empty()) {
            hull.pb({p.f, p.s, 0});
            continue;
        }
        ld dx = (p.f-hull.back()[0]);
        ld dy = (p.s-hull.back()[1]);
        if (dx < eps) continue;
        while (dy < hull.back()[2]*dx) {
            hull.pop_back();
            assert(!hull.empty());
            dx = (p.f-hull.back()[0]);
            dy = (p.s-hull.back()[1]);
        }
        hull.pb({p.f, p.s, dy/dx});
    }
    trav(p, hull) {
        dbg("hull", p[0], p[1], p[2]);
    }
    i = 0;
    while (hull[i][0] < 0.5) {
        i++;
    }
    ld ans1 = (ld)hull[i][1]-hull[i][2]*(hull[i][0]-0.5);
    i = 0;
    while (hull[i][1] < 0.5) {
        i++;
    }
    ld ans2;
    if (i == 0) ans2 = (ld)hull[i][0];
    else ans2 = (ld)hull[i][0] - (ld)1/hull[i][2]*(hull[i][1]-0.5);
    cout.precision(10);
    cout << fixed << ans1 << ' ' << ans2 << nl;
}