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

const int MX = 205;

struct Circle {
    int x, y, r;
    bool intersect(Circle o) {
        return ((x-o.x)*(x-o.x)+(y-o.y)*(y-o.y) <= (r+o.r)*(r+o.r));
    }
};

Circle c[MX];
vi gr[MX]; // 200 is left, 201 is right
bool vis[MX];
bool dfs(int v) {
    if (vis[v]) return false;
    vis[v] = 1;
    if (v == 201) return true;
    trav(u, gr[v]) {
//        dbg(v, u);
        if (dfs(u)) return true;
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    F0R(i, n) {
        cin >> c[i].x >> c[i].y >> c[i].r;
        F0R(i, MX) vis[i] = 0;
        F0R(j, i) {
            if (c[i].intersect(c[j])) {
                gr[i].pb(j);
                gr[j].pb(i);
            }
        }
        if (c[i].x-c[i].r < 0) {
            gr[i].pb(200);
            gr[200].pb(i);
        }
        if (c[i].x+c[i].r > 200) {
            gr[i].pb(201);
            gr[201].pb(i);
        }
        if (dfs(200)) {
            cout << i << nl;
            return 0;
        }
    }
    cout << n << nl;
    return 0;
}
