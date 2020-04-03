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
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ld n, w, u, v, t1, t2, m, l, p;
    cin >> n >> w >> u >> v >> t1 >> t2;
    char dir;
    vector<pair<ld, int> > times; // convert everything based on times
    F0R(i, n) {
        cin >> dir;
        cin >> m;
        F0R(j, m) {
            cin >> l >> p;
            if (dir == 'E') p = -p;
            p -= (ld)i*u*(w/v); // shift everything to the first lane
            times.pb(mp(p/u, 1));
            times.pb(mp((p+l)/u, -1));
        }
    }
    sort(times.begin(), times.end());
    int c = 0;
    ld prev = t1;
    ld ans = 0;
    trav(a, times) {
        if (a.f > t2*u) {
            if (c == 0) ckmax(ans, min(t2, a.f-(w/v))-prev);
            break;
        }
        if (c == 0) ckmax(ans, a.f-prev-(w/v));
        c += a.s;
        if (c == 0) prev = max(t1, a.f);
    }
    if (c == 0) ckmax(ans, t2-prev);
    cout.precision(5);
    cout << fixed << ans << endl;
}
