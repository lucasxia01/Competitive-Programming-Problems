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

const int MX = 1<<20;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, 1, -1};
struct Point {
    int x, y, t, e, c;
    bool operator<(const Point& other) const {
        return tie(t, x, y, e, c) < tie(other.t, other.x, other.y, other.e, other.c);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, starte, sx, sy, c; cin >> n >> starte >> sx >> sy >> c;
    vector<Point> pts;
    Point start; start.x = sx; start.y = sy; start.t = start.e = start.c = 0;
    pts.pb(start);
    F0R(i, c) {
        Point p;
        cin >> p.x >> p.y >> p.t;
        p.e = 0; p.c = 1;
        pts.pb(p);
        F0R(d, 4) {
            Point P = p;
            P.x+=dx[d]; P.y+=dy[d];
            if (P.x < 0 || P.x >= n || P.y < 0 || P.y >= n) continue;
            P.e = 1; P.c = 0;
            pts.pb(P);
        }
    }
    sort(all(pts));
    int SZ = sz(pts);
    int MAXE = 205;
    int dp[SZ][MAXE]; // states are the point and the energy from reaching the node
    F0R(i, SZ) F0R(j, MAXE) dp[i][j] = -INF;
    dp[0][starte] = 0;
    int ans = 0;
    F0R(i, SZ) {
//        dbg_out(pts[i].t, pts[i].x, pts[i].y, pts[i].c, pts[i].e);
        F0R(E, MAXE) {
            int curC = dp[i][E];
            if (curC == -INF) continue;
//            dbg_out(i, E, curC);
            FOR(j, i+1, SZ-1) {
                int dist = abs(pts[i].x-pts[j].x)+abs(pts[i].y-pts[j].y);
                // if we don't have enough energy or time to reach the node, skip
                if (min(E, pts[j].t-pts[i].t) < dist) continue;
                int newE = E-dist+pts[j].e;
                int newC = curC+pts[j].c;
//                dbg_out(j, newE, newC);
                ckmax(dp[j][newE], newC);
                ckmax(ans, newC);
            }
        }
//        dbg_out(nl);
    }
    cout << ans << nl;
    return 0;
}
