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

const int MX = 1e5+5;
pl l[MX];
int m;

struct Edge {
    ll d;
    int u, v;
    bool operator<(const Edge& o) const {
        return (d > o.d);
    }
};

ll dist(int u, int v) {
    if (v == m+1) return (abs(l[u].f-l[v].f) + abs(l[u].s-l[v].s));
    return min(abs(l[u].f-l[v].f), abs(l[u].s-l[v].s));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n >> m;
    cin >> l[0].f >> l[0].s >> l[m+1].f >> l[m+1].s;
    set<pair<ll, int> > x, y;
    int X, Y;
    F0R(i, m) {
        cin >> X >> Y;
        l[i+1] = {X, Y};
        x.insert({X, i+1}); y.insert({Y, i+1});
    }
    bool vis[m+2]; F0R(i, m+2) vis[i] = 0; vis[0] = 1;
    priority_queue<Edge> pq;
    ll ans = dist(0, m+1);
    FOR(i, 1, m) pq.push({dist(0, i), 0, i});
    while (!pq.empty()) {
        Edge e = pq.top(); pq.pop();
        if (vis[e.v]) continue;
        vis[e.v] = 1;
        ckmin(ans, e.d + dist(e.v, m+1));
        // check neighbors of e.v
        auto a = x.find({l[e.v].f, e.v});
        if (a != x.begin()) {
            a--;
            pq.push({e.d + dist(e.v, a->s), e.v, a->s});
            a++;
        }
        a++;
        if (a != x.end()) pq.push({e.d + dist(e.v, a->s), e.v, a->s});
        a--;
        x.erase(a);
        
        a = y.find({l[e.v].s, e.v});
        if (a != y.begin()) {
            a--;
            pq.push({e.d + dist(e.v, a->s), e.v, a->s});
            a++;
        }
        a++;
        if (a != y.end()) pq.push({e.d + dist(e.v, a->s), e.v, a->s});
        a--;
        y.erase(a);
    }
    cout << ans << nl;
    return 0;
}
