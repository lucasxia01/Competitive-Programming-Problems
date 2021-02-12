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

void dbg_out () {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
    cerr << H << " "; dbg_out(T...);
}

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;

vi gr[MX];
int d[MX];
void dfs(int v, int p, int dist) {
    d[v] = dist;
    trav(u, gr[v]) {
        if (u != p) dfs(u, v, dist+1);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, a, b, da, db; cin >> n >> a >> b >> da >> db;
        int u, v;
        FOR(i, 1, n) gr[i].clear();
        F0R(i, n-1) {
            cin >> u >> v;
            gr[u].pb(v);
            gr[v].pb(u);
        }
        if (db <= 2*da) {
            cout << "Alice" << nl;
            continue;
        }
        dfs(1, 0, 0);
        int m = -1, maxDist = 0;
        FOR(i, 1, n) if (ckmax(maxDist, d[i])) m = i;
        memset(d, 0, sizeof d);
        dfs(m, 0, 0);
        maxDist = 0; m = -1;
        FOR(i, 1, n) if (ckmax(maxDist, d[i])) m = i;
        memset(d, 0, sizeof d);
        if (2*da >= maxDist) {
            cout << "Alice" << nl;
            continue;
        }
        dfs(b, 0, 0);
        if (d[a] <= da) {
            cout << "Alice" << nl;
            continue;
        }
        cout << "Bob" << nl;
    }
    return 0;
}
