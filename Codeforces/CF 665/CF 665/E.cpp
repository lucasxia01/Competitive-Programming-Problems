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

const int MX = 1e6+5;

struct P {
    int x, t, y1, y2;
    bool operator<(const P& other) const {
        int t1 = -t, t2 = -other.t;
        return (tie(x, t1) < tie(other.x, t2));
    }
};

vector<P> v;
int f[MX];
void upd(int i, int v) {
    while (i < MX) {
        f[i] += v;
        i += (i&-i);
    }
}

int query(int i) {
    int sum = 0;
    while (i) {
        sum += f[i];
        i -= (i&-i);
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    ll ans = 1;
    F0R(i, n) {
        int y, lx, rx; cin >> y >> lx >> rx;
        v.pb({lx, 1, y, y});
        v.pb({rx, -1, y, y});
        if (lx == 0 && rx == 1000000) ans++;
    }
    F0R(i, m) {
        int x, ly, ry; cin >> x >> ly >> ry;
        v.pb({x, 0, ly, ry});
        if (ly == 0 && ry == 1000000) ans++;
    }
    sort(v.begin(), v.end());
    trav(p, v) {
        auto [x, t, y1, y2] = p;
//        cout << x << " " << t << " " << y1 << " " << y2 << nl;
        if (t) upd(y1+1, t);
        else {
//            cout << x << " " << y1 << " " << y2 << " " << query(y2+1) << " " << query(y1) << nl;
            ans += query(y2+1)-query(y1);
        }
    }
    cout << ans << nl;
    return 0;
}
