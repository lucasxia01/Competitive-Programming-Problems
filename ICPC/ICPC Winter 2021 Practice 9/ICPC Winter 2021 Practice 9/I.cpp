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

typedef pair<int, int> pii;
typedef pair<ll,ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpi;
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
const ll INF = (1LL<<47) + 123;
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

int n, m, s;
ll total = 0;
ll p[MX];
vpl gr[MX];
pl sh[MX];
ll dist[10][MX];
int a[MX];

struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); } // if you need flows
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0) {
        adj[a].push_back({b, sz(adj[b]), c, c});
        adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
    }
    ll dfs(int v, int t, ll f) {
        if (v == t || !f) return f;
        for (int& i = ptr[v]; i < sz(adj[v]); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    ll calc(int s, int t) {
        ll flow = 0; q[0] = s;
        F0R(L,31) do { // 'int L=30' maybe faster for random data
            lvl = ptr = vi(sz(q));
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                int v = q[qi++];
                for (Edge e : adj[v])
                    if (!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
        } while (lvl[t]);
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

void dijk(int t) {
    priority_queue<pl> pq;
    pq.push({0, sh[t].f});
    while (!pq.empty()) {
        pl cur = pq.top(); pq.pop();
        if (dist[t][cur.s] != -1) continue;
        cur.f = -cur.f;
        dist[t][cur.s] = cur.f;
        trav(u, gr[cur.s]) {
            if (dist[t][u.f] != -1) continue;
            pq.push({-cur.f-u.s, u.f});
        }
    }
}

const int MXN = 1024+10+5;

bool check(ll mid) { // run s dijkstras and then maxflow
    Dinic dn(MXN);
    int S = MXN-1, T = MXN-2;
    memset(a, 0, sizeof a);
    F0R(i, s) {
        dn.addEdge((1<<s)+i, T, sh[i].s);
        F0R(j, n) if (dist[i][j] != -1 && dist[i][j] <= mid) a[j] += (1<<i);
    }
//    F0R(i, n) dbg(i+1, a[i]);
    ll b[1<<s]; F0R(i, 1<<s) b[i] = 0;
    F0R(i, n) b[a[i]] += p[i];
    F0R(i, 1<<s) dn.addEdge(S, i, b[i]);
    F0R(i, 1<<s) F0R(j, s) if (i&(1<<j)) dn.addEdge(i, (1<<s)+j, INF);
    ll flow = dn.calc(S, T);
    return (flow == total);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> s;
    F0R(i, n) { cin >> p[i]; total += p[i]; }
    F0R(i, m) {
        int u, v, w; cin >> u >> v >> w; u--; v--;
        gr[u].pb({v, w});
        gr[v].pb({u, w});
    }
    F0R(i, s) {
        F0R(j, n) dist[i][j] = -1;
        int a, b; cin >> a >> b; a--;
        sh[i] = {a, b};
        dijk(i);
    }
    ll lo = 0, hi = INF;
    while (lo < hi) {
        ll mid = (lo+hi)/2;
        if (check(mid)) hi = mid;
        else lo = mid+1;
    }
    cout << (lo+hi)/2 << nl;
    return 0;
}
