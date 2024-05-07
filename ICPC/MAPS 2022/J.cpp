#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cassert>

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

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1e9 + 607; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}


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

const int MX = 1e3+5;

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

const int MAXK = 100;
int n, k;
int dp[2][101*101*101];

int Nxt(int v) {
    if (v == 0) return 0;
    if (v%101 == 1) {
        v /= 101;
    }
    v--;
    if (v/101) v-=101;
    if (v/(101*101)) v-=101*101;
    return v;
}

bool Set(int& v) {
    if (v == 0) v += k;
    else if (v/101 == 0) v += k*101;
    else if (v/(101*101) == 0) v += k * 101*101;
    else return 0;
    return 1;
}

void Print(int v) {
    cout << v%101 << " " << (v/101)%101 << " " << (v/(101*101)) << nl;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Combo<MX> cm;
    cin >> n >> k;
    vi primes = {5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    ll ans = 0;
    trav(p, primes) {
        if (p <= k) {
            ans = (ans+cm.comb(k, p))%MOD;
        }
    }
    // now the 2, 3 case
    vi pos; pos.pb(0);
    FOR(i, 1, 100) {
        pos.pb(i);
        FOR(j, 1, i-1) {
            pos.pb(i*101 + j);
            FOR(l, 1, j-1) {
                pos.pb(i*101*101 + 101*j + l);
            }
        }
    }

    dp[0][0] = 1;
    FOR(i, 0, n-1) {
        trav(p, pos) {
            if (dp[i%2][p] == 0) continue;
            int nxt = Nxt(p);
            int nxt2 = nxt; bool ok = Set(nxt2);
            // dbg(i);
            // Print(p); Print(nxt); Print(nxt2);
            if ((nxt2/101 > 0 || i < k-1) && ok) {
                // cout << i << " " << nxt2 << nl;
                dp[(i+1)%2][nxt2] = (dp[(i+1)%2][nxt2]+dp[i%2][p])%MOD;
            }
            if (nxt/101 > 0 || i < k-1) {
                // cout << i << " " << nxt << nl;
                dp[(i+1)%2][nxt] = (dp[(i+1)%2][nxt]+dp[i%2][p])%MOD;
            }
            dp[i%2][p] = 0;
        }
    }
    trav(p, pos) {
        // cerr << p.f << " " << p.s << nl;
        ans = (ans + dp[n%2][p])%MOD;
    }
    cout << ans << nl;
    return 0;
}

