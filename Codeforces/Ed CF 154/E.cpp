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
const ll INF = 1e17;
const ll MOD = 998244353;
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

const int MX = 4000+5;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Combo<MX> cm;
    int t = 1; 
    while (t--) {
        int n, k; cin >> n >> k;
        // precompute size k windows with j unique
        // int cnt[n+1][k+1];
        // F0R(i, n+1) cnt[0][i] = -INF;
        // cnt[0][0] = 0;
        // F0R(i, k) {
        //     F0R(j, k+1) {
        //         if (cnt[i][j] == -INF) continue;
        //         cnt[i+1][j] = mod(cnt[i+1][j]+mod(cnt[i][j]*j));
        //         cnt[i+1][j+1] = mod(cnt[i+1][j+1]+mod(cnt[i][j]*(n-j)));
        //     }
        // }
        // now precompute # of seqs that end in i steps
        int c[n+1]; F0R(i, k) c[i] = 0; // first ends at i
        int pref[n+1]; F0R(i, n+1) pref[i] = 0;
        FOR(i, k, n) {
            c[i] = mod(cm.fac[k]*cm.mod_pow(k, i-k));
            dbg(i, c[i]);
            FOR(j, k, i-1) {
                int val = c[j];
                if (i-j < k) {
                    val = mod(val*cm.fac[i-j]);
                } else {
                    val = mod(val*mod(cm.mod_pow(k, i-j-k)*cm.fac[k]));
                }
                c[i] = mod(c[i]-val);
            }
            pref[i] = pref[i-1]+c[i];
            dbg(i, c[i]);
        }
        int dp[n+1], cnt[n+1]; 
        F0R(i, n+1) {
            dp[i] = cnt[i] = 0;
        }
        dp[0] = 0; cnt[0] = 1;
        F0R(i, n) {
            FOR(j, i+k, n) {
                cnt[j] = mod(cnt[j]+mod(cnt[i]*c[j-i]));
                dp[j] = mod(dp[j]+mod(cnt[i]*c[j-i]));
            }
        }
        ll ans = 0;
        F0R(i, n+1) {
            dbg(i, cnt[i], dp[i]);
            ans = mod(ans + mod(dp[i]*cm.mod_pow(k, n-i)));
        }
        cout << ans << nl;
    }
    return 0;
}
