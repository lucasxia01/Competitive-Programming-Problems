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
const ll INF = (1LL<<60) + 123;
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

vpl gr[MX];
ll dist[MX];
int n, m; ll x;
ll small;

ll solve(ll mid) {
    F0R(i, n) dist[i] = INF;
    priority_queue<pl, vector<pl>, greater<pl> > pq;
    pq.push({0, 0});
//    dbg(mid);
    while (!pq.empty()) {
        pl cur = pq.top(); pq.pop();
//        dbg(cur.s, cur.f);
        if (dist[cur.s] != INF) continue;
        dist[cur.s] = cur.f;
        trav(v, gr[cur.s]) {
            if (v.s <= mid && dist[v.f] == INF) pq.push({v.s+cur.f, v.f});
        }
    }
    return dist[n-1];
}
bool check(ll mid) {
    ll d = solve(mid);
    return ((100LL+x)*small >= 100LL*d);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> x;
    F0R(i, m) {
        int a, b; ll c; cin >> a >> b >> c;
        a--; b--;
        gr[a].pb({b, c});
        gr[b].pb({a, c});
    }
    ll lo = 1, hi = 1e9+5;
    small = solve(hi);
    while (lo < hi) {
        ll mid = (lo+hi)/2;
        if (check(mid)) hi = mid;
        else lo = mid+1;
    }
    cout << (lo+hi)/2 << nl;
    return 0;
}
