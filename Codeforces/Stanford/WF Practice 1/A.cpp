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
typedef pair<ld,ld> pld;

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
const ll INF = (ll)1e18+5;
const ll MOD = 2520; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MXN = 1000+5;

ll k[MXN];
ll dp[MXN][MOD]; // after adding the current node
ll mark[MXN][MOD];
vi gr[MXN];
vi order;

int solve (int v, int x, int p) {
    order.pb(v);
    x = (x%MOD+MOD)%MOD;
    if (dp[v][x] > 0) return dp[v][x];
    else if (dp[v][x] == -1) {
        set<int> S;
        for (int i = mark[v][x]; i < p; i++) S.insert(order[i]);
        return sz(S);
    }
    dp[v][x] = -1;
    // find next state
    int nv = gr[v][x%sz(gr[v])];
    ll nx = (x + k[nv]);
    // dbg(v, x, nv, nx);
    mark[v][x] = p;
    dp[v][x] = solve(nv, nx, p+1);
    return dp[v][x];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    F0R(i, n) {
        cin >> k[i];
        k[i] = (k[i]%MOD+MOD)%MOD;
    }
    F0R(i, n) {
        int m; cin >> m;
        F0R(j, m) {
            int x; cin >> x; x--;
            gr[i].pb(x);
        }
    }
    int q; cin >> q;
    while (q--) {
        int x; ll y; cin >> x >> y;
        x--;
        y += k[x];
        y = (y%MOD+MOD)%MOD;
        if (dp[x][y]) cout << dp[x][y] << nl;
        else {
            order.clear();
            cout << solve(x, y, 0) << nl;
        }
    }
    return 0;
}
