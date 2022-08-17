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
const int MOD = 9901; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 301;
const int INV_2 = (MOD+1)/2;
int fac[MX];
vpi edges;
int n, k;
int par[MX], sze[MX];
int find(int i) {
    return (i==par[i] ? i : par[i]=find(par[i]));
}
void merge(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sze[a] >= sze[b]) {
        par[b] = a;
        sze[a] += sze[b];
    } else {
        par[a] = b;
        sze[b] += sze[a];
    }
}

int calc(int bitmask) {
    if (bitmask == 0) return fac[n-1];
    int deg[MX] = {};
    F0R(i, MX) par[i] = i;
    F0R(i, MX) sze[i] = 1;
    int count = 0;
    bool formedCycle = 0;
    F0R(i, sz(edges)) {
        if (bitmask&(1<<i)) {
            count++;
            deg[edges[i].f]++;
            deg[edges[i].s]++;
            if (find(edges[i].f) == find(edges[i].s)) formedCycle = 1;
            merge(edges[i].f, edges[i].s);
        }
    }
    int comps = 0, diff = 0;
    FOR(i, 1, n) {
        if (!deg[i]) continue;
        diff++;
        if (deg[i] > 2) return 0;
        if (par[i] == i) comps++;
    }
    assert(formedCycle == !(diff-count == comps));
    if (formedCycle) {
        bool ok = 1;
        FOR(i, 1, n) if (find(i) != find(1)) {
            ok = 0; // if one component its fine
            break;
        }
        if (ok) return ((count&1)?MOD-1:1)*2%MOD;
        else return 0;
    }
    assert(count < n && comps && comps <= k);
    return (((count&1)?MOD-1:1) * (((1<<comps)%MOD * fac[n-1-count])%MOD))%MOD;
}

int bash(int tt) {
    int adj[MX][MX]; F0R(i, MX) F0R(j, MX) adj[i][j] = 0;
    trav(a, edges) {
        adj[a.f][a.s] = 1;
        adj[a.s][a.f] = 1;
    }
    int a[n]; F0R(i, n) a[i] = i+1;
    int ans = 0;
    do {
        bool ok = 1;
        F0R(i, n) if (adj[a[i]][a[(i+1)%n]]) {
            ok = false;
            break;
        }
        if (ok) ans = (ans + 1)%MOD;
    } while (next_permutation(a+1, a+n));
    return (ans*INV_2)%MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    fac[0] = 1;
    FOR(i, 1, MX-1) fac[i] = (fac[i-1]*i)%MOD;
    F0R(tt, t) {
        int u, v;
        cin >> n >> k;
        edges.clear();
        F0R(i, k) {
            cin >> u >> v;
            edges.pb({u, v});
        }
        int ans = 0;
        F0R(i, 1<<k) ans = (ans + calc(i))%MOD;
        cout << "Case #" << tt+1 << ": " << (ans*INV_2)%MOD << nl;
    }
}
