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
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MX = 1e7+5;

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

ll ans[MX];
ll primeCount[MX] = {};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vi p;
    bool notPr[MX] = {};
    int spf[MX] = {};
    for (int i = 2; i < MX; i++) {
        if (!notPr[i]) {
            p.pb(i);
            for (int j = i; j < MX; j += i) {
                notPr[j] = 1;
                if (!spf[j]) spf[j] = i;
            }
        }
    }
    ans[1] = 1;
    for (int i = 2; i < MX; i++) {
        int k = i;
        ans[i] = ans[i-1];
        while (k != 1) {
            primeCount[spf[k]]++;
            if (primeCount[spf[k]]%2==0) ans[i] = (((ans[i]*spf[k])%MOD)*spf[k])%MOD;
            k /= spf[k];
        }
    }
    for (int n; cin >> n && n;) printf("%lld\n", ans[n]);
    return 0;
}
