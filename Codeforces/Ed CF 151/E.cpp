#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;
const int SQRTK = 42;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, K; cin >> n >> K;
    int a[n]; vi x, y;
    F0R(i, n) {
        cin >> a[i];
        if (a[i]) x.pb(i+1);
        else y.pb(i+1);
    }
    if (sz(x) > sz(y)) swap(x, y); // choose smaller set
    int m = sz(x);
    int dp[2][K+1][n+1]; // # of ways for <=i balls, exactly k cost, <=j bins
    pi range[m+1][K+1]; // active range for ball i given at most cost k
    F0R(i, m+1) F0R(k, K+1) {
        range[i][k] = {n+1, n}; // no range
    }
    F0R(i, 2) F0R(k, K+1) F0R(j, n+1) {
        dp[i][k][j] = 0;
    }
    range[0][0] = {0, 0}; // init range
    dp[0][0][0] = 1;
    FOR(i, 1, m) {
        int i0 = i%2;
        int i1 = (i-1)%2;
        F0R(k, K+1) {
            int l = max(i, x[i-1]-k), r = min(n-(m-i), x[i-1]+k);
            if (i-1-SQRTK >= 0) ckmax(l, x[i-1-SQRTK]);
            if (i-1+SQRTK < m) ckmin(r, x[i-1+SQRTK]);
            range[i][k] = {l, r}; // calcing active range
            dp[i0][k][l-1] = 0;
            FOR(j, l, r) {
                int diff = abs(x[i-1]-j);
                dp[i0][k][j] = dp[i0][k][j-1];
                // casework over where j-1 falls into the range of dp[i1][k-diff]
                if (j-1 < range[i-1][k-diff].f) dp[i0][k][j] += 0;
                else if (j-1 > range[i-1][k-diff].s) dp[i0][k][j] += dp[i1][k-diff][range[i-1][k-diff].s];
                else dp[i0][k][j] += dp[i1][k-diff][j-1];
                dp[i0][k][j] %= MOD;
                dbg(i, k, j, range[i-1][k-diff].f, range[i-1][k-diff].s, dp[i0][k][j]);
            }
        }
    }
    ll ans = 0;
    F0R(j, K+1) { // sum over all k with same parity as K
        if ((K-j)%2) continue;
        dbg(j, dp[m%2][j][range[m][j].s]);
        ans = (ans + dp[m%2][j][range[m][j].s])%MOD;
    }
    cout << ans << nl;
    return 0;
}
