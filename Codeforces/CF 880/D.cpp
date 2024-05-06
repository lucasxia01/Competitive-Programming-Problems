#include <bits/stdc++.h>

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

const int MX = 3e5+5;

vi val, comp, z, cont;
vector<vi> comps;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
            comps[ncomps].push_back(x);
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
        comps.pb(vi());
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
    comps.pb(vi());
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}
vector<vi> gr;
vector<bool> vis;
vi col;
int find_cycle(int v, int s, int dist) {
    if (v == s && dist) return dist;
    if (vis[v]) return 0;
    vis[v] = 1;
    trav(u, gr[v]) {
        if (comp[u] != comp[s]) continue;
        int ret = find_cycle(u, s, dist+1);
        if (ret) return ret;
    }
    return 0;
}
bool color(int v, int c, int K) {
    if (col[v] != -1 && col[v] != c) return 0;
    else if (col[v] != -1) return 1;
    col[v] = c;
    trav(u, gr[v]) {
        if (comp[u] != comp[v]) continue;
        if (!color(u, (c+1)%K, K)) return 0;
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n, m, k; cin >> n >> m >> k;
    gr.resize(n);
    vis.resize(n, 0);
    col.resize(n, -1);
    rep(i, 0, m) {
        int u, v; cin >> u >> v; u--; v--;
        gr[u].pb(v);
    }
    scc(gr, [&] (vi& v) {});
    vector<bool> done(ncomps, 0);
    ll ans = 0;
    rep(i, 0, n) {
        if (done[comp[i]]) continue;
        done[comp[i]] = 1;
        if (sz(comps[comp[i]]) == 1) continue;
        // dfs from i and then test factors
        int d = find_cycle(i, i, 0);
        // find max j that works
        int best = -1;
        for (int j = 1; j*j <= d; j++) {
            // try to j-color the scc
            if (j > best) {
                trav(v, comps[comp[i]]) col[v] = -1;
                if (color(i, 0, j)) {
                    ckmax(best, j);
                }
            }
            if (d/j > best) {
                trav(v, comps[comp[i]]) col[v] = -1;
                if (color(i, 0, d/j)) {
                    ckmax(best, d/j);
                }
            }
        }
        assert(best != -1);
        dbg(i, d, best);
        // can only visit things that are k%best away from u
        trav(v, comps[comp[i]]) col[v] = -1;
        assert(color(i, 0, best));
        vl cnt(best, 0);
        trav(v, comps[comp[i]]) {
            dbg(v, col[v]);
            cnt[col[v]]++;
        }
        if (k%best == 0) {
            rep(j, 0, best) {
                ans += cnt[j] * (cnt[j]-1) / 2;
                ans += cnt[j];
            }
        } else if (best%2 == 0 && k%best == best/2) {
            rep(j, 0, best/2) {
                ans += cnt[j] * cnt[j+best/2];
            }
        }
    }
    cout << ans << nl;
    return 0;
}
