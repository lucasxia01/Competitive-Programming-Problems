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

signed main() {
    // using denom 2*n*m
    int n; cin >> n;
    vi a(n); rep(i, 0, n) cin >> a[i];
    int m; cin >> m;
    ll denom = 2*n*m;
    vi b(m); rep(i, 0, m) cin >> b[i];
    sort(all(a));
    sort(all(b));
    int j = 0;
    ll p = 0;
    rep(i, 0, n) {
        auto it = lower_bound(all(b), a[i]);
        int less = it-b.begin();
        int equal = lower_bound(all(b), a[i]+1) - it;
        p += less*2;
        p += equal;
    }
    dbg("dice 1 prob", (long double)p/(denom));
    if (p < denom/2) {
        swap(n, m);
        swap(a, b);
    }
    int i = 0;
    j = 0;
    vector<pair<ll, ll>> pts;
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
        ll curp1 = previ*m*2 + (i-previ)*m;
        ll curp2 = prevj*n*2 + (j-prevj)*n;
        pts.pb({curp1, curp2});
        dbg("pts equal", comb[k], (long double)curp1/denom, (long double)curp2/denom);
        // see if we can beat comb[k]
        if (k == n+m-1 || comb[k]+1 < comb[k+1]) {
            curp1 = i*2*m;
            curp2 = j*2*n;
            pts.pb({curp1, curp2});
            dbg("pts over", comb[k], (long double)curp1/denom, (long double)curp2/denom);
        }
    }
    sort(all(pts));
    vector<array<ll, 4>> hull;
    trav(p, pts) {
        if (hull.empty()) {
            hull.pb({p.f, p.s, 0, 1});
            continue;
        }
        if (p.f == hull.back()[0]) continue;
        ll dx = (p.f - hull.back()[0]);
        ll dy = (p.s - hull.back()[1]);
        dbg((double)p.f/denom, (double)p.s/denom, dx, dy);
        while (dy*hull.back()[3] < dx*hull.back()[2]) {
            hull.pop_back();
            assert(!hull.empty());
            dx = (p.f - hull.back()[0]);
            dy = (p.s - hull.back()[1]);
        }
        hull.pb({p.f, p.s, dy, dx});
    }
    trav(p, hull) {
        dbg("hull", (double)p[0]/denom, (double)p[1]/denom, p[2], p[3]);
    }
    i = 0;
    while (2LL*hull[i][0] < denom) {
        i++;
    }
    dbg(i);
    long double ans1 = ((long double)hull[i][1]-(long double)hull[i][2]/hull[i][3]*(hull[i][0]-denom/2))/denom;
    hull[0][2] = 1;
    hull[0][3] = 0;
    i = 0;
    while (2LL*hull[i][1] < denom) {
        i++;
    }
    dbg(i);
    long double ans2 = ((long double)hull[i][0]-(long double)hull[i][3]/hull[i][2]*(hull[i][1]-denom/2))/denom;
    cout.precision(10);
    cout << fixed << ans1 << ' ' << ans2 << nl;
}