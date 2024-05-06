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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a+b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, q; cin >> n >> m >> q;
    set<pi> harbors;
    pi a[m]; 
    F0R(i, m) cin >> a[i].f;
    F0R(i, m) cin >> a[i].s;
    F0R(i, m) harbors.insert(a[i]);
    int prev = 1, prevmul = 1;
    Tree st(n+1);
    trav(p, harbors) {
        // update p.f with  with the appropriate sum of dist * prevmul
        st.update(p.f, (p.f-prev)*(p.f-prev-1)/2 * prevmul);
        dbg(p.f, prevmul);
        prev = p.f;
        prevmul = p.s;
    }
    while (q--) {
        dbg("now queries", q);
        int t; cin >> t;
        if (t == 1) { // add harbor and do updates to the corresponding ranges
            int x, v; cin >> x >> v;
            auto it = harbors.lower_bound({x, v});
            int x1 = it->f;
            --it;
            int x0 = it->f;
            // update this x1
            st.update(x1, (x1-x)*(x1-x-1)/2 * v);
            // update x with new val
            st.update(x, (x-x0)*(x-x0-1)/2 * it->s);
            harbors.insert({x, v});
        } else {
            // to query, we need a range sum over the full segments and the endpoints
            int l, r; cin >> l >> r;
            // find the first thing to the right
            auto itL = harbors.lower_bound({l, -1});
            auto itR = harbors.lower_bound({r+1, -1});
            itR--;
            // edge case if there's no harbor in between
            if (itL->f > itR->f) {
                // itL->f-r to itL->f-l
                dbg(itL->f, r, l);
                int ans = (itL->f-r+itL->f-l)*(r-l+1)/2 * itR->s;
                itR++;
                assert(itR==itL);
                cout << ans << nl;
                continue;
            }
            ll ans = st.query(itL->f+1, itR->f+1); // don't include itL->f, but include itR->f
            // range is [itL->f+1, itR->f]
            int cutA = itL->f;
            int cutB = itR->f+1;
            // now the left endpoint
            ll left = 0;
            if (itL != harbors.begin()) {
                int pos = itL->f;
                itL--;
                left = (pos-l+1)*(pos-l)/2 * itL->s;
                // range is [l, itL->f]
                // if l is a harbor, then it->f == l
            }
            int pos = itR->f;
            int val = itR->s;
            itR++;
            ll right = 0;
            if (itR != harbors.end()) {
                // itR->f-r to itR->f-pos-1
                dbg(itR->f, r, pos);
                right = (itR->f-pos-1 + itR->f-r) * (itR->f-pos - (itR->f-r)) / 2 * val;
                // range is [pos+1, r)
            }
            cout << ans+left+right << nl;
        }
    }

    return 0;
}
