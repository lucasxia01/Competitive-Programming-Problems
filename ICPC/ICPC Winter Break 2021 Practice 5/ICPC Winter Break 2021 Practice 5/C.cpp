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

const int MX = 10005;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const {
        return (-w < -o.w);
    }
};
vector<Edge> gr[MX];
int dist[MX];
vpi par[MX];
ll total = 0;
bool vis[MX];

void dfs(int v) {
    vis[v] = 1;
    trav(p, par[v]) {
        total += p.s;
        if (vis[p.f]) continue;
        vis[p.f] = 1;
        dfs(p.f);
//        dbg(v, p.f, p.s);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int p, t; cin >> p >> t;
    F0R(i, t) {
        int a, b, c;
        cin >> a >> b >> c;
        gr[a].pb({a, b, c});
        gr[b].pb({b, a, c});
    }
    F0R(i, p) dist[i] = INF;
    dist[0] = 0;
    priority_queue<pair<Edge, int> > pq;
    trav(v, gr[0]) pq.push({v, v.w});
    while (!pq.empty()) {
        pair<Edge, int> p = pq.top(); pq.pop();
        Edge e = p.f;
        if (dist[e.v] != INF) {
            if (e.w == dist[e.v]) par[e.v].pb({e.u, p.s});
            continue;
        }
        dist[e.v] = e.w;
        par[e.v].pb({e.u, p.s});
//        dbg(e.u, e.v, e.w);
        trav(v, gr[e.v]) {
//            dbg(v.u, v.v, v.w, dist[v.u]);
            Edge newv = v;
            newv.w += dist[v.u];
//            dbg("pushing in", newv.u, newv.v, newv.w, v.w, dist[v.u]);
            pq.push({newv, v.w});
        }
    }
//    cout << dist[p-1] << nl;
    dfs(p-1);
    cout << 2*total << nl;
}
