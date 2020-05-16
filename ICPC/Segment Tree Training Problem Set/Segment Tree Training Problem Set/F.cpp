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

const char nl = '\n';
const ll INF = (1LL<<50) + 123;
const ll LLINF = (1LL<<50) + 777;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

const int MX = 2e5+5;
int n;
int bit[MX];
void upd(int p, int v) {
    while (p <= n) {
        // cout << p << " " << v << nl;
        bit[p] += v;
        p += p&-p;
    }
}

int query(int p) {
    int ans = 0;
    while (p > 0) {
        ans += bit[p];
        p -= p&-p;
    }
    return ans;
}

vi edges[MX];
int ti[MX], to[MX], l[MX];
int t = 0;

void dfs(int v = 1, int p = 0) {
    ti[v] = ++t;
    l[v] = l[p]+1;
    trav(u, edges[v]) if (u != p) dfs(u, v);
    to[v] = t+1;
}
int main() {
    int q, u, v;
    cin >> n >> q;
    int a[n+1], b[n+1]; b[0] = 0;
    F0R(i, n) cin >> a[i+1];
    F0R(i, n-1) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    dfs(); // here we get the order for contiguous segments
    FOR(i, 1, n) if (!(l[i]&1)) a[i] = -a[i]; // odd levels are positive
    FOR(i, 1, n) b[ti[i]] = a[i];
    FOR(i, 1, n) a[i] = b[i] - b[i-1]; // we make the array of differences between elements in the order
    FOR(i, 1, n) upd(i, a[i]); // the fenwick tree will store  prefix sums of the element differences, so the prefix sums will be the actual value
    // the idea here is that we can do range modifications, but only element queries
    int op, x;
    while (q--) {
        cin >> op;
        if (op == 1) {
            cin >> x >> v;
            if (!(l[x]&1)) v = -v;
            upd(ti[x], v);
            upd(to[x], -v);
        }
        else {
            cin >> x;
            int ret = query(ti[x]);
            cout << ((l[x]&1) ? ret : -ret) << nl;
        }
    }
    return 0;
}
