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

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
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
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

struct SumNode {
	SumNode *l = 0, *r = 0;
	int lo, hi, madd = 0, val = 0;
	SumNode(int lo,int hi):lo(lo),hi(hi){} // Large interval of 0
	SumNode(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new SumNode(v, lo, mid); r = new SumNode(v, mid, hi);
			val = l->val+r->val;
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		push();
		return l->query(L, R)+r->query(L, R);
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = l->val+r->val;
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new SumNode(lo, mid); r = new SumNode(mid, hi);
		}
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    vi a(n); F0R(i, n) cin >> a[i];
    int cnt[n+1]; F0R(i, n+1) cnt[i] = 0;
    F0R(i, n) cnt[a[i]]++;
    int pref[n+1]; pref[0] = 0;
    F0R(i, n) pref[i+1] = pref[i] + cnt[i+1];
    
    vpi v; F0R(i, n) v.pb({a[i], i});
    sort(all(v));
    int last[n+1]; FOR(i, 1, n) last[i] = -1;
    int prev[n];
    vi upds[n+1];
    F0R(i, n) {
        prev[i] = last[a[i]];
        dbg(i, prev[i]);
        last[a[i]] = i;
    }
    Node st(0, n);
    trav(p, v) {
        int x = st.query(prev[p.s]+1, p.s);
        st.set(p.s, p.s+1, p.f);
        dbg(p.s, p.f, prev[p.s]);
        if (prev[p.s] == -1) x = p.f;
        if (x == -inf) continue;
        upds[p.f].pb(x);
        dbg(p.f, x);
    }

    vector<array<int, 3> > qs;
    F0R(i, q) {
        int l, r; cin >> l >> r;
        qs.pb({r, l, i});
    }
    sort(all(qs));
    int ptr = 0;
    int ans[q];
    SumNode sumST(1, n+1);
    FOR(i, 1, n) {
        // perform the updates
        dbg("i", i);
        trav(u, upds[i]) {
            dbg(u);
            sumST.add(u, u+1, 1);
        }
        // now answer queries
        while (ptr < q && qs[ptr][0] == i) {
            int l = qs[ptr][1];
            int r = qs[ptr][0];
            int idx = qs[ptr][2];
            ans[idx] = sumST.query(l, n+1);
            dbg(l, r, idx, ans[idx]);
            ptr++;
        }
    }
    F0R(i, q) {
        cout << ans[i] << nl;
    }
    return 0;
}
