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

const int MAXN = 1e6 + 5;  // 1-based

int N;
ll A[MAXN];
struct Node {
	ll sum;   // Sum tag
	ll max1;  // Max value
	ll max2;  // Second Max value
	ll maxc;  // Max value count
	ll min1;  // Min value
	ll min2;  // Second Min value
	ll minc;  // Min value count
	ll lazy;  // Lazy tag
} T[MAXN * 4];

const ll llINF = 1e18;
void merge(int t) {
	// sum
	T[t].sum = T[t << 1].sum + T[t << 1 | 1].sum;

	// max
	if (T[t << 1].max1 == T[t << 1 | 1].max1) {
		T[t].max1 = T[t << 1].max1;
		T[t].max2 = max(T[t << 1].max2, T[t << 1 | 1].max2);
		T[t].maxc = T[t << 1].maxc + T[t << 1 | 1].maxc;
	} else {
		if (T[t << 1].max1 > T[t << 1 | 1].max1) {
			T[t].max1 = T[t << 1].max1;
			T[t].max2 = max(T[t << 1].max2, T[t << 1 | 1].max1);
			T[t].maxc = T[t << 1].maxc;
		} else {
			T[t].max1 = T[t << 1 | 1].max1;
			T[t].max2 = max(T[t << 1].max1, T[t << 1 | 1].max2);
			T[t].maxc = T[t << 1 | 1].maxc;
		}
	}

	// min
	if (T[t << 1].min1 == T[t << 1 | 1].min1) {
		T[t].min1 = T[t << 1].min1;
		T[t].min2 = min(T[t << 1].min2, T[t << 1 | 1].min2);
		T[t].minc = T[t << 1].minc + T[t << 1 | 1].minc;
	} else {
		if (T[t << 1].min1 < T[t << 1 | 1].min1) {
			T[t].min1 = T[t << 1].min1;
			T[t].min2 = min(T[t << 1].min2, T[t << 1 | 1].min1);
			T[t].minc = T[t << 1].minc;
		} else {
			T[t].min1 = T[t << 1 | 1].min1;
			T[t].min2 = min(T[t << 1].min1, T[t << 1 | 1].min2);
			T[t].minc = T[t << 1 | 1].minc;
		}
	}
}

void push_add(int t, int tl, int tr, ll v) {
	if (v == 0) { return; }
	T[t].sum += (tr - tl + 1) * v;
	T[t].max1 += v;
	if (T[t].max2 != -llINF) { T[t].max2 += v; }
	T[t].min1 += v;
	if (T[t].min2 != llINF) { T[t].min2 += v; }
	T[t].lazy += v;
}

// corresponds to a chmin update
void push_max(int t, ll v, bool l) {
	if (v >= T[t].max1) { return; }
	T[t].sum -= T[t].max1 * T[t].maxc;
	T[t].max1 = v;
	T[t].sum += T[t].max1 * T[t].maxc;
	if (l) {
		T[t].min1 = T[t].max1;
	} else {
		if (v <= T[t].min1) {
			T[t].min1 = v;
		} else if (v < T[t].min2) {
			T[t].min2 = v;
		}
	}
}

// corresponds to a chmax update
void push_min(int t, ll v, bool l) {
	if (v <= T[t].min1) { return; }
	T[t].sum -= T[t].min1 * T[t].minc;
	T[t].min1 = v;
	T[t].sum += T[t].min1 * T[t].minc;
	if (l) {
		T[t].max1 = T[t].min1;
	} else {
		if (v >= T[t].max1) {
			T[t].max1 = v;
		} else if (v > T[t].max2) {
			T[t].max2 = v;
		}
	}
}

void pushdown(int t, int tl, int tr) {
	if (tl == tr) return;
	// sum
	int tm = (tl + tr) >> 1;
	push_add(t << 1, tl, tm, T[t].lazy);
	push_add(t << 1 | 1, tm + 1, tr, T[t].lazy);
	T[t].lazy = 0;

	// max
	push_max(t << 1, T[t].max1, tl == tm);
	push_max(t << 1 | 1, T[t].max1, tm + 1 == tr);

	// min
	push_min(t << 1, T[t].min1, tl == tm);
	push_min(t << 1 | 1, T[t].min1, tm + 1 == tr);
}

void build(int t = 1, int tl = 0, int tr = N - 1) {
	T[t].lazy = 0;
	if (tl == tr) {
		T[t].sum = T[t].max1 = T[t].min1 = A[tl];
		T[t].maxc = T[t].minc = 1;
		T[t].max2 = -llINF;
		T[t].min2 = llINF;
		return;
	}

	int tm = (tl + tr) >> 1;
	build(t << 1, tl, tm);
	build(t << 1 | 1, tm + 1, tr);
	merge(t);
}

void update_add(int l, int r, ll v, int t = 1, int tl = 0, int tr = N - 1) {
	if (r < tl || tr < l) { return; }
	if (l <= tl && tr <= r) {
		push_add(t, tl, tr, v);
		return;
	}
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	update_add(l, r, v, t << 1, tl, tm);
	update_add(l, r, v, t << 1 | 1, tm + 1, tr);
	merge(t);
}

void update_chmin(int l, int r, ll v, int t = 1, int tl = 0, int tr = N - 1) {
	if (r < tl || tr < l || v >= T[t].max1) { return; }
	if (l <= tl && tr <= r && v > T[t].max2) {
		push_max(t, v, tl == tr);
		return;
	}
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	update_chmin(l, r, v, t << 1, tl, tm);
	update_chmin(l, r, v, t << 1 | 1, tm + 1, tr);
	merge(t);
}

void update_chmax(int l, int r, ll v, int t = 1, int tl = 0, int tr = N - 1) {
	if (r < tl || tr < l || v <= T[t].min1) { return; }
	if (l <= tl && tr <= r && v < T[t].min2) {
		push_min(t, v, tl == tr);
		return;
	}
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	update_chmax(l, r, v, t << 1, tl, tm);
	update_chmax(l, r, v, t << 1 | 1, tm + 1, tr);
	merge(t);
}

ll query_sum(int l, int r, int t = 1, int tl = 0, int tr = N - 1) {
	if (r < tl || tr < l) { return 0; }
	if (l <= tl && tr <= r) { return T[t].sum; }
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	return query_sum(l, r, t << 1, tl, tm) +
	       query_sum(l, r, t << 1 | 1, tm + 1, tr);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    N = n;
    vpi a(n); F0R(i, n) { cin >> a[i].f; a[i].s = i; }
    sort(all(a));
    // coordinate compress
    int m[n]; F0R(i, n) m[a[i].s] = i; // mapping from index to coord compressed val
    int b[n]; F0R(i, n) b[i] = a[i].f;
    build(); // all zeros
    int q; cin >> q;
    vpi v;
    while (q--) {
        int l, r; cin >> l >> r;
        l--; r--;
        v.pb({l, -r});
    }
    sort(all(v));
    int l = 0, r = -1;
    ll pref[n+1]; F0R(i, n) pref[i] = 0;
    trav(u, v) {
        if (-u.s <= r) continue;
        // move l to the right
        dbg(u.f, -u.s);
        while (l < u.f) {
            update_add(0, m[l], -1); // remove l
            // update_chmin(0, n-1, 0);
            pref[0]--;
            pref[m[l]+1]++;
            l++;
        }
        // move r to the right
        while (r < -u.s) {
            r++;
            update_add(0, m[r], 1);
            update_chmin(0, n-1, 0);
            pref[0]++;
            pref[m[r]+1]--;
        }
    }
    // now figure out the best we can do
    int cur = 0;
    ll ans = 0;
    F0R(i, n) {
        cur += pref[i];
        int val = query_sum(i, i);
        int histmax = cur - val;
        dbg(i, cur, val, histmax, b[i]);
        ckmax(ans, 1LL*(histmax-1)*(b[i]));
    }
    cout << ans << nl;
    return 0;
}
