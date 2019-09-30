#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>

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
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template<int sz> struct Combo {
    ll fac[sz + 1];
    ll ifac[sz + 1];
 
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

Combo<251> C;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    ll dp[n+1][n+1];
    F0R(i, n+1) F0R(j, n+1) dp[i][j] = 0;
    ll pows[n+1], pows1[n+1];
    ll pow = 1, pow1 = 1;
    F0R(i, n+1) {
        pows[i] = pow;
        pows1[i] = pow1;
        pow = (pow*(k))%MOD;
        pow1 = (pow1*(k-1))%MOD;
    }
    
    dp[0][0] = 1;
    FOR(j, 1, n+1) {
        FOR(i, 0, n+1) {
            ll sum = 0, temp;
            FOR(l, 1, i+1) {
                temp = (C.comb(i,l)*pows1[i-l])%MOD;
                temp = (temp*dp[i-l][j-1])%MOD;
                sum = (sum + temp)%MOD;
            }
            ll tem = (((pows[n-i]-pows1[n-i])+MOD)*dp[i][j-1])%MOD;
            dp[i][j] = ((sum*pows[n-i])%MOD+tem)%MOD;
            cout << i << " " << j << " " << tem << " " << dp[i][j] << endl;
        }
    }
    cout << dp[n][n] << endl;
    return 0;
}
