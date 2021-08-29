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
const ll INF = 1e9+1005;
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

const int MX = 3e5+5;
pi st[2*MX];
vi vals[MX];

void upd(int i, int v) {
    i += MX;
    st[i] = {v, i-MX};
    i>>=1;
    while (i) {
        st[i] = min(st[i<<1], st[i<<1|1]);
        i>>=1;
    }
}

// returns {y, x};
pi query(int l, int r) { // [l, r)
    pi ans = {INF, -1};
    for (l += MX, r += MX; l < r; l>>=1, r>>=1) {
        if (l&1) ckmin(ans, st[l++]);
        if (r&1) ckmin(ans, st[--r]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int d, s; cin >> d >> s;
    set<int> x;
    map<pi, int> dropIdx; // map from coords to index of drop to print answer at the end
    int ans[d]; F0R(i, d) ans[i] = 0;
    pi drops[d]; F0R(i, d) {
        cin >> drops[i].f >> drops[i].s;
        x.insert(drops[i].f);
    }
    pair<int, pi> segs[s];
    F0R(i, s) {
        cin >> segs[i].s.f >> segs[i].s.s >> segs[i].f;
        x.insert(segs[i].s.f);
        x.insert(segs[i].s.s);
    }
    map<int, int> m;
    int ii = 0;
    trav(xx, x) m[xx] = ii++;
    vpi alldrops; // y coord, then x coord
    F0R(i, d) {
        drops[i].f = m[drops[i].f];
        dropIdx[{drops[i].f, drops[i].s}] = i;
        alldrops.pb({drops[i].s, drops[i].f});
    }
    sort(all(alldrops));
    reverse(all(alldrops)); // we should have highest y first
    F0R(i, s) {
        segs[i].s.f = m[segs[i].s.f];
        segs[i].s.s = m[segs[i].s.s];
    }
    sort(segs, segs+s);
    reverse(segs, segs+s);
    F0R(i, MX) vals[i].pb(INF);
    F0Rd(i, 2*MX) st[i] = {INF, i};

    int curDropIdx = 0;
    F0R(i, s) {
        // first deal with all the drops higher than this segment
        while (curDropIdx < sz(alldrops) && alldrops[curDropIdx].f > segs[i].f) {
            // insert this drop into the segtree
            int X = alldrops[curDropIdx].s, Y = alldrops[curDropIdx].f;
            upd(X, Y);
            // also add it to the list of drops at this x position
            vals[X].pb(Y);
            // dbg("adding drops", X, Y);
            curDropIdx++;
        }

        // want to query 
        int prevY = -1;
        // F0R(i, 16) cout << st[i].f << " "; cout << nl;
        while (1) {
            pi ret = query(segs[i].s.f, segs[i].s.s+1);
            // dbg(segs[i].s.f, segs[i].s.s+1, segs[i].f, ret.f, ret.s);
            if (ret.f == INF) break;
            if (prevY != -1 && ret.f != prevY) break;
            prevY = ret.f;
            assert(ret.s != -1);
            // ret.s is the x-coord of the drop
            // we need to remove the drop from vals and the segtree too and update with the new value
            vals[ret.s].pop_back();
            int newY = vals[ret.s].back();
            upd(ret.s, newY);
            // dbg("updating ans", ret.s, ret.f, dropIdx[{ret.s, ret.f}], segs[i].f);
            ans[dropIdx[{ret.s, ret.f}]] = segs[i].f; // cur Y coord
        }
    }

    F0R(i, d) cout << ans[i] << nl;

    return 0;
}
