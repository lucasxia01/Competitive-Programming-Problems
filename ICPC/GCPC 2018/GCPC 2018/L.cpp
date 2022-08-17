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

const int MX = 102;

int ans[MX][MX], g[MX][MX];
int dx[3] = {-1, 0, 1}, dy[3] = {-1, 0, 1};
int h, w;
int count(int x, int y) {
    int cnt = 0;
    F0R(i, 3) F0R(j, 3) {
        int nx = x+dx[i], ny = y+dy[j];
        if (nx < 1 || nx > h || ny < 1 || ny > w) continue;
        cnt += ans[nx][ny];
    }
    return cnt;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> h >> w;
    F0R(i, h+2) F0R(j, w+2) cin >> g[i][j];
    bool ok = 1;
    F0R(i, h+2) {
        F0R(j, w+2) {
            int cnt = count(i, j);
            if (i < h && j < w) {
                if (cnt+1 == g[i][j]) ans[i+1][j+1] = 1;
                else if (cnt != g[i][j]) ok = 0;
            } else ok &= (cnt == g[i][j]);
        }
    }
    if (!ok) cout << "impossible" << nl;
    else {
        FOR(i, 1, h) {
            FOR(j, 1, w) cout << ".X"[ans[i][j]];
            cout << nl;
        }
    }
    return 0;
}
