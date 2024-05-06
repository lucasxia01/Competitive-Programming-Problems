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
const ll INF = (1LL<<60) + 123;
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
        int n, k; cin >> n >> k;
        int a[n+1]; F0R(i, n) {
            cin >> a[i+1];
        }
        a[0] = 0;
        int h[k+1], c[k+1];
        F0R(i, k) cin >> c[i+1];
        F0R(i, k) cin >> h[i+1];

        int dp[n+1][k+1]; // pos i, other cpu program j, 0 is unused
        F0R(i, n+1) {
            F0R(j, k+1) {
                dp[i][j] = INF;
            }
        }
        dp[0][0] = 0;
        FOR(i, 1, n) {
            F0R(j, k+1) {
                if (dp[i-1][j] == INF) continue;
                dbg(i-1, j, dp[i-1][j]);
                int val = c[a[i]];
                if (a[i] == a[i-1]) val = h[a[i]];
                ckmin(dp[i][j], dp[i-1][j]+val);

                if (a[i] == j) 
                    ckmin(dp[i][a[i-1]], dp[i-1][j]+h[a[i]]);
                else
                    ckmin(dp[i][a[i-1]], dp[i-1][j]+c[a[i]]);
            }
        }
        int ans = INF;
        F0R(j, k+1) {
            dbg(n, j, dp[n][j]);
            ckmin(ans, dp[n][j]);
        }
        cout << ans << nl;
    }
    return 0;
}
