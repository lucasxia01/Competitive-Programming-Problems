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
#include <climits>

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

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 5e3 + 5;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    Combo<5005> cm;
    while (t--) {
        ll n; cin >> n;
        ll b[n]; F0R(i, n) cin >> b[i];
        int cnt = 1;
        vpi c;
        F0R(i, n) {
            if (i == n-1 || b[i] != b[i+1]) {
                c.pb({b[i], cnt});
                cnt = 1;
            } else cnt++;
        }
        trav(cc, c) {dbg(cc.f, cc.s);}
        ll N = n;
        n = sz(c);
        ll dp[n+1][N/2+1][2]; F0R(i, n+1) F0R(j, N/2+1) F0R(k, 2) dp[i][j][k] = 0;
        dp[n][0][0] = 1;
        cnt = 0;
        F0Rd(i, n) {
            F0R(j, N/2+1)  {
                int pj = j-1;
                if (i == n-1) pj = j;
                ll num = j-1 - (cnt-j);
                if (j == N/2) num++;
                int val = cm.comb(num, c[i].s-1);
                if (c[i].s == 1) val = 1;
                if (j != N/2) dp[i][j][0] = (val*(dp[i+1][pj][0] + dp[i+1][j][1])%MOD)%MOD;
                dp[i][j][1] = (cm.comb(num, c[i].s) * (dp[i+1][pj][0] + dp[i+1][j][1])%MOD)%MOD;
                dbg(i, j, cm.comb(num, c[i].s), dp[i][j][0], dp[i][j][1]);
            }
            cnt += c[i].s;
        }
        ll ans = 0;
        F0R(j, N/2+1) F0R(k, 2) ans = (ans+dp[0][j][k])%MOD;
        // FOR(i, 1, n) ans = (ans*cm.ifac[freq[i]])%MOD;
        cout << ans << nl;
    }
    return 0;
}
