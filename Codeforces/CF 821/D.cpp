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
const ll INF = (1LL<<55) + 123;
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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, x, y; cin >> n >> x >> y;
        string s, t; cin >> s >> t;
        vi diffs;
        F0R(i, n) {
            if (s[i] != t[i]) diffs.pb(i);
        }
        if (sz(diffs)%2) {
            cout << -1 << nl;
            continue;
        }
        if (x >= y) {
            if (sz(diffs) == 2 && diffs[0]+1 == diffs[1]) {
                cout << min(x, 2*y) << nl;
            } else {
                cout << sz(diffs)/2 * y << nl;
            }
        } else {
            // dp 
            int N = sz(diffs);
            int dp[N+1]; F0R(i, N+1) dp[i] = INF;
            dp[0] = 0;
            F0R(i, N) {
                if (dp[i] == INF) continue;
                // jump from i to j
                int cur = 0;
                for (int j = i+1; j < N; j+=2) {
                    ckmin(dp[j+1], dp[i]+y+cur);
                    if (j+1 < N) cur += (diffs[j+1]-diffs[j])*x;
                }
                ckmin(dp[i+2], dp[i]+(diffs[i+1]-diffs[i])*x);
            }
            cout << dp[N] << nl;

        }

    }
    return 0;
}
