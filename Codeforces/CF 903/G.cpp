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

const int MX = 2e5+5;

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
    void reset(int n) {
        for (int i = 0; i < n; i++) s[i] = 0;
    }
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

FT f(MX); // for true values of characters
FT f2(2*MX); // fenwick tree for palindromes
int isPal[2*MX];

bool check(const vi& v, int n, int i) {
    if (i%2) { // check even palindrome
        i/=2;
        assert(i < n-1);
        int val1 = (v[i]+f.query(i+1))%26;
        int val2 = (v[i+1]+f.query(i+2))%26;
        return (val1==val2);
    } else {
        i/=2;
        assert(i > 0 && i < n-1);
        int val1 = (v[i-1]+f.query(i))%26;
        int val2 = (v[i+1]+f.query(i+2))%26;
        return (val1==val2);
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        f.reset(n);
        f2.reset(2*n);
        memset(isPal, 0, sizeof(int) * (2*n));
        string s; cin >> s;
        vi v(n); F0R(i, n) v[i] = s[i]-'a';
        FOR(i, 1, 2*n-3) {
            int prev = isPal[i];
            isPal[i] = check(v, n, i);
            f2.update(i, isPal[i]-prev);
        }
        // first find all the palindromes
        while (m--) {
            int t; cin >> t;
            if (t == 1) {
                int l, r, x; cin >> l >> r >> x; l--;
                f.update(l, x);
                f.update(r, -x);
                
                // update the edges of the range
                FOR(i, max(1LL, 2*l-2), min(2*n-3, 2*l+2)) {
                    int prev = isPal[i];
                    isPal[i] = check(v, n, i);
                    f2.update(i, isPal[i]-prev);
                }
                FOR(i, max(1LL, 2*r-2), min(2*n-3, 2*r+2)) {
                    int prev = isPal[i];
                    isPal[i] = check(v, n, i);
                    f2.update(i, isPal[i]-prev);
                }
            } else {
                int l, r; cin >> l >> r; l--;
                if (r-l==1) {
                    cout << "YES" << nl;
                    continue;
                }
                // query for the range [2*l+1, 2*r-3]
                cout << (f2.query(2*r-2) - f2.query(2*l+1)?"NO":"YES") << nl;
            }
        }
    }
    return 0;
}
