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

const int MX = 1e6+5;

struct FT {
	vector<ll> s;
	FT(int n) : s(n, 0) {}
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
    int t = 1; 
    cin >> t;
    while (t--) {
        int n; cin >> n;
        int a[n+1]; F0R(i, n) cin >> a[i+1];
        FT f(2*n+5);
        // find the segment
        vector<array<int, 3> > segs;
        FOR(i, 1, n) {
            // i to a[i] is the segment
            if (i > a[i]) {
                dbg("seg", i, a[i]+n);
                segs.pb({i, 0, a[i]});
                segs.pb({a[i]+n, 1, i});
            }
            else {
                dbg("seg", i, a[i]);
                dbg("seg", i+n, a[i]+n);
                segs.pb({i, 0, a[i]});
                segs.pb({a[i], 1, i});
                segs.pb({i+n, 0, a[i]});
                segs.pb({a[i]+n, 1, i+n});
            }
        }
        sort(all(segs));
        int ans[n+1];
        trav(p, segs) {
            if (p[1] == 1) {
                // its an end so we need to count 
                int len = p[0] - p[2];
                // count how many segments it contains
                // dbg(p[0], f.query(p[0]+1), p[2]-1, f.query(p[2]));
                int cnt = f.query(p[0]+1) - f.query(p[2]);
                int idx = p[0];
                if (idx > n) idx-=n;
                dbg(idx, len-cnt);
                ans[idx] = len-cnt;
                f.update(p[2], 1);
            }
        }
        FOR(i, 1, n) cout << ans[i] << " ";
        cout << nl;
    }
    return 0;
}
