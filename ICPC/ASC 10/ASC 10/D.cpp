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

const int MX = 45;
vi primes;
ll n;
ll maxFacts, ans = 1e17;
void solve(int i=0, ll num=1, ll facts=1) {
//    cout << primes[i] << " " << num << " " << facts << nl;
    if (ckmax(maxFacts, facts) || (facts==maxFacts && num < ans)) ans = num;
    ll pow = 1;
    int exp = 0;
    while (1) {
        pow *= primes[i];
        exp++;
        if (num*pow > n) return; // no overflow cuz 1e16
        solve(i+1, num*pow, facts*(exp+1));
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("divisors.in", "r", stdin);
//    freopen("divisors.out", "w", stdout);
    cin >> n;
    int nP[MX] = {};
    
    for (int i = 2; i < MX; i++) {
        if (!nP[i]) {
            primes.pb(i);
            for (int j = 2*i; j < MX; j+=i) nP[j] = 1;
        }
    }
    solve();
    cout << ans << nl;
    return 0;
}
