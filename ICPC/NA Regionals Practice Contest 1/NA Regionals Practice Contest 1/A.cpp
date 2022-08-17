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
const ll LLINF = (1LL<<40);
const ll INF = LLINF;
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

const int N = 6, M = 13;
const int MX = M*M*4+5;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int idx(int x, int y, int d) {
    return ((x+N)*M+(y+N))*4+d;
}
int DIR(int i) { return (i%4);}
int Y(int i) { return ((i/4)%M - N);}
int X(int i) { return (i/(4*M) - N);}

int main() {
    ll b, s, r, l, n; cin >> b >> s >> r >> l >> n;
    ll dist[MX][MX]; F0R(i, MX) F0R(j, MX) dist[i][j] = INF;
    ll dirTrans[4][4] = {{s, l, INF, r}, {r, s, l, INF}, {INF, r, s, l}, {l, INF, r, s}};
    F0R(i, MX) dist[i][i] = 0;
    F0R(i, MX) {
        int x = X(i), y = Y(i), d = DIR(i);
        F0R(dir, 4) {
            int nx = x+dx[dir], ny = y+dy[dir];
            if (nx < -N || nx > N || ny < -N || ny > N) continue;
            dist[i][idx(nx,ny,dir)] = b+dirTrans[d][dir];
        }
    }
    F0R(k, MX) F0R(i, MX) F0R(j, MX) ckmin(dist[i][j], dist[i][k]+dist[k][j]);

    ll dp[n+1][4]; F0R(i, n+1) F0R(j, 4) dp[i][j] = LLINF;
    F0R(i, 4) dp[0][i] = 0LL;
    int x = 0, y = 0, px = 0, py = 0;
    F0R(i, n) {
        px = x; py = y;
        cin >> x >> y;
        F0R(j, 4) F0R(k, 4) ckmin(dp[i+1][j], dp[i][k] + dist[idx(px,py,k)][idx(x,y,j)]);
    }
    ll ans = LLINF;
    F0R(i, 4) ckmin(ans, dp[n][i]);
    cout << ans << nl;
    return 0;
}
