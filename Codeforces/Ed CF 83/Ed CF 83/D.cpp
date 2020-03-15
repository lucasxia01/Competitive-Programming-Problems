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
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
const int N = (int)2e5+5;
 
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
 
 
ll computePow2(ll n) {
    ll ans = 1;
    ll curPow = 2;
    while (n) {
        if (n % 2) ans = (ans * curPow)%MOD;
        n /= 2;
        curPow = (curPow * curPow) % MOD;
    }
    return ans;
}
 
int main() {
    int n, m;
    cin >> n >> m;
    ll ans = 0;
    Combo<N> c;
    // just math here
    for (int i = 1; i <= m; i++) {
        ans = modAdd(ans, mod(mod((i-1)*c.comb(i-2, n-3))*computePow2(n-3)));
    }
    cout << ans << endl;
    
    return 0;
}
