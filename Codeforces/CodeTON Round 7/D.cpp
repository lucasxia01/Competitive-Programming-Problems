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

const int MX = 1e5+5;

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
        int n, q; cin >> n >> q;
        int a[n]; F0R(i, n) cin >> a[i];
        FT f(n+5);
        F0R(i, n) f.update(i, a[i]);
        // need to keep track of first 1 and last 1
        set<int> ones;
        F0R(i, n) if (a[i] == 1) ones.insert(i);
        while (q--) {
            int op; cin >> op;
            if (op == 1) {
                int s; cin >> s; // desired sum
                auto it = ones.begin();
                if (it == ones.end()) { // no ones and only 2s
                    cout <<  ((s%2 == 0)?"YES":"NO") << nl;
                } else {
                    int l = *it;
                    auto it2 = ones.rbegin();
                    int r = *it2;
                    int hi = max(f.query(r+1), f.query(n)-f.query(l));
                    int mid = f.query(r+1)-f.query(l);
                    int num2s = n-(r-l+1);
                    bool ok = 0;
                    dbg(l, r, hi, mid, num2s);
                    assert(hi == mid+max(l, n-1-r)*2);
                    if (s <= hi) ok = 1;
                    if (s >= mid && (s-mid)%2 == 0 && (s-mid)/2 <= num2s) ok = 1;
                    cout << (ok?"YES":"NO") << nl;
                }
            } else {
                int i, v; cin >> i >> v; i--;
                if (a[i] == 1 && v == 2) {
                    ones.erase(ones.find(i));
                    f.update(i, 1);
                    a[i] = v;
                } else if (a[i] == 2 && v == 1) {
                    ones.insert(i);
                    f.update(i, -1);
                    a[i] = v;
                }

            }
        }
    }
    return 0;
}
