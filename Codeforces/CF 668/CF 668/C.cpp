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

void dbg_out () {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
    cerr << H << " "; dbg_out(T...);
}

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

struct BIT {
    int f[MX] = {};
    void upd(int i, int val) {
        for (; i < MX; i += (i&-i)) f[i] += val;
    }

    int query(int i) {
        int sum = 0;
        for (; i; i -= (i&-i)) sum += f[i];
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    int a[n]; F0R(i, n) cin >> a[i];
    int cnt = 0;
    vi u[n];
    BIT f;
    F0R(i, n) {
        if (a[i]-i-1 > 0) continue;
        if (cnt+a[i]-i-1 < 0) continue;
        else cnt++;
        int lo = 0, hi = i+1;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            int ret = f.query(i+1) - f.query(mid);
//            cout << i+1 << " " << f.query(i+1) << " " << mid << " " << f.query(mid) << " " << ret << nl;
            if (ret < i+1-a[i]) hi = mid;
            else lo = mid+1;
        }
        int mid = (lo+hi)/2-1;
        f.upd(mid+1, 1);
//        cout << a[i] << " " << mid << nl;
//        F0R(i, n) cout << f.query(i+1)-f.query(i) << " "; cout << nl;
        u[mid].pb(i);
    }
    
    int x, y;
    vector<pi> qs[n];
    F0R(i, q) {
        cin >> x >> y;
        qs[x].pb({y, i});
    }
    BIT g;
    int ans[q];
    F0Rd(i, n) {
        trav(v, u[i]) g.upd(v+1, 1);
        trav(v, qs[i]) ans[v.s] = g.query(n-v.f);
    }
    F0R(i, q) cout << ans[i] << nl;
    return 0;
}
