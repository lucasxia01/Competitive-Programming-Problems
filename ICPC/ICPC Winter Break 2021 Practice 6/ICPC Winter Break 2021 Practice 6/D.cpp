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
const ll INF = (1LL<<50) + 123;
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

const int MX = 2005;
const ld eps = 1e-6;

struct Edge {
    int u, v;
    ll w;
};
vector<Edge> gr[MX];

struct HullSeg {
    ld l;
    ld r;
    ll m, b;
    vi v;
};

int used[MX][MX];
pair<ll, vi > dp[MX][MX];
void dfs(int v, int k) {
    assert(sz(dp[v][k].s));
    trav(u, dp[v][k].s) {
        if (!used[u][k-1]) {
//            dbg(v, k, u);
            used[u][k-1] = 1;
            dfs(u, k-1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    F0R(i, m) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        a--; b--;
        gr[a].pb({a, b, c});
        gr[b].pb({b, a, c});
    }
    F0R(i, n) F0R(j, n) dp[i][j] = {INF, {}};
    dp[0][0] = {0, {}};
    F0R(i, n-1) F0R(v, n) {
        trav(u, gr[v]) if (dp[u.v][i+1].f > dp[v][i].f+u.w) {
            dp[u.v][i+1].f = dp[v][i].f+u.w;
            dp[u.v][i+1].s = {u.u};
        } else if (dp[u.v][i+1].f == dp[v][i].f+u.w) {
            dp[u.v][i+1].s.pb(u.u);
        }
    }
    vector<HullSeg> segs;
    F0R(i, n) {
        HullSeg h; h.m = i; h.b = dp[n-1][i].f;
        h.v = dp[n-1][i].s;
        if (h.b == INF) continue;
        if (segs.empty()) {
            h.l = 0; h.r = INF;
            segs.pb(h);
        } else {
            // check if the right side of back
            while (!segs.empty()) {
                HullSeg h1 = segs.back();
//                    dbg(h1.m, h1.b, h.m, h.b, h1.m*h1.r+h1.b, h.m*h1.r+h.b);
                if (h1.m*h1.r+h1.b > h.m*h1.r+h.b+eps) segs.pop_back();
                else {
                    if (h1.b < h.b) break;
                    h.l = 0;
                    h.r = ((ld)h1.b-h.b)/(h.m-h1.m);
                    segs.back().l = h.r;
                    segs.pb(h);
                    break;
                }
            }
            if (segs.empty()) { // not possible
                dbg(i);
                assert(0);
            }
        }
    }
//        dbg(v);
    F0R(i, n) used[n-1][i] = 1;
    used[0][0] = 1;
    trav(h, segs) {
//        dbg(h.m, h.b, h.l, h.r);
//        trav(u, h.v) dbg(u);
        trav(u, h.v) {
            if (used[u][h.m-1]) continue;
            used[u][h.m-1] = 1;
            dfs(u, (int)h.m-1);
        }
    }
    int ans = 0; vi ansv;
    F0R(i, n) {
        bool ok = 1;
        F0R(j, n) if (used[i][j]) ok = 0;
        ans += ok;
        if (ok) ansv.pb(i);
    }
    cout << ans << nl;
    if (ans) {
        trav(i, ansv) cout << i+1 << " "; cout << nl;
    }
    return 0;
}
