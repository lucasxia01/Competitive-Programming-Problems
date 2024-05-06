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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Combo<205> cm;
    int n; cin >> n;
    int c[n]; F0R(i, n) cin >> c[i];
    vi t[n]; 
    F0R(i, n) {
        int x; cin >> x; x--;
        t[x].pb(i);
    }
    // DP[i][j] is number of votings after processed i people, j voted for own team
    int DP[n+1][n+1]; F0R(i, n+1) F0R(j, n+1) DP[i][j] = 0;
    DP[0][0] = 1;
    F0R(i, n) { // for each team i
        // compute dp for it
        int m = sz(t[i]); // size of the team
        int dp[m+1][m+1]; F0R(j, m+1) F0R(k, m+1) dp[j][k] = 0; 
        dp[0][0] = 1;
        // dp[j][k] is number of ways for k people to vote for own team after processing j people
        F0R(j, m) {
            int v = c[t[i][j]]; // number of votes for this person
            F0R(k, m+1) {
                if (dp[j][k] == 0) continue;
                F0R(l, v+1) { // l votes for this person from own team
                    if (k+l > m) break;
                    dp[j+1][k+l] += mod(dp[j][k]*mod(cm.ifac[l]*cm.ifac[v-l]));
                    dp[j+1][k+l] %= MOD;
                }
            }
        }
        F0R(j, n+1) {
            if (DP[i][j] == 0) continue;
            F0R(k, m+1) {
                DP[i+1][j+k] += mod(DP[i][j]*mod(dp[m][k]*mod(cm.comb(m, k)*cm.fac[k])));
                DP[i+1][j+k] %= MOD;
            }
        }
    }
    int ans = 0;
    F0R(i, n+1) {
        dbg(i, mod(DP[n][i]*cm.fac[n-i]));
        ans += mod((i%2?-1:1)*mod(DP[n][i]*cm.fac[n-i]));
        ans %= MOD;
    }
    cout << ans << nl;
    return 0;
}
