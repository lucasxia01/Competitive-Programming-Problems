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

const int MX = 3e5+5;

int inf = 1e9;
struct Node { // we want range additions, range max and second max queries
	Node *l = 0, *r = 0;
	int lo, hi, madd = 0, val = 1;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of 1
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo]; 
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf; // or 1??
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int n;
vi gr[MX];
int l = 0;
pi range[MX];
int prevIdx[MX];
int a[MX];
vi colorCh[MX];
vi start;

void dfs(int v, int ans = 0) {
    int prev = prevIdx[a[v]];
    int ans2 = ans + (prev==-1);
    if (prev != -1) colorCh[prev].pb(v);
    prevIdx[a[v]] = v;
    int in = l;
    trav(u, gr[v]) {
        dfs(u, ans2);
    }
    if (gr[v].empty()) {
        start.pb(ans2);
        l++;
    }
    int out = l;
    range[v] = {in, out};
    prevIdx[a[v]] = prev;
}
ll ans = 1;

void dfs2(Node& st, int v) {
    trav(u, gr[v]) {
        // calc ans for every child with the other children
        int res = st.query(range[u].f, range[u].s);
        int res2 = max(st.query(range[v].f, range[u].f), st.query(range[u].s, range[v].s));
        ckmax(res, 1);
        ckmax(res2, 1);
        ckmax(ans, 1LL * res * res2);
        dbg(v, u, res, res2, ans);
    }

    // now remove this node and recursve
    // find all color children and add 1 to them
    trav(u, colorCh[v]) {
        st.add(range[u].f, range[u].s, 1);
    }
    st.add(range[v].f, range[v].s, -1); // remove 1 from everything now
    trav(u, gr[v]) {
        dfs2(st, u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        // 1 index
        cin >> n;
        F0R(i, n+1) {
            gr[i].clear();
            range[i] = {-1, -1};
            prevIdx[i] = -1;
            a[i] = -1;
            colorCh[i].clear();
        }
        l = 0;
        ans = 1;
        start.clear();
        int p[n+1]; FOR(i, 2, n) {
            cin >> p[i];
            gr[p[i]].pb(i);
        }
        FOR(i, 1, n) cin >> a[i];
        // label the leaves from 0 to l-1, where l is the number of leaves
        // calculate the range of every node on the leaves
        // calcualte all the color parents if any
        dfs(1);
        Node st(start, 0, l);
        dbg(l);
        FOR(i, 1, n) {
            // i want the vals of everything
            dbg("node", i, "with range", range[i].f, range[i].s);
        }
        F0R(i, l) {
            dbg("leaf", start[i]);
        }
        // ok lets ROLL
        // dfs the tree again but this time, we need to update the segtree
        dfs2(st, 1);
        cout << ans << nl;
    }
    return 0;
}
