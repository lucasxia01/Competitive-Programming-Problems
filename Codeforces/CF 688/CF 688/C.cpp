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

const int MX = 2000+5;
int n;
char a[MX][MX];
int edges[10][4];

int solve(int i, int j) {
    int d = a[i][j]-'0';
    int ret = 0;
    ckmax(ret, (edges[d][0]-i)*(max(j, n-1-j)));
    ckmax(ret, (i-edges[d][1])*(max(j, n-1-j)));
    ckmax(ret, (edges[d][2]-j)*(max(i, n-1-i)));
    ckmax(ret, (j-edges[d][3])*(max(i, n-1-i)));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        F0R(i, n) F0R(j, n) cin >> a[i][j];
        F0R(i, 10) {
            edges[i][0] = -INF; // max X
            edges[i][1] = INF; // min X
            edges[i][2] = -INF; // max Y
            edges[i][3] = INF; // min Y
        }
        vpi pos[10];
        F0R(i, n) F0R(j, n) {
            pos[a[i][j]-'0'].pb({i, j});
            ckmax(edges[a[i][j]-'0'][0], i);
            ckmin(edges[a[i][j]-'0'][1], i);
            ckmax(edges[a[i][j]-'0'][2], j);
            ckmin(edges[a[i][j]-'0'][3], j);
        }
        int ans[10] = {};
        F0R(i, n) F0R(j, n) ckmax(ans[a[i][j]-'0'], solve(i, j));
        F0R(i, 10) cout << ans[i] << " "; cout << nl;
    }
    return 0;
}
