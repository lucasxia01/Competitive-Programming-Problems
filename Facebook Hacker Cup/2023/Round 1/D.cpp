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
	int lo, hi, mset = inf, madd = 0, hi_val = inf, hi_idx = -1, lo_val = inf, lo_idx = -1;
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
            if (l->lo_val <= r->lo_val) lo_idx = l->lo_idx;
            else lo_idx = r->lo_idx;
			if (l->hi_val >= r->hi_val) {
                hi_val = l->hi_val;
                hi_idx = l->hi_idx;
            } else {
                hi_val = r->hi_val;
                hi_idx = r->hi_idx;
            }
            if (l->lo_val <= r->lo_val) {
                lo_val = l->lo_val;
                lo_idx = l->lo_idx;
            } else {
                lo_val = r->lo_val;
                lo_idx = r->lo_idx;
            }
		}
		else {
            hi_val = v[lo];
            hi_idx = lo;
            lo_val = v[lo];
            lo_idx = lo;
        }
	}
	pi queryMax(int L, int R) {
		if (R <= lo || hi <= L) return {-inf, -1};
		if (L <= lo && hi <= R) return {hi_val, hi_idx};
		push();
		pi retL = l->queryMax(L, R);
        pi retR = r->queryMax(L, R);
        if (retL.f >= retR.f) return retL;
        else return retR;
	}

    pi queryMin(int L, int R) {
		if (R <= lo || hi <= L) return {inf, -1};
		if (L <= lo && hi <= R) return {lo_val, lo_idx};
		push();
		pi retL = l->queryMin(L, R);
        pi retR = r->queryMin(L, R);
        if (retL.f <= retR.f) return retL;
        else return retR;
	}
	void add(int L, int R) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd = !madd;
            swap(hi_val, lo_val);
            swap(lo_idx, hi_idx);
			hi_val = MOD-hi_val;
            lo_val = MOD-lo_val;
		}
		else {
			push(), l->add(L, R), r->add(L, R);
            if (l->hi_val >= r->hi_val) {
                hi_val = l->hi_val;
                hi_idx = l->hi_idx;
            } else {
                hi_val = r->hi_val;
                hi_idx = r->hi_idx;
            }
            if (l->lo_val <= r->lo_val) {
                lo_val = l->lo_val;
                lo_idx = l->lo_idx;
            } else {
                lo_val = r->lo_val;
                lo_idx = r->lo_idx;
            }

		}
	}
	void push() {
		if (!l) {
            assert(0);
			// int mid = lo + (hi - lo)/2;
			// l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (madd)
			l->add(lo,hi), r->add(lo,hi), madd = 0;
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    FOR(tt, 1, t) {
        cout << "Case #" << tt << ": ";
        int n; cin >> n;
        vi a(n); F0R(i, n) cin >> a[i];
        Node st(a, 0, n);
        int q; cin >> q;
        ll ans = 0;
        while (q--) {
            int l, r; cin >> l >> r; l--;
            st.add(l, r);
            pi ret = st.queryMax(0, n);
            // dbg(ret.f, ret.s);
            ans += (ret.s+1);
        }
        cout << ans << nl;
    }
    return 0;
}
