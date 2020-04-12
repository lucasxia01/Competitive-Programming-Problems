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

const ll MX = 1e15 + 5;
const ll sqrtMX = 3e7+2e6;

int fac[sqrtMX+1];
bool p[sqrtMX] = {};

template<int sz> struct Combo {
    Combo() {
        fac[0] = 1;
        for (int i = 1; i <= sz; i++) {
            fac[i] = (1LL*fac[i - 1] * i) % MOD;
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

vl pr, primes;
Combo<sqrtMX> com;
unordered_map<ll, ll> memo;

ll compute_ans(ll x) {
    ll y = x;
    if (memo.find(x) != memo.end()) return memo[x];
    unordered_map<ll, int> f;
    int c = 0;
    trav(a, primes) {
        while (x%a==0) {
            f[a]++;
            x /= a;
            c++;
        }
    }
    if (x > 1) c++;
    ll ret = fac[c];
    trav(a, f) {
        ret = (ret * com.mod_inv(fac[a.s]))%MOD;
    }
    memo[y] = ret;
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll D, u, v;
    cin >> D;
    
    int q;
    cin >> q;
    
    pr.pb(2);
    if (D%2==0) primes.pb(2);
    ll sqrtD = sqrt(D);
    for (int i = 3; i < sqrtD; i+=2) {
        if (!p[i]) {
            pr.pb(i);
            if (D%i==0) primes.pb(i);
            for (int j = i; j < sqrtD; j+=i) {
                p[j] = 1;
            }
        }
    }
    F0R(i, q) {
        cin >> u >> v;
        ll g = gcd(u, v);
        u /= g; v /= g;
        ll ans = (compute_ans(u) * compute_ans(v)) % MOD;
        cout << ans << '\n';
    }
    return 0;
}
