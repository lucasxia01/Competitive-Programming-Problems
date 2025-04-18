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

const int MX = 1<<20;

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a)%MOD;
        a = (a * a)%MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        ll n, p; cin >> n >> p;
        ll k[n]; F0R(i, n) cin >> k[i];
        ll minP = 0;
        if (p > 1) {
            ll pow = 1;
            while (n > pow) {
                minP++;
                pow *= p;
            }
        } else minP = INF;
        sort(k, k+n, greater<int>());
        ll sum = 0, sumDividedBypk = 0;
        bool over = 0;
        F0R(i, n) {
            if (i && sumDividedBypk) {
                if (k[i-1]-k[i] >= minP) over = 1;
                else if (sumDividedBypk*binpow(p, k[i-1]-k[i]) >= n) over = 1;
                else sumDividedBypk *= binpow(p, k[i-1]-k[i]);
            }
            if (over) sum = ((sum - binpow(p, k[i]))%MOD+MOD)%MOD;
            else {
                if (sumDividedBypk == 0) {
                    sum = ((sum + binpow(p, k[i]))%MOD+MOD)%MOD;
                    sumDividedBypk++;
                    if (sumDividedBypk >= n) over = 1;
                } else {
                    sum = ((sum - binpow(p, k[i]))%MOD+MOD)%MOD;
                    sumDividedBypk--;
                }
            }
        }
        cout << sum << nl;
    }
    return 0;
}
