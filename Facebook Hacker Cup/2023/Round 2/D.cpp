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

const int MX = 1e6+5;

map<int, ll> dp[MX+1][21];

template<int sz> struct Combo {
    ll fac[sz+1], ifac[sz+1];
    Combo() {
        fac[0] = 1LL;
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
    // // Combo<MX> cm;
    // cout.flush();
    // int lp[MX];
    // vi pr;
    // FOR(i, 2, MX-1) {
    //     if (lp[i] == 0) {
    //         pr.pb(i);
    //         lp[i] = i;
    //     }
    //     dbg(j);
    //     for (int j = 0; i*pr[j] < MX; j++) {
    //         lp[i*pr[j]] = pr[j];
    //         if (pr[j]==lp[i]) break;
    //     }
    // }
    int t = 1; 
    cin >> t;
    FOR(tt, 1, t) {
        cout << "Case #" << tt << ": ";
        int n, k, d; cin >> n >> k >> d;
        int h[n]; F0R(i, n) cin >> h[i];
        F0R(i, n+1) F0R(j, k+1) dp[i][j].clear();
        // dp on N * K * ~100  = 15 billion = easy
        dp[0][0].insert({0, 1LL});
        FOR(i, 1, n) {
            F0R(j, k+1) {
                trav(v, dp[i-1][j]) {
                    dp[i][j][v.f] = v.s;
                }
                if (j == 0) continue;
                trav(v, dp[i-1][j-1]) {
                    int g = gcd(h[i-1], v.f);
                    if (!dp[i][j].count(g)) dp[i][j][g] = v.s;
                    else {
                        dp[i][j][g] += v.s;
                    }
                }
            }
        }
        // now see what things divide d
        ll ans = 0;
        trav(p, dp[n][k]) {
            if (d%p.f == 0) {
                ans += p.s;
            }
        }
        ll kfac = 1;
        FOR(i, 1, k) {
            kfac *= i;
            kfac %= MOD;
        }
        cout << (kfac*ans)%MOD << nl;
    }
    return 0;
}