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
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 5e5+5;
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n; // 1, 2, ..., n-1, n;
    vi primes;
    primes.pb(1);
    bool isNotPrime[MX] = {};
    int mults[MX] = {}; // mults[i] counts the number of numbers whose largest proper factor is i
    for (int i = 2; i <= n; i++) {
        if (!isNotPrime[i]) {
            primes.pb(i);
            for (int j = 2*i; j <= n; j+=i) {
                if (!isNotPrime[j]) mults[j/i]++; // if it has not been marked before, we have found j's smallest factor, i, and its largest factor is j/i
                isNotPrime[j] = 1;
            }
        }
    }
    int ptr = sz(primes);
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        cout << ans << ' ';
        if (i == ptr) {
            ans++;
            ptr += mults[ans];
        }
    }
    cout << '\n';
    return 0;
}
