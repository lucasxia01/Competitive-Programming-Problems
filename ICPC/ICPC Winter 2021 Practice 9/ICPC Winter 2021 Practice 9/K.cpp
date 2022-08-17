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

const int MX = 1e5;

vi gr[MX];
vi cur;
int sz[MX];
int total;

int dfs(int v, int p) {
    int ans = (sz(gr[v]) == 1);
    if (ans) cur.pb(v);
    trav(u, gr[v]) {
        if (u == p) continue;
        ans += dfs(u, v);
    }
    sz[v] = ans;
//    dbg(v, sz[v]);
    return ans;
}

int find(int v, int p) {
//    dbg("visiting",v);
    trav(u, gr[v]) {
        if (u == p) continue;
        if (2*sz[u] > total) {
            return find(u, v);
        }
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, h; cin >> n >> h;
    F0R(i, n-1) {
        int a, b; cin >> a >> b;
        gr[a].pb(b);
        gr[b].pb(a);
    }
    // find centroid
    total = dfs(h, -1);
    h = find(h, -1);
    
//    dbg(h);
    vector<pair<int, vi > > V;
    total = 0;
    trav(v, gr[h]) {
        cur.clear();
        int cnt = dfs(v, h);
        total += cnt;
        V.pb({cnt, cur});
    }
    sort(all(V));
    int large = V.back().f;
    vpi ans;
    if (total%2) {
        ans.pb({V.back().s.back(), h});
        V.back().s.pop_back();
        large--;
        total--;
    }
    vi u;
    trav(v, V) {
        trav(uu, v.s) {
            u.pb(uu);
        }
    }
    int half = sz(u)/2;
    assert(sz(u)%2==0);
    F0R(i, half) {
        ans.pb({u[i], u[i+half]});
    }
    cout << sz(ans) << nl;
    trav(a, ans) cout << a.f <<" " << a.s << nl;
    return 0;
}
