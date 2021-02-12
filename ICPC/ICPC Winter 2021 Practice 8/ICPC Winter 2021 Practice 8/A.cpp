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

const int MX = 205;

ld d(pair<ld, ld> p1, pair<ld, ld> p2) {
    return sqrtl((p1.f-p2.f)*(p1.f-p2.f)+(p1.s-p2.s)*(p1.s-p2.s));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    pair<ld, ld> pts[MX];
    ld x0, y0, x1, y1; cin >> x0 >> y0 >> x1 >> y1;
    pts[0] = {x0, y0};
    pts[1] = {x1, y1};
    int n; cin >> n;
    int N = 2*n+2;
    ld dist[N][N]; F0R(i, N) F0R(j, N) dist[i][j] = INF; F0R(i, N) dist[i][i] = 0;

    F0R(i, n) {
        cin >> x0 >> y0 >> x1 >> y1;
        pts[2*i+2] = {x0, y0};
        pts[2*i+3] = {x1, y1};
        dist[2*i+2][2*i+3] = d(pts[2*i+2], pts[2*i+3])/2;
    }
    F0R(i, N) F0R(j, N) {
        ckmin(dist[i][j], d(pts[i], pts[j]));
    }
    F0R(k, N) F0R(i, N) F0R(j, N) {
        ckmin(dist[i][j], dist[i][k]+dist[k][j]);
    }
    cout.precision(10);
    cout << dist[0][1] << nl;
    return 0;
}
