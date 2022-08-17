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
const ll INF = 2e9+1;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Point {
    int x, y, z;
    bool operator<(const Point& o) const {
        return (x < o.x) || (x == o.x && y < o.y) || (x == o.x && y == o.y && z < o.z);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, h; cin >> n >> m >> h;
    string a[n]; F0R(i, n) cin >> a[i];
    string b[n]; F0R(i, n) cin >> b[i];
    vector<Point> minAns, maxAns;
    int lo = 0, hi = 0;
    F0R(i, n) {
        vi c1, c2;
        F0R(j, m) if (a[i][j] == '1') c1.pb(j);
        F0R(j, h) if (b[i][j] == '1') c2.pb(j);
        if ((!sz(c1)&&sz(c2)) || (sz(c1)&&!sz(c2))) {
            cout << -1 << nl;
            return 0;
        }
        int s1 = sz(c1), s2 = sz(c2);
        lo += max(s1, s2);
        hi += s1*s2;
        trav(j, c1) trav(k, c2) maxAns.pb({i, j, k});
        int l = 0;
        for (; l < min(s1, s2); l++) minAns.pb({i, c1[s1-1-l], c2[s2-1-l]});
        if (s2 > s1) for (; l < s2; l++) minAns.pb({i, c1[0], c2[s2-1-l]});
        else if (s1 > s2) for (; l < s1; l++) minAns.pb({i, c1[s1-1-l], c2[0]});
        assert(l == max(s1, s2));
    }
    sort(minAns.begin(), minAns.end());
    sort(maxAns.begin(), maxAns.end());
    assert(lo == sz(minAns));
    assert(hi == sz(maxAns));
    cout << hi << nl;
    trav(a, maxAns) cout << a.x << " " << a.y << " " << a.z << nl;
    cout << lo << nl;
    trav(a, minAns) cout << a.x << " " << a.y << " " << a.z << nl;
    return 0;
}
