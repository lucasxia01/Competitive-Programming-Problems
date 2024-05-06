#include<bits/stdc++.h>
using namespace std;

#define F0R(i, n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)

typedef long long ll;
const ll MOD = 998244353;
#define int ll

const int MX = 1e6+6;

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

int mod(int x) {
    return (x%MOD+MOD)%MOD;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    Combo<MX> cm;
    int n, m; cin >> n >> m;
    int nm = n*m;
    int ans = cm.fac[nm];
    rep(i, 1, n) {
        int tmp = (i%2?MOD-1:1);
        int v = mod(mod(cm.comb(nm-i*m, i*m) * cm.fac[i*m]) * cm.fac[nm-i*m]);
        tmp = mod(tmp*mod(cm.comb(nm, i) * mod(cm.fac[nm] - v)));
        cerr << i << " " << v << " " << tmp << endl;
        ans = (ans+tmp)%MOD;
    }
    cout << ans << endl;
}