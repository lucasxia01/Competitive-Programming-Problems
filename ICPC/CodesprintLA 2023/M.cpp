#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

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
#define rep(i, a, b) for(int i = a; i < (b); ++i)

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
const ll INF = 1e17 + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){
	c << "(" << v.fi << "," <<v.se <<")"; return c;
}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){
	out << "{ ";
	trav(x,c) out<<x<<" ";
	out<<"}"; return out;
}
#else
#define dbg(...)
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;

int n, l;
vector<vector<pi>> adj(MX);

int timer;
vector<int> tin, tout;
vector<vector<int>> up;
vector<vector<int>> d;

void dfs(int v, int p, int dist)
{
    tin[v] = ++timer;
    up[v][0] = p;
    d[v][0] = dist;
    for (int i = 1; i <= l; ++i) {
        up[v][i] = up[up[v][i-1]][i-1];
        d[v][i] = d[v][i-1] + d[up[v][i-1]][i-1];
    }
    for (auto u : adj[v]) {
        if (u.f != p) {
            dfs(u.f, v, u.s);
        }
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

int compute_dist(int u, int v) {
    if (u == v) return 0;
    assert(is_ancestor(v, u)); // v is the ancestor of u
    int ans = 0;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            ans += d[u][i];
            u = up[u][i];
        }
    }
    return ans + d[u][0];
}

void preprocess(vi roots) {
    tin.resize(n+1);
    tout.resize(n+1);
    timer = 0;
    l = ceil(log2(n+1));
    up.assign(n+1, vector<int>(l + 1));
    d.assign(n+1, vector<int>(l + 1));

    trav(root, roots) {
        dbg("dfsing", root);
        dfs(root, root, 0);
        dbg("dfsing done");
        timer++;
    }
}

int parent2[MX], SZ2[MX];

int find_set2(int v) {
    if (v == parent2[v])
        return v;
    return (parent2[v] = find_set2(parent2[v]));
}
void make_set2(int v) {
    parent2[v] = v;
    SZ2[v] = 1;
}

void union_sets2(int a, int b) {
    a = find_set2(a);
    b = find_set2(b);
    if (a != b) {
        if (SZ2[a] < SZ2[b])
            swap(a, b);
        parent2[b] = a;
        SZ2[a] += SZ2[b];
    }
}

int parent[MX], SZ[MX];

int find_set(int v) {
    if (v == parent[v])
        return v;
    return (parent[v] = find_set(parent[v]));
}
void make_set(int v) {
    parent[v] = v;
    SZ[v] = 1;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (SZ[a] < SZ[b])
            swap(a, b);
        parent[b] = a;
        SZ[a] += SZ[b];
    }
}


vpi gr[MX];
vi comps[MX];
vi cycles[MX];
vi dists[MX];
int root_map[MX];
map<int, int> cycle_index[MX];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n; // nodes are 1-indexed
    FOR(i, 1, n) {
        make_set(i);
        make_set2(i);
    }
    F0R(i, n) {
        int j, t; cin >> j >> t;
        gr[i+1].pb({j, t});
        gr[j].pb({i+1, t});
        union_sets(i+1, j);
    }
    // find components
    FOR(i, 1, n) {
        // dbg("one", i, find_set(i));
        comps[find_set(i)].pb(i);
    }
    vi allroots;
    // for each comp, need to dissect into trees by finding the cycle through top sort
    FOR(i, 1, n) {
        if (sz(comps[i]) == 0) continue;
        dbg("comp", i);
        dists[i].pb(0);
        // top sort
        map<int, int> deg;
        queue<int> q;
        trav(v, comps[i]) {
            deg[v] = sz(gr[v]);
            if (deg[v] == 1) q.push(v);
        }

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto [u, t] : gr[v]) {
                deg[u]--;
                if (deg[u] == 1) q.push(u);
            }
        }
        // if deg > 1, its in cycle, if not, its in a tree
        int cur = -1;
        trav(v, comps[i]) {
            if (deg[v] > 1) {
                dbg(v, deg[v]);
                cur = v;
            }
        }
        assert(cur != -1);
        int prev = -1;
        int start = cur;
        // now find the cycle
        vi cycle, lens;
        dbg("two", cur, deg[cur]);
        do {
            // get next
            bool ok = 0;
            pi store;
            trav(nxt, gr[cur]) {
                // dbg("three", cur, nxt.f, deg[nxt.f]);
                if (deg[nxt.f] > 1 && nxt.f != prev) {
                    // dbg(cur, nxt.f);
                    cycle.pb(nxt.f); lens.pb(nxt.s);
                    prev = cur;
                    cur = nxt.f;
                    ok = 1;
                    break;
                } else if (deg[nxt.f] > 1) {
                    store = nxt;
                }
            }
            if (!ok) { // cycle len = 2
                cycle.pb(store.f); lens.pb(store.s);
                break;
            }
        } while (cur != start);
        dbg("cycle", i);
        F0R(j, sz(cycle)) {
            dbg("in cycle", cycle[j], lens[j]);
            cycles[i].pb(cycle[j]);
            dists[i].pb(lens[j] + dists[i].back());
            allroots.pb(cycle[j]);
            cycle_index[i][cycle[j]] = j;
        }
        dbg("here");
        // now lca time
        // for all nodes with deg < 2, merge into components
        trav(v, comps[i]) {
            if (deg[v] <= 1) {
                trav(u, gr[v]) {
                    union_sets2(u.f, v);
                    adj[u.f].pb({v, u.s});
                    if (deg[u.f] > 1) adj[v].pb({u.f, u.s});
                }
            }
        }
        dbg("end");
    }
    preprocess(allroots);
    trav(root, allroots) {
        root_map[find_set2(root)] = root;
    }
    dbg("preprocessed");

    
    int L; cin >> L;
    int djik[L][n+1];
    vpi GR[n+1];
    FOR(j, 1, n) GR[j] = gr[j];
    vi vv;
    F0R(i, L) {
        F0R(j, n+1) djik[i][j] = INF;
        int x, y, t; cin >> x >> y >> t;
        // dijkstra from all x's
        GR[x].pb({y, t});
        GR[y].pb({x, t});
        vv.pb(x);
    }
    int idx = 0;
    trav(u, vv) {
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        pq.push({0, u});
        while (!pq.empty()) {
            pi cur = pq.top(); pq.pop();
            if (djik[idx][cur.s] != INF) continue;
            djik[idx][cur.s] = cur.f;
            trav(o, GR[cur.s]) {
                if (djik[idx][o.f] != INF) continue;
                pq.push({cur.f + o.s, o.f});
            }
        }
        idx++;
    }
    int q; cin >> q;
    while (q--) {
        int a, b; cin  >> a >> b;
        int ans = INF;
        if (find_set(a) == find_set(b)) {
            int comp = find_set(a);
            // check if they're in the same tree
            if (find_set2(a) == find_set2(b)) {
                int l = lca(a, b);
                dbg(a, b, l, compute_dist(a, l), compute_dist(b, l));
                ckmin(ans, compute_dist(a, l) + compute_dist(b, l));
            } else { // mf
                int r1 = root_map[find_set2(a)];
                int r2 = root_map[find_set2(b)];

                // r1 to r2???
                int tmp =  compute_dist(a, r1) + compute_dist(b, r2);
                int idx1 = cycle_index[comp][r1], idx2 = cycle_index[comp][r2];
                // get prefix sum diff
                if (idx1 > idx2) swap(idx1, idx2);
                int d1 = dists[comp][idx2 + 1] - dists[comp][idx1 + 1];
                int d2 = dists[comp].back() - d1;
                ckmin(ans, tmp + min(d1, d2));
            }
        }
        F0R(i, L) {
            ckmin(ans, djik[i][a] + djik[i][b]);
        }
        if (ans == INF) cout << -1 << nl;
        else cout << ans << nl;
    }
    return 0;
}