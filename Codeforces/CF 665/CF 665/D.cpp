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
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;

vi gr[MX];
map<pi, ll> m;

ll solve(int v, int u) {
    if (m[{v,u}]) return m[{v,u}];
    ll total = 0;
    trav(w, gr[u]) if (w != v) total += solve(u, w);
    return (m[{v,u}]=m[{u,v}]=total+1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int u, v;
        vpi edges;
        F0R(i, n-1) {
            cin >> u >> v;
            gr[u].pb(v);
            gr[v].pb(u);
            edges.pb({u, v});
        }
        trav(u, gr[1]) solve(1, u);
        vl f;
        trav(e, edges) {
            f.pb(m[{e.f, e.s}]*(n-m[{e.f, e.s}]));
            assert((m[{e.f,e.s}]*(n-m[{e.f, e.s}])));
        }
        FOR(i, 1, n) gr[i].clear();
        m.clear();
        assert(sz(f) == n-1);
        sort(f.begin(), f.end(), greater<ll>());
        int M; cin >> M;
        ll p[M]; F0R(i, M) cin >> p[i];
        sort(p, p+M, greater<ll>());
        ll facts[n-1];
        if (M < n-1) {
            F0R(i, M) facts[i] = p[i];
            FOR(i, M, n-2) facts[i] = 1;
        } else {
            facts[0] = 1;
            F0R(i, M-n+2) facts[0] = (facts[0] * p[i])%MOD;
            FOR(i, M-n+2, M-1) facts[i-(M-n+2)+1] = p[i];
        }
        ll ans = 0;
        F0R(i, n-1) {
            ll t = (f[i]*facts[i])%MOD;
            ans = (ans+t)%MOD;
        }
        cout << ans << nl;
    }
    
    return 0;
}
