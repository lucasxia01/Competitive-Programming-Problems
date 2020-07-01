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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for (int tt =
    999838674; tt >= 1 ; tt--) {
        if (tt%100000 == 0) cout << tt << nl;
        ll n = tt;
        ll m = n;
        int pow2 = 0, pow3 = 0;
        while (m%2==0) {
            pow2++;
            m/=2;
        }
        m = n;
        while (m%3==0) {
            pow3++;
            m/=3;
        }
        int ans = -1;
        if (powl(2, pow2)*powl(3, pow3) == n && pow3 >= pow2)
            ans = pow3-pow2+pow3;
        
        int ns = n;
        int moves = 0;
        unordered_set<int> visited;
        visited.insert(n);
        while (ns != 1) {
            if (ns % 6 == 0) ns /= 6;
            else ns *= 2;
            if (visited.find(ns) != visited.end()) {
                assert(ans == -1);
                break;
            }
            visited.insert(ns);
            moves++;
        }
        if (ns == 1) {
            cout << tt << nl;
            assert(moves == ans);
        }
    }
    return 0;
}
