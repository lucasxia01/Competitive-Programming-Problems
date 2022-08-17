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

const int MX = 1e5+5;
int n;
pi a[MX];
vi gr[MX], g[MX];
set<pi> edges;
int color[MX];
void build() {
    stack<pi> s;
    F0R(i, n) {
        int f = a[i].f;
        while (!s.empty() && f >= s.top().s) {
            int j = s.top().f; f -= s.top().s;
            s.pop();
            if (j != i-1) { g[j].pb(i); g[i].pb(j); edges.insert({j, i});};
            gr[i].pb(j);
            gr[j].pb(i);
        }
        if (f > 0) {
            s.top().s -= f;
            int j = s.top().f;
            if (j != i-1) { g[j].pb(i); g[i].pb(j); edges.insert({j, i});}
            gr[i].pb(j);
            gr[j].pb(i);
        }
        if (a[i].s > 0) s.push({i, a[i].s});
    }
}

bool check2(int v, int p, int c) {
    color[v] = c;
    trav(u, gr[v]) {
        if (u == p) continue;
        if (color[u] == c) return 0;
        else if (color[u] == 0) {
            if (!check2(u, v, 3-c)) return 0;
        }
    }
    return 1;
}

vi dag[MX];
void solve3() {
    queue<int> q;
    int deg[MX] = {};
    F0R(i, n) if (sz(g[i]) == 0) q.push(i);
    F0R(i, n) deg[i] = sz(g[i]);
    pi ptrs[MX]; F0R(i, n) { ptrs[i].f = (i+1)%n; ptrs[i].s = (i+n-1)%n; }
    F0R(i, n) {
        int cur = q.front(); q.pop();
        int v = ptrs[cur].f, u = ptrs[cur].s;
        dag[cur] = {v, u};
        // dbg(cur, v, u);
        ptrs[ptrs[cur].f].s = ptrs[cur].s;
        ptrs[ptrs[cur].s].f = ptrs[cur].f;
        if (edges.find({min(v, u), max(v, u)}) != edges.end()) {
            deg[v]--;
            deg[u]--;
            if (deg[v] == 0) q.push(v);
            if (deg[u] == 0) q.push(u);
        }
    }
}

bool vis[MX];
void dfs(int v) {
    vis[v] = 1;
    vi colors;
    trav(u, dag[v]) {
        if (!vis[u]) dfs(u);
        colors.pb(color[u]);
    }
    F0R(i, 3) {
        bool ok = 1;
        trav(c, colors) if (c == i+1) ok = 0;
        if (ok) {
            color[v] = i+1;
            break;
        }
    }
    // dbg(v, color[v]);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    F0R(i, n) cin >> a[i].f >> a[i].s;
    bool one = 1;
    F0R(i, n) if (a[i].f != 0) one = 0;
    if (one) {
        cout << 1 << nl;
        F0R(i, n) cout << 1 << " "; cout << nl;
        return 0;
    }
    build();
    bool two = 1;
    F0R(i, n) {
        if (!color[i]) two = (two&&check2(i, -1, 1));
    }
    if (two) {
        cout << 2 << nl;
        F0R(i, n) cout << color[i] << " "; cout << nl;
        return 0;
    }
    // three must work since its an outerplanar graph
    solve3();
    F0R(i, n) color[i] = 0;
    F0R(i, n) if (!vis[i]) dfs(i);
    cout << 3 << nl;
    F0R(i, n) cout << color[i] << " "; cout << nl;
    return 0;
}