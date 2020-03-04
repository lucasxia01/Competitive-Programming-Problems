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

const int MAX_N = 100011;
const int MX = 1<<20;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a < b ? 0 : (a=b, 1);
}
template <typename T> bool ckmax(T& a, const T& b) {
    return a > b ? 0 : (a=b, 1);
}

const ll N = 1000000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    ll a[n];
    ll ans = 0;
    F0R(i, n) {
        cin >> a[i];
        if (a[i]&1) ans++;
    }
    vl check;
    bool isPrime[N] = {};
    for (ll i = 3; i < N; i+=2) {
        if (!isPrime[i]) {
            check.pb(i);
            for (ll j = 3*i; j < N; j += 2*i) {
                isPrime[j] = true;
            }
        }
    }
    ll div = 1;
    while (1) {
        if ((a[0]+ans)/div < N) break;
        for(ll i = (a[0]-ans)/div; i <= (a[0]+ans)/div; i++) {
            if (i < N) {
                i = 1e6;
                continue;
            }
            if (i%2 && i%3 && i%5 && i%7 && i%11 && i%13) check.pb(i);
        }
        div++;
    }
    ll u, v;
    trav(m, check) {
        ll count = 0;
        F0R(i, n) {
            u = a[i]%m;
            v = m-(a[i]%m);
            if (a[i] < m) count += v;
            else if (u < v) count += u;
            else count += v;
            if (count >= ans) break;
        }
        ckmin(ans, count);
    }
    cout << ans << endl;
    return 0;
}
