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

const int MX = 55;

int par[MX], sze[MX];

int find(int p) {
    return (p == par[p] ? p : (par[p]=find(par[p])));
}

bool merge(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return 1;
    if (sze[a] < sze[b]) swap(a, b);
    par[b] = a;
    sze[a] += sze[b];
    return 0;
}

struct Circle {
    ll x, y, r;
    bool intersect(const Circle& o) const {
        return ((x-o.x)*(x-o.x)+(y-o.y)*(y-o.y) < (r+o.r)*(r+o.r) &&
                (x-o.x)*(x-o.x)+(y-o.y)*(y-o.y) > (r-o.r)*(r-o.r));
    }
    bool touch(const Circle& o) const {
        return ((x-o.x)*(x-o.x)+(y-o.y)*(y-o.y) <= (r+o.r)*(r+o.r) &&
        (x-o.x)*(x-o.x)+(y-o.y)*(y-o.y) >= (r-o.r)*(r-o.r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("circles.in", "r", stdin);
//    freopen("circles.out", "w", stdout);
    int n; cin >> n;
    Circle c[n];
    int ans = 1;
    F0R(i, n) {
        cin >> c[i].x >> c[i].y >> c[i].r;
        par[i] = i;
        sze[i] = 1;
        bool inter = 0;
        F0R(j, i) { // count intersection points
            if (c[i].intersect(c[j])) ans += 2, inter = 1;
            if (c[i].touch(c[j])) if (merge(i, j)) ans++;
        }
        if (!inter) ans++;
        cout << ans << nl;
    }
    cout << ans << nl;
    return 0;
}
