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

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n]; F0R(i, n) cin >> a[i];
    vpi v; F0R(i, n) v.pb({a[i], i});
    sort(all(v)); reverse(all(v));
    set<int> s1, s2; // s1 is full, s2 is empty
    FOR(i, 0, n-1) s1.insert(i);
    s1.insert(n);
    s2.insert(n);
    s2.insert(-1);
    vector<array<int, 3> > ops[n+1];
    trav(u, v) {
        // find left endpoint and right endpoint
        auto it = s2.lower_bound(u.s);
        int r = *it;
        --it;
        int l = *it;
        it = s1.lower_bound(r);
        int r2 = *it;
        dbg(u.f, u.s, l+1, r, r2);
        ops[l+1].pb({1, r, r2});
        ops[r].pb({-1, r, r2});
        s1.erase(u.s);
        s2.insert(u.s);
    }
    // process the dudes and find their ranges
    FT ft(n+1);
    int q; cin >> q;
    vector<array<int, 3> > qs(q);
    F0R(i, q) {
        cin >> qs[i][0] >> qs[i][1];
        qs[i][0]--; qs[i][1]--;
        qs[i][2] = i;
    }
    sort(all(qs));
    bool ans[q];
    int ptr = 0;
    F0R(i, n) {
        // process ops first
        trav(u, ops[i]) {
            dbg(u[0], u[1], u[2]);
            if (u[0] == 1) {
                ft.update(u[1], 1);
                ft.update(u[2], -1);
            } else {
                ft.update(u[1], -1);
                ft.update(u[2], 1);
            }
        }
        // F0R(j, n+1) {
        //     cerr << ft.query(j+1) << " ";
        // } cerr << nl;
        while (ptr < q && qs[ptr][0] == i) {
            ans[qs[ptr][2]] = ft.query(qs[ptr][1]+1);
            ptr++;
        }
    }
    F0R(i, q) cout << (ans[i]?"YES":"NO") << nl;
    return 0;
}
