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

struct Edge
{
    int from, to, capacity, cost;
};

vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;

using C = ll;
#define V vector
typedef vector<bool> vb;
C hungarian(const V<V<C>>& a) {
    int N = sz(a)-1, M = sz(a[0])-1; assert(N <= M);
    V<C> u(N+1), v(M+1); // potentials to make edge weights >= 0
    vi job(M+1);
    FOR(i,1,N) { // find alternating path with job i
        const C inf = numeric_limits<C>::max();
        int w = 0; job[w] = i; // add "dummy" 0, find path to real worker
        V<C> dist(M+1,inf); vi pre(M+1,-1); vb done(M+1);
        while (job[w]) { // dijkstra
            done[w] = 1; int j = job[w], nexW; C delta = inf;
            // fix dist[j], update dists from j
            F0R(W,M+1) if (!done[W]) { // try all workers
                if (ckmin(dist[W],a[j][W]-u[j]-v[W])) pre[W] = w;
                if (ckmin(delta,dist[W])) nexW = W;
            }
            F0R(W,M+1) { // subtract constant from all edges going
                // from done -> not done vertices, lowers all
                // remaining dists by constant
                if (done[W]) u[job[W]] += delta, v[W] -= delta;
                else dist[W] -= delta;
            }
            w = nexW;
        } // potentials adjusted so all edge weights >= 0
        for (int W; w; w = W) job[w] = job[W = pre[w]];
    } // job[w] = 0, found alternating path
    return -v[0]; // min cost
}

struct P {
    int x, y;
    int dist(P o) {
        return (abs(o.x-x) + abs(o.y-y));
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int m, n; cin >> m >> n;
    P b[m]; F0R(i, m) cin >> b[i].x >> b[i].y;
    P a[n]; F0R(i, n) cin >> a[i].x >> a[i].y;
    P c; cin >> c.x >> c.y;
    V<C> v(n+m, INF);
    V<V<C>> M(m+1, v);
    F0R(j, m) F0R(i, n) M[j+1][i+1] = a[i].dist(b[j]) + c.dist(b[j]);
    F0R(j, m) FOR(i, n, n+m-2) M[j+1][i+1] = c.dist(b[j])+c.dist(b[j]);
    cout << hungarian(M) << nl;
    return 0;
}
