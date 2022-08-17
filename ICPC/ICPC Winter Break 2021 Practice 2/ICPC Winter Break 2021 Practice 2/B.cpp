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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

struct Trip {
    int s, t, d;
    bool operator<(const Trip& o) const {
        return (s < o.s);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<Trip> a[n+1];
    int x, s, t, d;
    F0R(i, m) {
        cin >> x >> s >> t >> d;
        Trip tr; tr.s=s; tr.t=t;tr.d=d;
        a[x].pb(tr);
    }
    // calculate the minimum time (with all the delays) to get to each station
    // this will be the benchmark to test for compensation
    int T[n+1]; F0R(i, n+1) T[i] = INF; T[1] = 0;
    FOR(i, 1, n-1) {
        trav(trip, a[i]) {
            if (trip.s+trip.d >= T[i]) ckmin(T[i+1], trip.t+trip.d);
        }
    }
    int ans = INF;
    vector<pair<int, int> > v;
    trav(b, a[1]) v.pb(mp(b.t, b.s));
    FOR(i, 2, n) {
        vector<pair<int, int> > v1;
        sort(all(v));
//        trav(vv, v) dbg(vv.f, vv.s);
        dbg(T[i]);
        trav(vv, v) if (T[i]-vv.f >= 1800) ckmin(ans, vv.s);
        if (i == n) break;
        sort(all(a[i]));
        int quickest[sz(a[i])];
        int cur = INF;
        F0Rd(j, sz(a[i])) {
            ckmin(cur, a[i][j].s);
            quickest[j] = cur;
        }
        int j = 0;
        trav(vv, v) {
            while (j < sz(a[i]) && a[i][j].s < vv.f) j++;
            if (j != sz(a[i])) v1.pb(mp(quickest[j], vv.s));
        }
        v = v1;
    }
    if (ans != INF) cout << ans << nl;
    else cout << "impossible" << nl;
    return 0;
}
