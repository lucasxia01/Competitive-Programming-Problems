#include<bits/stdc++.h>
using namespace std;

#define F0R(i, n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
typedef long long ll;
#define sz(x) (int)(x).size()
#define vi vector<int>

const int MX = 7e3 + 5;

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

vector<int> gr[MX];

bool vis[MX];

int par[MX], SZ[MX];

int find(int x) {
    return (x==par[x]?x:par[x]=find(par[x]));
}

void merge(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (SZ[a] < SZ[b]) swap(a, b);
    par[b] = a;
    SZ[a] += SZ[b];
}

void dfs(int v) {
    vis[v] = 1;
    for (int u : gr[v]) {
        if (vis[u]) continue;
        dfs(u);
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    F0R(i, m) {
        int a, b; cin >> a >> b;
        a--; b--;
        gr[a].push_back(b);
    }
    Dinic dnc(2*n+5);
    int s = 2*n+3, t = 2*n+4;

    F0R(i, n) {
        F0R(j, n) vis[j] = 0;
        dfs(i);
        F0R(j, n) if (vis[j] && i != j) {
            dnc.addEdge(i, j+n, 1);
        }
    }
    F0R(i, n) {
        dnc.addEdge(s, i, 1);
        dnc.addEdge(i+n, t, 1);
    }
    int flow = dnc.calc(s, t);
    F0R(i, MX) {
        par[i] = i;
        SZ[i] = 1;
    }
    F0R (a, n) {
        for (auto x : dnc.adj[a]) {
            if (x.flow() > 0 && x.to >= n && x.to < 2*n) {
                // cerr << a << " " << x.rev << endl;
                merge(a, x.to - n);
            }
        }
    }
    map<int, int> M;
    F0R(i, n) {
        if (find(i) == i) {
            int S = sz(M);
            M[i] = S+1;
        }
    }
    F0R(i, n) {
        cout << M[find(i)] << " ";
    } cout << endl;
}