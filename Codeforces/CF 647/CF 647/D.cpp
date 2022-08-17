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

const int MX = 1<<20;

vi c[MX];
int a[MX], vis[MX], ptrs[MX];
vi tour;
int p;
void dfs(int v=0) {
    vis[v] = 1;
    vis[v^1] = 1;
    int curBin = a[v^1]%p;
    while (ptrs[curBin] < sz(c[curBin])) {
        int u = c[curBin][ptrs[curBin]++];
        if (vis[u]) continue;
        dfs(u);
    }
    tour.pb(v^1); tour.pb(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    F0R(i, 2*n) cin >> a[i];
    FORd(ans, 0, 20) { // CHANGE TO 20
        p = 1<<ans;
        tour.clear();
        F0R(i, p) c[i].clear();
        F0R(i, 2*n) c[a[i]%p].pb(i);
        F0R(i, 2*n) vis[i] = 0;
        F0R(i, p) ptrs[i] = 0;
        bool ok = 1;
        F0R(i, p) if (sz(c[i])%2) {ok = 0; break;}
        if (ok) dfs();
        if (!ok || sz(tour) != 2*n) continue;
        else {
            cout << ans << nl;
            trav(v, tour) cout << v+1 << " "; cout << nl;
            return 0;
        }
    }
    assert(0);
    return 0;
}
