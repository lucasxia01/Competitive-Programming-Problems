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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, h; cin >> n >> h;
    int x[n+1]; F0R(i, n) cin >> x[i+1];
    x[0] = 0;
    int p[n], f[n]; 
    FOR(i, 1, n-1) cin >> p[i] >> f[i];
    // which station, how much gas I have now, how much gas I need going back coming out this station
    int dp[n+1][h+1][h+1]; F0R(i, n+1) F0R(j, h+1) F0R(k, h+1) dp[i][j][k] = 1e9;
    dp[0][h][0] = 0;
    FOR(i, 0, n-1) {
        F0R(j, h+1) F0R(k, h+1) {
            if (dp[i][j][k] == 1e9) continue;
            int dist = x[i+1]-x[i];
            // fuel ->, fuel <-, or do nothing
            if (i) {
                int nj = min(h, j+f[i]);
                if (nj-dist >= 0 && k+dist <= h) ckmin(dp[i+1][nj-dist][k+dist], dp[i][j][k]+p[i]);
                // i need k gas going back at i, so need to have k-f[i] gas entering
                // 
                // so i need k+dist gas going back from i+1
                if (j-dist >= 0 && max(k-f[i], 0)+dist <= h) ckmin(dp[i+1][j-dist][max(k-f[i], 0)+dist], dp[i][j][k]+p[i]);
            }
            if (j-dist >= 0 && k+dist <= h) ckmin(dp[i+1][j-dist][k+dist], dp[i][j][k]);
        }
    }
    // find all states where i have enough gas to go back
    int ans = 1e9;
    F0R(j, h+1) F0R(k, h+1) {
        if (j >= k) ckmin(ans, dp[n][j][k]);
    }
    if (ans == 1e9) cout << -1 << nl;
    else cout << ans << nl;
    return 0;
}
