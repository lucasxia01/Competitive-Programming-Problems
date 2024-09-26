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

const int MX = 1<<20;

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a^b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
        // dbg(b, e-1);
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

class HLD {
    public:
    HLD (int n, vector<vi> gr, vi v) : gr(gr), st(n), idx(n, -1), s(n, 0), h(n, -1), par(n, -1), chain_root(n, -1) {
        dfs1(0, -1, 0);
        dfs2(0, -1, 0, 0);
        // F0R(i, n) dbg(i, idx[i], chain_root[i], h[i], s[i], par[i]);
        F0R(i, n) st.update(idx[i], v[i]);
    }
    void update(int i, int v) {
        st.update(idx[i], v);
    }
    int query(int i, int j) {
        if (h[chain_root[i]] < h[chain_root[j]]) return query(j, i);
        if (chain_root[i] == chain_root[j]) {
            if (idx[j] > idx[i]) swap(i, j);
            return st.query(idx[j], idx[i]+1);
        }
        int nxt = par[chain_root[i]];
        return (st.query(idx[chain_root[i]], idx[i]+1)^query(nxt, j));
    }
    private:
    Tree st;
    vi idx, s, h, par, chain_root;
    vector<vi> gr;
    
    int dfs1(int v, int p, int l) {
        par[v] = p;
        h[v] = l;
        int sum = 1;
        trav(u, gr[v]) {
            if (u == p) continue;
            sum += dfs1(u, v, l+1);
        }
        s[v] = sum;
        return sum;
    }
    void dfs2(int v, int p, int r, int i) {
        chain_root[v] = r;
        idx[v] = i;
        int heavy = -1, m = 0;
        trav(u, gr[v]) {
            if (u == p) continue;
            if (ckmax(m, s[u])) heavy = u;
        }
        if (heavy == -1) return;
        dfs2(heavy, v, r, i+1);
        i += s[heavy];
        trav(u, gr[v]) {
            if (u == p) continue;
            if (u != heavy) {
                dfs2(u, v, u, i+1);
                i += s[u];
            }
        }
    }
};

int main() {
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    vi a(n); F0R(i, n) cin >> a[i];
    int u, v;
    vector<vi> gr(n);
    F0R(i, n-1) {
        cin >> u >> v; u--; v--;
        gr[u].pb(v);
        gr[v].pb(u);
    }
    HLD hld(n, gr, a);
    F0R(i, q) {
        int x, y, z; cin >> x >> y >> z;
        if (x == 1) hld.update(--y, z);
        else cout << hld.query(--y, --z) << nl;
    }
    return 0;
}
