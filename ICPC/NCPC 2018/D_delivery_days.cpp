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

#define int long long

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
const ll INF = 1e18;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1000+5;

vector<pair<int, ll> > gr[MX];
ll dist[MX][MX];
int n, m, k;

void dijk(int s) {
    priority_queue<pl, vector<pl>, greater<pl> > pq;
    int cur = s;
    dist[s][s] = 0;
    F0R(i, n-1) {
        // add edges in cur in pq
        trav(u, gr[cur]) {
            if (dist[s][u.f] == -1) pq.push({dist[s][cur]+u.s, u.f});
        }
        // find next node
        while (1) {
            pl t = pq.top(); pq.pop();
            if (dist[s][t.s] == -1) {
                dist[s][t.s] = t.f;
                cur = t.s;
                break;
            }
        }
    }
}

ll s[MX]; 
pl o[MX];

bool check(ll t) {
    ll dp[k+1]; F0R(i, k+1) dp[i] = INF;
    dp[0] = 0;
    F0R(i, k) {
        ll base = dp[i];
        if (dp[i] == INF) continue;
        // cout << i << " " << dp[i] << nl;
        ll time = 0;
        int cur = 1;
        ll worst = -INF;
        FOR(j, i, k-1) {
            ckmax(base, o[j].s);
            time -= dist[cur][1];
            time += dist[cur][o[j].f];
            ckmax(worst, time-s[j]);
            if (base+worst > t) break;
            time += dist[o[j].f][1];
            cur = o[j].f;
            ckmin(dp[j+1], base+time);
        }
    }
    // cout << k << " " << dp[k] << nl;
    F0R(i, k) if (dp[i+1] == INF) return 0;
    return 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    F0R(i, m) {
        int u, v, w; cin >> u >> v >> w;
        gr[u].pb({v, w});
        gr[v].pb({u, w});
    }
    F0R(i, MX) F0R(j, MX) dist[i][j] = -1;
    // run dijkstras on every node
    F0R(i, n) dijk(i+1);
    // F0R(i, n) {
    //     F0R(j, n) cout << dist[i+1][j+1] << " ";
    //     cout << nl;
    // }
    cin >> k;
    F0R(i, k) cin >> s[i] >> o[i].f >> o[i].s;
    ll lo = 0, hi = 1e17;
    while (lo < hi) {
        ll mid = (lo+hi)/2;
        bool ret = check(mid);
        // cout << mid << " " << ret << nl;
        if (ret) hi = mid;
        else lo = mid+1;
    }
    cout << lo << endl;
    return 0;
}
