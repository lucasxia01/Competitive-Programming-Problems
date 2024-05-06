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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret, p;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)), p(sz(C)) {}
	void dfs(vector<vi>& C, int v, int par) {
        p[v] = par;
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

const int MX = 60;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<vi> adj(n);
    vpi e;
    F0R(i, n-1) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
        e.pb({u, v});
    }
    LCA lca(adj);
    vl W(n-1); F0R(i, n-1) cin >> W[i];
    vl w = W;
    int ans[MX][n];
    F0R(i, MX) {
        ans[i][0] = 0;
        FOR(j, 1, n-1) {
            ans[i][j] = (ans[i][j-1]^(w[j-1]&1));
            dbg(i, j, w[j-1], ans[i][j]);
        }
        F0R(j, n-1) {
            w[j] -= ans[i][j]+ans[i][j+1];
            w[j] += 2*ans[i][lca.lca(j, j+1)];
            w[j]/=2;
        }
    }
    ll x[n]; F0R(i, n) x[i] = 0;
    F0R(i, n) {
        F0R(j, MX) x[i] += (1LL<<j)*ans[j][i];
    }
    bool ok = 1;
    F0R(i, n-1) {
        if (W[i] != x[i]+x[i+1]-2LL*x[lca.lca(i,i+1)]) ok = 0;
        if (lca.p[e[i].f] == e[i].s) swap(e[i].f, e[i].s);
        if (x[e[i].s]-x[e[i].f] <= 0) ok = 0;
    }
    F0R(i, n) dbg(x[i]);
    if (!ok) cout << -1 << nl;
    else F0R(i, n-1) cout << x[e[i].s]-x[e[i].f] << nl;
    return 0;
}
