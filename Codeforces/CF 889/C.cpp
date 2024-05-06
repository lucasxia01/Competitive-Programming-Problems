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

const int MX = 1000+5;

template<int sz> struct Combo {
    ll fac[sz+1], ifac[sz+1];
    Combo() {
        fac[0] = ifac[0] = 1LL;
        for (int i = 1; i <= sz; i++) {
            fac[i] = fac[i - 1] * i % MOD;
            ifac[i] = mod_inv(fac[i]);
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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Combo<MX> cm;
    int INV2 = cm.mod_inv(2);
    int invpow2[MX]; invpow2[0] = 1;
    FOR(i, 1, MX-1) invpow2[i] = invpow2[i-1] * INV2 % MOD;
    int n, m; cin >> n >> m;
    int a[n+1]; F0R(i, n) cin >> a[i];
    a[n] = m+1;
    int ans = 0;
    F0R(i, n) {
        int dp[m+2][m+2]; F0R(j, m+2) F0R(k, m+2) dp[j][k] = 0;
        dp[a[i]][a[i+1]] = 1;
        dbg(a[i], a[i+1]);
        F0R(j, m+2) {
            F0R(k, m+1) {
                if (j >= k) continue;
                dp[j+1][k] = (dp[j+1][k] + (1LL*INV2*dp[j][k]%MOD))%MOD;
                dp[j][k+1] = (dp[j][k+1] + (1LL*INV2*dp[j][k]%MOD))%MOD;
            }
        }
        // F0Rd(k, m+2) {
        //     F0R(j, m+2) cout << dp[j][k] << " ";
        //     cout << nl;
        // }
        int tmp = 0;
        int t = m+1-a[i];
        F0R(j, m+2) tmp = (tmp + (1LL*t*dp[j][m+1]%MOD))%MOD;
        F0R(j, m+2) tmp = (tmp + (1LL*(j-a[i])*dp[j][j]%MOD))%MOD;
        dbg(tmp);
        ans = (ans + tmp)%MOD;
    }
    cout << ans << nl;
    return 0;
}
