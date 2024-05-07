#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define trav(a, x) for (auto& a : x)
#define pi pair<int,int>
#define vi vector<int>
#define rep(i,a,b) for(int i = a; i < b; i++)
#define sz(x) (int)(x).size()
#define vpi vector<pi>
#define pb push_back

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

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
int main() {
    int n, m; cin >> n >> m;
    vpi e;
    vi out[n];
    rep(i, 0, m) {
        int a, b; cin >> a >> b;
        e.pb({a, b});
        out[a].pb(i);
    }
	set<int> lower[n];
	for (int i = n-1; i >= 0; i--) {
		for (int j : out[i]) {
			int b = e[j].second;
			trav(c, lower[b]) lower[i].insert(c);
		}
		lower[i].insert(i);
	}
    int N = 2*m+5;
    Dinic dnc(N);
    int S = N-1, T = N-2;
    rep(i, 0, m) {
        dnc.addEdge(S, i, 1);
        dnc.addEdge(i+m, T, 1);
    }
    rep(i, 0, m) {
		trav(node, lower[e[i].second]) {
			for (auto j : out[node]) {
				dnc.addEdge(i, j+m, 1);
			}
		}
        
    }
    cout << m - dnc.calc(S, T) << endl;
}