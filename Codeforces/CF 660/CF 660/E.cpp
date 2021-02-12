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

struct Seg {
    ll y, lx, rx;
    bool operator<(const Seg& o) const {
        return (tie(y, lx, rx) < tie(o.y, o.lx, o.rx));
    }
};

struct badSeg {
    ll x, y, type;
    bool operator<(const badSeg& o) const {
        if (y*o.x == o.y*x) return (type < o.type);
        return (atan2(y, x) < atan2(o.y, o.x));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    Seg a[n];
    F0R(i, n) cin >> a[i].lx >> a[i].rx >> a[i].y;
    sort(a, a+n);
    reverse(a, a+n);
    vector<badSeg> bad;
    F0R(i, n) {
        FOR(j, i+1, n-1) {
            if (a[i].y == a[j].y) continue;
            bad.pb({a[j].lx-a[i].lx, a[j].y-a[i].y, -1});
            bad.pb({a[j].rx-a[i].lx, a[j].y-a[i].y, 1});
            bad.pb({a[j].lx-a[i].rx, a[j].y-a[i].y, -1});
            bad.pb({a[j].rx-a[i].rx, a[j].y-a[i].y, 1});
        }
    }
    sort(bad.begin(), bad.end());
    int cnt = 0;
    vpl angles;
    trav(b, bad) {
        if (!cnt) angles.pb({b.x, b.y});
        cnt += b.type;
        if (!cnt) angles.pb({b.x, b.y});
    }
    trav(an, angles) cout << an.f << " " << an.s << nl;
    reverse(a, a+n);
    priority_queue<pair<ld, ld> > hi, lo;
    ld m = 0, b = 0;
    F0R(i, n) {
        // slope is a[i].y
        if (m ==)
    }
    return 0;
}
