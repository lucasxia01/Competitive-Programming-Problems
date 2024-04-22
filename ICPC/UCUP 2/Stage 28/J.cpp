#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define trav(a, x) for(auto& a : x)
#define f first
#define s second
#define pb push_back
const char nl = '\n';

#ifdef DBG
void dbg_out() { cerr << nl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<vi> treeJump(vi& P) {
    int on = 1, d = 1;
    while (on < sz(P)) on *= 2, d++;
    vector<vi> jmp(d, P);
    rep(i, 1, d) rep(j, 0, sz(P)) {
        jmp[i][j] = jmp[i-1][jmp[i-1][j]];
    }
    return jmp;
}

int jmp(vector<vi>& tbl, int nod, int steps) {
    rep(i, 0, sz(tbl)) 
        if (steps&(1<<i)) nod = tbl[i][nod];
    return nod;
}

int lca(vector<vi>& tbl, vi& depth, int a, int b) {
    if (depth[a]  < depth[b]) swap(a, b);
    a = jmp(tbl, a, depth[a]-depth[b]);
    if (a == b) return a;
    for (int i = sz(tbl); i--;) {
        int c = tbl[i][a], d = tbl[i][b];
        if (c != d) a = c, b = d;

    }
    return tbl[0][a];
}
const int MX = 1e5;
vi gr[MX];

vi par;
vi depth;
vi numCh;
void dfs(int v, int p, int dep) {
    par[v] = p;
    depth[v] = dep;
    trav(u, gr[v]) {
        if (u == p) continue;
        dfs(u, v, dep+1);
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        gr[u].pb(v);
        gr[v].pb(u);
    }
    par.resize(n, 0);
    depth.resize(n, 0);
    numCh.resize(n, 0);
    rep(i, 1, n) numCh[i] = sz(gr[i])-1;
    numCh[0] = sz(gr[0]);
    dfs(0, 0, 0);
    trav(x, par) dbg(x);
    auto tbl = treeJump(par);
    vi cnt(n, 0);
    while (q--) {
        int k; cin >> k;
        vi v;
        set<int> distinct;
        set<int> extra_dead;
        rep(i, 0, k) {
            int x; cin >> x;
            x--;
            distinct.insert(x);
            v.pb(x);
        }
        int node = v[0];
        bool ok = 1;
        if (sz(distinct) != k) ok = 0;
        set<int> touched;
        int curRoot = v[0];
        rep(i, 0, k-1) {
            // check stuff
            int cur = v[i];
            int nxt = v[i+1];
            if (nxt == 0) {
                ok = 0;
                break;
            }
            bool done = (cnt[node] == numCh[node]);
            bool moveup = 0;
            while (done) {
                // move up the tree
                if (node == curRoot) {
                    moveup = 1;
                    break;
                }
                if (node == 0) {
                    ok = 0;
                    break;
                }
                dbg(node);
                node = par[node];
                cnt[node]++;
                touched.insert(node);
                done = (cnt[node] == numCh[node]);
            }
            dbg(cur, nxt, node, moveup);
            if (moveup) {
                // find the lca of cur and nxt
                dbg(cur, nxt);
                int l = lca(tbl, depth, cur, nxt);
                // find the node right under the lca that is ancestor of cur
                if (par[nxt] != l) ok = 0;
                int diff = depth[cur]-depth[l];
                int under = jmp(tbl, cur, diff-1);
                dbg("under", under);
                extra_dead.insert(under);
                node = nxt;
                curRoot = nxt;
            } else {
                // not done so we move to the child
                // check that nxt is a child of cur
                if (par[nxt] != node) {
                    ok = 0;
                    break;
                }
                node = nxt;
            }
            if (extra_dead.count(nxt)) ok = 0;
            dbg(node, nxt);
            assert(node == nxt);
        }

        cout << (ok?"Yes":"No") << nl;

        // reset the cnts
        trav(x, touched) cnt[x] = 0;
    }
}