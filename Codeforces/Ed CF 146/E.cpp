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

const int MX = 2e5+5;

int n, SQRTN, chunks;
int a[MX];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    n--;
    F0R(i, n) cin >> a[i];

    SQRTN = sqrt(n);

    chunks = (n+SQRTN-1)/SQRTN;
    int DP[chunks][2][2];
    F0R(i, chunks) {
        int l = i*SQRTN, r = min((i+1)*SQRTN-1, n-1);
        int dp[r-l+1][2][2];
        F0R(ii, r-l+1) F0R(j, 2) F0R(k, 2) dp[ii][j][k] = INF;
        dp[0][0][0] = 0;
        dp[0][1][1] = a[l];
        FOR(j, 1, r-l) {
            ckmin(dp[j][0][0], dp[j-1][0][1]);
            ckmin(dp[j][0][1], min(dp[j-1][0][0], dp[j-1][0][1]) + a[l+j]);
            ckmin(dp[j][1][0], dp[j-1][1][1]);
            ckmin(dp[j][1][1], min(dp[j-1][1][0], dp[j-1][1][1]) + a[l+j]);
        }
        F0R(j, 2) F0R(k, 2) 
            DP[i][j][k] = dp[r-l][j][k];
    }
    int q; cin >> q;
    while (q--) {
        int k, x; cin >> k >> x;
        k--;
        a[k] = x;
        // recompute chunk k/SQRTN
        int idx = k/SQRTN;
        int l = idx*SQRTN, r = min((idx+1)*SQRTN-1, n-1);
        dbg(k, l, r);
        int dp[r-l+1][2][2];
        F0R(ii, r-l+1) F0R(j, 2) F0R(k, 2) dp[ii][j][k] = INF;
        dp[0][0][0] = 0;
        dp[0][1][1] = a[l];
        FOR(j, 1, r-l) {
            ckmin(dp[j][0][0], dp[j-1][0][1]);
            ckmin(dp[j][0][1], min(dp[j-1][0][0], dp[j-1][0][1]) + a[l+j]);
            ckmin(dp[j][1][0], dp[j-1][1][1]);
            ckmin(dp[j][1][1], min(dp[j-1][1][0], dp[j-1][1][1]) + a[l+j]);
        }
        F0R(j, 2) F0R(k, 2) {
            DP[idx][j][k] = dp[r-l][j][k];
            dbg(idx, j, k, DP[idx][j][k]);
        }
        
        // now compute the answer
        int dp2[chunks][2];
        F0R(i, chunks) F0R(j, 2) dp2[i][j] = INF;
        dp2[0][1] = DP[0][1][1];
        dp2[0][0] = DP[0][1][0];
        FOR(i, 1, chunks-1) {
            dp2[i][0] = min(dp2[i-1][1] + min(DP[i][1][0], DP[i][0][0]), dp2[i-1][0] + DP[i][1][0]);
            dp2[i][1] = min(dp2[i-1][1] + min(DP[i][0][1], DP[i][1][1]), dp2[i-1][0] + DP[i][1][1]);
            dbg(i, dp2[i][0], dp2[i][1]);
        }
        cout << dp2[chunks-1][1]*2 << nl;
    }
    return 0;
}
