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
#include <random>
#include <chrono>
#include <cassert>

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
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 55;
const ld eps = 1e-5;

int par[MX], sze[MX];
int find(int p) {
    return (p == par[p] ? p : (par[p]=find(par[p])));
}

void merge(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sze[a] < sze[b]) swap(a, b);
    sze[a] += sze[b];
    par[b] = a;
}


struct Circle {
    ll x, y, r;
    bool intersect(const Circle& o) const {
        return ((x-o.x)*(x-o.x)+(y-o.y)*(y-o.y) <= (r+o.r)*(r+o.r) &&
                (x-o.x)*(x-o.x)+(y-o.y)*(y-o.y) >= (r-o.r)*(r-o.r));
    }
    bool touch(const Circle& o) const {
        return ((x-o.x)*(x-o.x)+(y-o.y)*(y-o.y) == (r+o.r)*(r+o.r));
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("circles.in", "r", stdin);
//    freopen("circles.out", "w", stdout);
    int n; cin >> n;
    Circle c[n]; F0R(i, n) cin >> c[i].x >> c[i].y >> c[i].r;
    int e = 0;
    vector<pair<ld, ld> > pts;
    F0R(i, n) {
        par[i] = i;
        sze[i] = 1;
    }
    F0R(i, n) {
        vector<pair<ld, ld> > v;
        F0R(j, n) { // find intersection points
            if (i == j || !c[i].intersect(c[j])) continue;
            merge(i, j);
            ld d, a, h;
            d = sqrtl((c[i].x-c[j].x)*(c[i].x-c[j].x)+(c[i].y-c[j].y)*(c[i].y-c[j].y));
            assert(d);
            a = (c[i].r*c[i].r - c[j].r*c[j].r + d*d)/(2*d);
            h = sqrt(c[i].r*c[i].r - a*a);
            ld p2x = (c[j].x-c[i].x)*a/d+c[i].x;
            ld p2y = (c[j].y-c[i].y)*a/d+c[i].y;
            ld x3, y3, x4, y4;
            x3 = p2x + h*(c[j].y - c[i].y)/d;
            y3 = p2y - h*(c[j].x - c[i].x)/d;
            x4 = p2x - h*(c[j].y - c[i].y)/d;
            y4 = p2y + h*(c[j].x - c[i].x)/d;
//            cout << i << " " << x3 << " " << y3 << " " << x4 << " " << y4 << nl;
            bool ok = 1;
            trav(p, v) if (fabsl(p.f-x3) < eps && fabsl(p.s-y3) < eps) ok = 0;
            if (ok) v.pb({x3, y3});
            ok = 1;
            trav(p, v) if (fabsl(p.f-x4) < eps && fabsl(p.s-y4) < eps) ok = 0;
            if (ok) v.pb({x4, y4});
        }
        e += sz(v);
        trav(p, v) {
            bool ok = 1;
            trav(p2, pts) if (fabsl(p.f-p2.f) < eps && fabsl(p.s-p2.s) < eps) ok = 0;
            if (ok) pts.pb(p);
        }
    }
    int comps = 0;
    F0R(i, n) if (par[i] == i) comps++;
//    cout << comps << " " << e << " " << sz(pts) << nl;
    cout << e+2-sz(pts)+comps-1 << nl;
    return 0;
}
