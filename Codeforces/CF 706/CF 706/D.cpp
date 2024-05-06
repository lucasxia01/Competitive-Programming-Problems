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
const ll MOD = 998244353;
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

const int MX = 400+5;
int n, m;
vi gr[MX];
int dist[MX];
int cnt[MX];

void bfs(int v) {
    queue<array<int, 3> > q;
    q.push({v, -1, 0});
    while (!q.empty()) {
        array<int, 3> cur = q.front(); q.pop();
        if (dist[cur[0]] != -1 && dist[cur[0]] != cur[2]) continue;
        else if (dist[cur.f] == cur.s) {

            continue;
        }
        dist[cur.f] = cur.s;
        cnt[cur.f]++;
        if (cnt[cur.f] > 1) continue;
        trav(u, gr[cur.f])
            q.push({u, cur.s+1});
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    F0R(i, m) {
        int u, v; cin >> u >> v;
        u--; v--;
        gr[u].pb(v);
        gr[v].pb(u);
    }
    F0R(i, n) {
        // first bfs and count # trees from node i
        F0R(j, n) dist[j] = -1;
        memset(cnt, 0, sizeof cnt);
        bfs(i);
        ll total = 1;
        F0R(j, n) total = (total * cnt[j])%MOD;
//        F0R(j, n) cout << cnt[j] << " "; cout << nl;
        F0R(j, n) if (cnt[j] == 1) cout << total << " "; else cout << 0 << " ";
        cout << nl;
    }
    
    return 0;
}
