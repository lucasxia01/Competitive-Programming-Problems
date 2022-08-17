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
#include <climits>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pld;

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
const ll INF = (ll)1e18+5;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MXN = 400+5;
const int MXM = 2.5e5+5;
int a[MXN];
vector<vi> v(MXM);


bool check(int i, ll V) {
    int s = v[i][0]-1, f = v[i][1]-1;
    ll c = v[i][2];
    int r = v[i][3];
    // dbg(i, V, s, f, c, r);
    ll tank = V;
    for (int j = s+1; j <= f; j++) {
        tank -= c*(a[j]-a[j-1]);
        if (tank < 0) {
            r--;
            tank = V - c*(a[j]-a[j-1]);
            if (tank < 0 || r < 0) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    F0R(i, n) cin >> a[i];
    F0R(i, m) {
        F0R(j, 4) {
            int x; cin >> x;
            v[i].pb(x);
        }
    }
    shuffle(v.begin(), v.begin()+m, rng);
    ll V = 1;
    F0R(i, m) {
        // check that this V works, otherwise, we need to recompute
        if (check(i, V)) continue;
        else {
            // binary search for the new V;
            ll lo = V+1, hi = INF;
            while (lo < hi) {
                ll mid = (lo+hi)/2;
                if (check(i, mid)) hi = mid;
                else lo = mid+1;
            }
            V = lo;
        }
    }
    cout << V << nl;
    return 0;
}
