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
    int n, p;
    cin >> n >> p;
    int hi = 0;
    int a[n];
    F0R(i, n) {
        cin >> a[i];
        ckmax(hi, a[i]);
    }
    sort(a, a+n);
    int z = 0;
    int res[p]; F0R(i, p) res[i] = 0;
    int off = 1;
    F0Rd(i, n) {
        if (a[i] <= hi-n) z++;
        else {
            res[((n-(a[i]-(hi-n))-(n-i-1))%p+p)%p]++;
            ckmax(off, -((n-(a[i]-(hi-n))-(n-i-1)))+1);
        }
    }
    vi ans;
    FOR(x, hi-n+off, hi-1) {
        while (z < n && a[z] <= x) {
            res[((n-(a[z]-(hi-n))-(n-z-1))%p+p)%p]--;
            z++;
        }
        if (z >= p) break;
        if (res[((hi-n-x)%p+p)%p]) continue;
        ans.pb(x);
    }
    cout << sz(ans) << nl;
    trav(x, ans) cout << x << " "; cout << nl;
    return 0;
}
