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
#include <climits>
 
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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
 
const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);
 
template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }
 
void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }
 
#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif
 
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int MX = 2000;
const ld eps = 1e-7;
 
vector<pair<ld, ld> > v[MX];

struct C {
    int x, y, r, i;
 
    void del(pair<ld, ld> range) {
        if (range.f == 0 && range.s == 0) return;
        if (range.f == 0 && range.s == 1) { v[i].pb(range); return; }
        if (range.f < 0) {
            v[i].pb(mp(range.f+1, 1));
            v[i].pb(mp(0, range.s));
        } else if (range.s > 1) {
            v[i].pb(mp(range.f, 1));
            v[i].pb(mp(0, range.s-1));
        } else v[i].pb(range);
    }
};
 
C c[MX];
 
pair<ld, ld> cross(C a, C b) {
    ld dist = (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
    if (dist > (a.r+b.r)*(a.r+b.r)) return mp(0, 0); // too far
    if (dist <= (a.r-b.r)*(a.r-b.r)) { //
        if (a.r >= b.r) return mp(0, 1);
        else return mp(0, 0);
    }
    ld angle = atan2l(a.y-b.y, a.x-b.x);
    if (angle < 0) angle += 2*PI;
    assert(fabsl((ld)(b.r*b.r+dist-a.r*a.r)/(2*b.r*sqrtl(dist))) <= 1);
    ld da = acosl((ld)(b.r*b.r+dist-a.r*a.r)/(2*b.r*sqrtl(dist)));
    return mp((angle-da)/(2*PI), (angle+da)/(2*PI));
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    F0R(i, n) {
        int x, y, r; cin >> x >> y >> r;
        c[i].x = x; c[i].y = y; c[i].r = r; c[i].i = i;
//        if (i%10 == 9) dbg(i);
        F0R(j, i) {
            pair<ld, ld> p = cross(c[i], c[j]);
//            dbg(p.f*360, p.s*360);
            c[j].del(p);
        }
    }
    ld ans = 0;
//    dbg("test");
    F0R(i, n) {
        sort(all(v[i]));
//        dbg(sz(v[i]));
        ld total = 0;
        ld hi = -1, lo = -1;
        trav(r, v[i]) {
            if (r.f > hi) {
                total += (hi-lo);
                lo = r.f;
            }
            ckmax(hi, r.s);
        }
        total += (hi-lo);
//        dbg(i, total*360);
        ans += (1-total)*c[i].r;
    }
    ans *= 2*PI;
    cout.precision(12);
    cout << fixed << ans << nl;
    return 0;
}
