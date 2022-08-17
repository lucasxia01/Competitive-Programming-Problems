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

const int MX = 2e5+9;

struct P {
    int x, y;
    bool operator<(const P& o) const {
        return (tie(x, y) < tie(o.x, o.y));
    }
};
int seg[2*MX];
void upd(int i, int v) {
    i += MX;
    while (i) {
        ckmax(seg[i], v);
        i>>=1;
    }
}

int query(int i) {
    int l = 0, r = i;
    int ans = 0;
    for (l += MX, r += MX; l < r; l>>=1, r>>=1) {
        if (l&1) ckmax(ans, seg[l++]);
        if (r&1) ckmax(ans, seg[--r]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int x, y, ex, ey; cin >> x >> y >> ex >> ey;
    P e[n];
    set<int> vals;
    F0R(i, n) {
        cin >> e[i].x >> e[i].y;
        if (x > ex) e[i].x = -e[i].x;
        if (y > ey) e[i].y = -e[i].y;
        vals.insert(e[i].x);
        vals.insert(e[i].y);
    }
    sort(e, e+n);
    if (x > ex) x = -x, ex = -ex;
    if (y > ey) y = -y, ey = -ey;
    vals.insert(x); vals.insert(ex);
    vals.insert(y); vals.insert(ey);
    map<int, int> m; int ii = 0; trav(v, vals) m[v] = ii++;
    x = m[x]; y = m[y]; ex = m[ex]; ey = m[ey];
    F0R(i, n) e[i].x = m[e[i].x], e[i].y = m[e[i].y];
//    dbg_out(x, y, ex, ey);
    // bottom left to upper right
    F0R(i, n) {
//        dbg_out(e[i].x, e[i].y);
        if (e[i].x < x || e[i].x > ex || e[i].y < y || e[i].y > ey) continue;
        upd(e[i].y, max(seg[e[i].y+MX], query(e[i].y+1)+1));
//        dbg_out(seg[e[i].y+MX]);
    }
    cout << query(MX) << nl;
    
    return 0;
}
