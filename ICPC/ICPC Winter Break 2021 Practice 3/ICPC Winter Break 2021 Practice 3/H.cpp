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

const int MX = 1e4+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int p, v; cin >> p >> v;
    vpi sizes[MX];
    F0R(i, p) {
        int a, b;
        cin >> a >> b;
        sizes[min(a,b)].pb({(a==b), i});
        if (a != b) sizes[max(a,b)].pb({1, i});
    }
    F0R(i, MX) sort(all(sizes[i]));
    pi c[v];
    F0R(i, v) { cin >> c[i].f; c[i].s = i; }
    sort(c, c+v);
    int ans[v]; F0R(i, v) ans[i] = -1;
    int taken[p]; F0R(i, p) taken[i] = 0;
    F0R(i, v) {
        while (sz(sizes[c[i].f]) && taken[sizes[c[i].f].back().s]) {
            sizes[c[i].f].pop_back();
        }
        if (sz(sizes[c[i].f])) {
            ans[c[i].s] = sizes[c[i].f].back().s;
            taken[sizes[c[i].f].back().s] = 1;
        } else {
            cout << "impossible" << nl;
            return 0;
        }
    }
    F0R(i, v) cout << ans[i]+1 << nl;
    return 0;
}
