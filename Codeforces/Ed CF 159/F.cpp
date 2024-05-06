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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 2e5+5;
int n;
int A[MX];

template <int NUMBITS>
struct XORBasis_ {
    vector<int> basis;
    XORBasis_() {}
    XORBasis_(int x) {
        basis.pb(x);
    }
    bool add(int x) {
        trav(y, basis) x = min(x, x^y);
        if (x) {
            basis.pb(x);
            return 1;
        }
        return 0;
    }

    void merge(const XORBasis_& b) {
        trav(x, b.basis) this->add(x);
    }
    static XORBasis_ merge(XORBasis_& a, XORBasis_& b) {
        // just throw one into the other
        if (sz(a.basis) < sz(b.basis)) {
            XORBasis_ c = b;
            trav(x, a.basis) c.add(x);
            return c;
        } else {
            XORBasis_ c = a;
            trav(x, b.basis) c.add(x);
            return c;
        }
    }
};

using XORBasis = XORBasis_<20>;

vector<vector<pair<int, XORBasis > > > treeJump(vi& P){
	int on = 1, d = 1;
	while(on < sz(P)) on *= 2, d++;
    vector<pair<int, XORBasis> > P2;
    F0R(i, sz(P)) P2.pb({P[i], XORBasis(A[i])});
	vector<vector<pair<int, XORBasis> > > jmp(d, P2);
	rep(i,1,d) rep(j,0,sz(P)) {
		jmp[i][j].f = jmp[i-1][jmp[i-1][j].f].f;
        jmp[i][j].s = XORBasis::merge(jmp[i-1][j].s, jmp[i-1][jmp[i-1][j].f].s);
    }
	return jmp;
}

pair<int, XORBasis> jmp(vector<vector<pair<int, XORBasis > > >& tbl, int nod, int steps){
    XORBasis ret;
	rep(i,0,sz(tbl))
		if(steps&(1<<i)) {
            ret.merge(tbl[i][nod].s);
            nod = tbl[i][nod].f;
        }
	return {nod, ret};
}

int jmp_no_merge(vector<vector<pair<int, XORBasis > > >& tbl, int nod, int steps){
	rep(i,0,sz(tbl))
		if(steps&(1<<i)) {
            nod = tbl[i][nod].f;
        }
	return nod;
}

XORBasis lca(vector<vector<pair<int, XORBasis > > >& tbl, vi& depth, pair<int, XORBasis> a, pair<int, XORBasis> b) {
	if (depth[a.f] < depth[b.f]) swap(a, b);
    int new_a = jmp_no_merge(tbl, a.f, depth[a.f] - depth[b.f]);
    int new_b = b.f;
	// a = jmp(tbl, a.f, depth[a.f] - depth[b.f]);
	if (new_a == b.f) {
        // actually do the jump
        a = jmp(tbl, a.f, depth[a.f] - depth[b.f]);
        a.s.add(A[a.f]);
        return a.s;
    }
	for (int i = sz(tbl); i--;) {
		auto c = tbl[i][new_a].f, d = tbl[i][new_b].f;
		if (c != d) {
            new_a = c;
            new_b = d;
        }
	}
    int lca_node = tbl[0][new_a].f;
    // now jump to the LCA
    a = jmp(tbl, a.f, depth[a.f] - depth[lca_node]);
    b = jmp(tbl, b.f, depth[b.f] - depth[lca_node]);
    a.s.merge(b.s);
    a.s.add(A[lca_node]);
	return a.s;
}

vi gr[MX];
vi P(MX), depth(MX);

void dfs(int v, int p, int d) {
    dbg(v, p, d);
    P[v] = p;
    depth[v] = d;
    trav(u, gr[v]) {
        if (u == p) continue;
        dfs(u, v, d+1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    F0R(i, n) cin >> A[i+1];
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        gr[u].pb(v);
        gr[v].pb(u);
    }
    dfs(1, 0, 0);
    auto tbl = treeJump(P);
    int q; cin >> q;
    while (q--) {
        int x, y, k; cin >> x >> y >> k;
        auto basis = lca(tbl, depth, {x, XORBasis()}, {y, XORBasis()});
        // check if k is in the basis
        // trav(b, basis.basis) {
        //     cerr << b << " ";
        // }
        // cerr << nl;
        if (!basis.add(k)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
