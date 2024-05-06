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
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 100+5;

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
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
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

int par[100+5], SZ[100+5];

int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
void merge(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (SZ[a] < SZ[b]) swap(a, b);
    SZ[a] += SZ[b];
    par[b] = a;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    F0R(i, 100+5) {
        par[i] = i;
        SZ[i] = 1;
    }
    int t;
    t = 1;
    while (t--) {
        int n, m; cin >> n >> m;
        int g[n+1][n+1];
        F0R(i, n+1) F0R(j, n+1) g[i][j] = 0;
        F0R(i, m) {
            int u, v, y; cin >> u >> v >> y;
            g[u][v] = g[v][u] = y;
            if (y == 0) merge(u, v);
        }
        ll total = 0;
        vector<pair<string, ll> > ans;
        int cnt = 0;
        while (find(1) != find(n)) {
            Dinic dnc(MX);
            FOR(i, 1, n) FOR(j, i+1, n) {
                dbg(i, j, g[i][j]);
                if (g[i][j]) {
                    dnc.addEdge(find(i), find(j), 1, 1);
                }
            }
            ll flow = dnc.calc(find(1), find(n));
            // cout << flow << nl;
            if (flow == 0) {
                cout << "inf" << nl;
                return 0;
            }
            // find the cut
            string s = "";
            FOR(i, 1, n) {
                if (dnc.leftOfMinCut(find(i))) s += '1';
                else s += '0';
            }
            vpi v;
            int lo = 1e9+1;
            FOR(i, 1, n) FOR(j, i+1, n) {
                if (s[i-1] != s[j-1] && g[i][j] > 0) {
                    dbg("cut", i, j);
                    v.pb({i, j});
                    ckmin(lo, g[i][j]);
                }
            }
            if (lo == 1e9+1) assert(0);
            trav(u, v) {
                g[u.f][u.s] -= lo;
                g[u.s][u.f] -= lo;
                if (g[u.f][u.s] == 0) {
                    dbg("merge", u.f, u.s);
                    merge(u.f, u.s);
                }
            }
            ans.pb({s, lo});
            total += lo;
            cnt++;
        }
        cout << total << " " << cnt << nl;
        for (auto x : ans) cout << x.f << " " << x.s << nl;
    }
    return 0;
}
