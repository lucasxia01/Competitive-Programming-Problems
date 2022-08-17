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
typedef pair<ld,ld> pld;

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
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			F0R(j,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

vpi times[MX];

struct LCA {
	int T = 0;
	vi time, path, ret, depth, p;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1,0), ret)), depth(sz(C)), p(sz(C)) {}
	void dfs(vector<vi>& C, int v, int par, int d) {
        p[v] = par;
		time[v] = T++;
        depth[v] = d;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v, d+1);
            times[v].pb({time[y], y});
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	int dist(int a, int b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

vector<vi> gr;
map<pi, pld> M;

pld solve(int v, int u) { // u -> v
    if (M.find({u, v}) != M.end()) return M[{u, v}];
    ld total = 0;
    int size = 1;
    trav(w, gr[v]) {
        if (w == u) continue;
        pld p = solve(w, v);
        total += (p.f+1)*p.s;
        size += p.s;
    }
    pld ret = {total/size, size};
    M[{u, v}] = ret;
    dbg(u, v, ret.f, ret.s);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    F0R(i, n) {
        vi temp;
        gr.pb(temp);
    }
    vpi e;
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        gr[u].pb(v);
        gr[v].pb(u);
        e.pb({u, v});
        e.pb({v, u});
    }
    trav(ee, e) solve(ee.f, ee.s);
    LCA l(gr);
    F0R(i, n) sort(all(times[i]));
    while (m--) {
        int u, v; cin >> u >> v;
        u--; v--;
        int lca = l.lca(u, v);
        int pathlen = l.dist(u, v);
        dbg(lca, pathlen);
        // find x and y on the path of u and v;
        int x = -1, y = -1;
        if (lca == u) {
            pi temp = {l.time[v], INF};
            x = (--upper_bound(times[u].begin(), times[u].end(), temp))->s;
            y = l.p[v];
        } else if (lca == v) {
            x = l.p[u];
            pi temp = {l.time[u], INF};
            y = (--upper_bound(times[v].begin(), times[v].end(), temp))->s;
        } else {
            x = l.p[u];
            y = l.p[v];
        }
        dbg(x+1, u+1, y+1, v+1);
        ld ans = pathlen + 1 + M[{x, u}].f + M[{y, v}].f;
        cout.precision(10);
        cout << fixed << ans << nl;
    }
    return 0;
}
