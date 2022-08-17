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
const ll MOD = 998244353;
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

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
    int n, m; cin >> n >> m;
    pi a[n]; F0R(i, n) cin >> a[i].f >> a[i].s;
    pi b[m]; F0R(i, m) cin >> b[i].f >> b[i].s;
    int count[n+2]; memset(count, 0, sizeof(count));
    F0R(i, n) {
        count[a[i].f]++;
        count[a[i].s+1]--;
    }
    FOR(i, 1, n) count[i] += count[i-1];
    // precompute combos
    ll combos[2*m+1][n+1];
    F0R(i, 2*m+1) combos[i][0] = 0;
    F0R(i, 2*m+1) FOR(j, 1, n) {
        if (count[j] < i || j < i) combos[i][j] = 0;
        else combos[i][j] = cm.comb(count[j]-i, j-i);
    }
    F0R(i, 2*m+1) FOR(j, 1, n) combos[i][j] = (combos[i][j]+combos[i][j-1])%MOD;
    ll ans = 0;
    F0R(i, 1<<m) {
        if (i == 0) {
            ans = (ans + combos[0][n])%MOD;
            continue;
        }
        int lo = 0, hi = n;
        int cnt = 0;
        set<int> s;
        F0R(j, m) {
            if (i&(1<<j)) {
                cnt++;
                s.insert(b[j].f);
                s.insert(b[j].s);
                ckmax(lo, a[b[j].f-1].f);
                ckmax(lo, a[b[j].s-1].f);
                ckmin(hi, a[b[j].f-1].s);
                ckmin(hi, a[b[j].s-1].s);
            }
        }
        if (hi < lo) continue;
        int SZ = sz(s);
        ll temp = (modAdd(combos[SZ][hi],-combos[SZ][lo-1]) * ((cnt&1)?MOD-1:1))%MOD;
        ans = (ans + temp)%MOD;
    }
    cout << ans << nl;
    return 0;
}
