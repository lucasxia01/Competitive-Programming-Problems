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

const int MX = 1e5+5;

vpi gr[MX];
pi d1[MX];
int d2[MX];

void dijk() {
    priority_queue<pair<pi, int>, vector<pair<pi, int> >, greater<pair<pi, int> > > pq;
    pq.push({{0, 0}, 0});
    while (!pq.empty()) {
        pair<pi, int> t = pq.top(); pq.pop();
        if (t.f > d1[t.s]) continue;
        trav(u, gr[t.s]) {
            pi new_dist = {t.f.f, t.f.s + u.s};
            if (t.f.s + u.s > 12) {
                new_dist = {t.f.f+1, u.s};
            }
            if (ckmin(d1[u.f], new_dist)) {
                pq.push({new_dist, u.f});
            }
        }
    }
}

void dijk2() {
    priority_queue<pi, vector<pi>, greater<pi> > pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        pi t = pq.top(); pq.pop();
        if (t.f > d2[t.s]) continue;
        trav(u, gr[t.s]) {
            int new_dist = u.s+t.f;
            if (ckmin(d2[u.f], new_dist)) {
                pq.push({new_dist, u.f});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    F0R(i, m) {
        int u, v, d;
        cin >> u >> v >> d;
        gr[u].pb({v, d});
        gr[v].pb({u, d});
    }
    F0R(i, n) {d1[i] = {INF, INF}; d2[i] = INF;}
    d1[0] = {0, 0};
    d2[0] = 0;
    dijk();
    // cout << d1[n-1].f*12 + d1[n-1].s << nl;
    dijk2();
    pi b;
    if (d2[n-1]%12 == 0) {
        b = {d2[n-1]/12 - 1, 12};
    } else b = {d2[n-1]/12, d2[n-1]%12};
    if (d2[n-1] == 0) {
        b = {0, 0};
    }
    cout << -(24*(b.f-d1[n-1].f) + b.s-d1[n-1].s) << nl;
    return 0;
}
