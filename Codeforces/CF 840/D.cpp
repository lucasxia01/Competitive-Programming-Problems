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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 100+5;


template<int sz> struct Combo {
    ll fac[sz+1], ifac[sz+1];
    Combo() {
        fac[0] = ifac[0] = 1LL;
        for (int i = 1; i <= sz; i++) {
            fac[i] = fac[i - 1] * i % MOD;
        }
        ifac[sz] = mod_inv(fac[sz]);
        for (int i = sz; i > 0; i--) {
            ifac[i-1] = ifac[i] * i % MOD;
        }
    }
 
    ll mod_pow(ll a, ll b) {
        if (b == 0) return 1LL;
        ll p = mod_pow(a, b >> 1);
        p = p * p % MOD;
        if (b & 1)
            p = p * a % MOD;
        return p;
    }
 
    ll mod_inv(ll n) {
        return mod_pow(n, MOD - 2);
    }
 
    ll comb(ll n, ll r) {
        if (n == -1 && r == -1) return 1LL;
        if (n < r || n < 0 || r < 0) return 0LL;
        ll res = (fac[n] * ifac[r] % MOD) * ifac[n - r] % MOD;
        return res;
    }
};
 
ll mod(ll x) {
    return (x % MOD + MOD) % MOD;
}
 
ll modAdd(ll x, ll y) {
    return ( (x % MOD + y % MOD) % MOD + MOD ) % MOD;
}
 
ll gcd(ll a, ll b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Combo<MX> cm;
    int t; cin >> t;
    while (t--) {
        int n, i, j, x, y; cin >> n >> i >> j >> x >> y;
        i--; j--;
        // int ans = 0;
        // FOR(k, 1, n-2) {
        //     int tmp = 0;
        //     if (k < i) {
        //         if (x < y) continue;
        //         tmp = ((cm.comb(n-x-1, i-k-1) * cm.comb(x-y-1, j-i-1))%MOD * cm.comb(y-1, n-1-j))%MOD;
        //     } else if (k > j) {
        //         if (x > y) continue;
        //         tmp = ((cm.comb(n-y-1, k-j-1) * cm.comb(y-x-1, j-i-1))%MOD * cm.comb(x-1, i))%MOD;
        //     } else {
        //         if (x < y) tmp = ((cm.comb(n-y-1, j-k-1) * cm.comb(y-x-1, k-i-1 - (n-y-1 - (j-k-1))))%MOD * cm.comb(x-1, i))%MOD;
        //         else tmp = ((cm.comb(n-x-1, k-i-1) * cm.comb(x-y-1, j-k-1 - (n-x-1 - (k-i-1))))%MOD * cm.comb(y-1, n-1-j))%MOD;
        //     }
        //     // dbg(k, tmp);
        //     ans = (ans + tmp)%MOD;
        // }
        // cout << ans << nl;

        auto check = [&](int p, int v) {
            if (p == i && v != x) return false;
            if (p == j && v != y) return false;
            return true;
        };

        int dp[n][n]; F0R(i, n) F0R(j, n) dp[i][j] = 0;
        FOR(i, 1, n-2) {
            if (check(i, n)) dp[i][i] = 1;
        }

        F0R(r, n) {
            F0Rd(l, r+1) {
                int v = n - (r-l+1);
                if (l > 0 && check(l-1, v)) dp[l-1][r] = (dp[l-1][r] + dp[l][r])%MOD;
                if (r < n-1 && check(r+1, v)) dp[l][r+1] = (dp[l][r+1] + dp[l][r])%MOD;
            }
        }

        cout << dp[0][n-1] << nl;
    }
    return 0;
}
