#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cassert>
#include <climits>

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
const ll INF = (1LL<<50) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 2e5+5;

struct Tree {
	typedef ll T;
	static constexpr T unit = INF;
	T f(T a, T b) { return min(a, b); } // (any associative fn)
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

ll f(ll a, ll b) {
    return (a+b+min(a, b));
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    F0R(tt, t) {
        int n, m; cin >> n >> m;
        ll a[n]; F0R(i, n) cin >> a[i];
        sort(a, a+n);
        vpl b[n+1];
        vpl c[n+1];
        F0R(i, m) {
            int l, r;
            cin >> l >> r;
            int idx = lower_bound(a, a+n, l)-a;
            int idx2 = lower_bound(a, a+n, r+1)-a;
            dbg(l, r, idx, idx2);
            if (idx != idx2) continue;
            b[idx].pb({l, r});
            c[idx].pb({r, l});
        }
        F0R(i, n+1) {
            sort(all(b[i]));
            sort(all(c[i]));
        }

        vpl o[n+1];
        FOR(i, 1, n-1) {
            // construct all the options u have
            int N = sz(b[i]);
            if (N == 0) {
                o[i].pb({0, 0});
                continue;
            }
            Tree st(N, a[i]);
            F0R(j, N) st.update(j, b[i][j].s);
            o[i].pb({0, a[i]-st.query(0, N)});
            F0R(j, N) {
                st.update(j, a[i]);
                o[i].pb({b[i][j].f-a[i-1], a[i]-st.query(0, N)});
            }
            trav(oo, o[i]) {
                dbg(i, oo.f, oo.s);
            }
        }
        // c[n].back().f-a[n-1]);
        ll x = 0;
        if (sz(c[0])) x = a[0]-c[0][0].f;
        dbg(x);
        vpl dp[n+1];
        ll y = 0;
        if (sz(b[n])) y = b[n].back().f - a[n-1];
        o[n].pb({y, 0});
        trav(oo, o[1]) {
            dp[1].pb({oo.s, f(x, oo.f)});
            dbg(0, oo.s, f(x, oo.f));
        }
        
        // now dp time
        FOR(i, 1, n-1) {
            int N = sz(dp[i]);
            Tree st(N);
            F0R(j, N) st.update(j, dp[i][j].f+dp[i][j].s);
            int idx = N-1;
            trav(oo, o[i+1]) {
                while (idx >= 0 && dp[i][idx].f <= oo.f) {
                    st.update(idx, dp[i][idx].f*2+dp[i][idx].s);
                    idx--;
                }
                ll best = INF;
                ckmin(best, st.query(0, idx+1)+2*oo.f);
                ckmin(best, st.query(idx+1, N)+oo.f);
                dp[i+1].pb({oo.s, best});
                dbg(i, oo.s, best);
            }
        }
        cout << dp[n][0].s << nl;
    }
    return 0;
}
