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
const ll MOD = 100000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MX = 360000;

ll binpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a)%MOD;
        a = (a * a)%MOD;
        b >>= 1;
    }
    return res;
}

ll gcd(ll a, ll b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(a%b, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for (int s, p; cin >> s >> p && s != -1;) {
        int f[MX] = {};
        int a[MX];
        F0R(i, p) {
            cin >> a[i];
            f[a[i]] = 1;
        }
        int minPer = MX;
        FOR(i, 1, MX) {
            if (MX%i != 0) continue;
            bool ok = 1;
            F0R(j, p) if (f[a[j]] && !f[(a[j]+i)%MX]) {
                ok = 0; break;
            }
            if (ok) {
                minPer = i; break;
            }
        }
        ll count = 0;
        F0R(i, minPer) if (f[i]) count++;
        assert(p%count==0);
        int g = p/count;
        ll ans = 0;
        ll t = binpow((ll)s, count);
        // burnsides
        FOR(i, 1, g) {
            ll add = binpow(t, gcd(i, g));
            ans = (ans + add)%MOD;
        }
        ll invg = binpow(g, MOD-2);
        cout << (ans*invg)%MOD << nl;
    }
    return 0;
}
