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
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const int INF = 1e5;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

void solve() {
    int n, d; cin >> n >> d;
    vi t[n];
    int x;
    t[0].pb(1);
    vpi times;
    F0R(i, n-1) {
        cin >> x;
        if (x < 0) t[-x].pb(i+2);
        else times.pb({x, i+2});
    }
    sort(times.begin(), times.end());
    int adj[n+1][n+1]; F0R(i, n+1) F0R(j, n+1) adj[i][j] = -1;
    vpi e; int u, v;
    F0R(i, d) {
        cin >> u >> v;
        e.pb({u, v});
        adj[u][v] = adj[v][u] = 0;
    }
    set<int> vis; vis.insert(1);
    int visTime[n+1]; F0R(i, n+1) visTime[i] = -1;
    visTime[1] = 0;
    int count = 1;
    int maxTime = 0;
    int curT = 0;
    while (count < n) {
        if (sz(t[count]) == 0) {
            int t = times[curT].f;
            int v = times[curT].s;
            trav(u, vis) {
                if (adj[u][v] == 0) {
                    assert(visTime[u] != -1);
                    adj[u][v] = adj[v][u] = t - visTime[u];
                    visTime[v] = t;
                    vis.insert(v);
                }
            }
            maxTime = t;
            curT++;
            count++;
            continue;
        }
        
        trav(u, vis) {
            trav(v, t[count]) {
                if (adj[u][v] == 0) {
                    assert(visTime[u] != -1);
                    adj[u][v] = adj[v][u] = maxTime+1 - visTime[u];
                    visTime[v] = maxTime+1;
                    vis.insert(v);
                } else assert(adj[u][v] == -1);
            }
        }
        maxTime++;
        count+=sz(t[count]);
    }
    trav(a, e) {
        if (adj[a.f][a.s] == 0) adj[a.f][a.s] = INF;
        cout << adj[a.f][a.s] << " ";
    } cout << nl;
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    F0R(i, t) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    
    return 0;
}
