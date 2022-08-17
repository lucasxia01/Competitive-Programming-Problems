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
const ll INF = (1LL<<60) + 123;
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

const int MX = 1001;
vpl gr[MX];

struct HullSeg {
    ll l;
    ld r;
    ll m, b;
    bool type;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, x, y; cin >> n >> m >> x >> y; x--; y--;
    F0R(i, m) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        gr[u].pb({v, w});
        gr[v].pb({u, w});
    }
    bool swerc[n]; F0R(i, n) swerc[i] = 0;
    int c; cin >> c;
    F0R(i, c) {
        int cc; cin >> cc; cc--;
        swerc[cc] = 1;
    }
    
    ll dp[n][n][2]; F0R(i, n) F0R(j, n) F0R(k, 2) dp[i][j][k] = INF;
    dp[0][x][0] = 0;
    F0R(i, n-1) {
        F0R(v, n) {
            F0R(k, 2) {
                if (dp[i][v][k] == INF) continue;
                trav(u, gr[v]) {
                    ckmin(dp[i+1][u.f][k||!swerc[u.f]], dp[i][v][k]+u.s);
                }
            }
        }
    }

    ll dp1[n][n]; F0R(i, n) F0R(j, n) dp1[i][j] = INF;
    dp1[0][x] = 0;
    F0R(i, n-1) {
        F0R(v, n) {
            if (!swerc[v]) continue;
            trav(u, gr[v]) {
                if (!swerc[u.f] || dp1[i][v] == INF) continue;
                ckmin(dp1[i+1][u.f], dp1[i][v]+u.s);
//                dbg(i+1, u.f, dp1[i+1][u.f]);
            }
        }
    }
//    F0R(i, n) dbg(i, dp[i][y][1]);
//    dbg();
//    F0R(i, n) dbg(i, dp1[i][y]);
    vector<HullSeg> v;
    F0R(i, n) {
        if (min(dp[i][y][1], dp1[i][y]) == INF) continue;
        HullSeg h; h.m = i; h.b = min(dp[i][y][1], dp1[i][y]);
        if (dp[i][y][1] > dp1[i][y]) h.type = 1;
        else h.type = 0;
        if (v.empty()) {
            h.l = 0; h.r = INF;
            v.pb(h);
        } else {
            // check if the right side of back
            while (!v.empty()) {
                HullSeg h1 = v.back();
                if (h1.m*h1.r+h1.b >= h.m*h1.r+h.b) v.pop_back();
                else {
                    h.l = 0;
                    h.r = (ld)(h1.b-h.b)/(h.m-h1.m);
                    h1.l = h.r;
                    v.pb(h);
                    break;
                }
            }
            if (v.empty()) { // not possible
                dbg(i);
                assert(0);
            }
        }
    }
    ll ans = -1;
    trav(h, v) {
        if (h.type) {
            ans = h.r;
            if (ans != INF && (ll)h.r == h.r) ans--;
            break;
        }
    }
    if (ans == INF) cout << "Infinity" << nl;
    else if (ans <= 0) cout << "Impossible" << nl;
    else cout << ans << nl;
    return 0;
}
