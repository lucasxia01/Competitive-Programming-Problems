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

const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}
const int MX = 1e5+5;
const int sqrtMX = 1e3;
vi edges[MX];
int level[MX];
vi levelCount[sqrtMX];
bool marked[MX];
int n, sqrtn;
bool foundCycle = 0;

// this one searches for the cycle
int dfs(int v, int l = 0) {
    marked[v] = 1;
    level[v] = l;
    levelCount[l%(sqrtn-1)].pb(v);
    trav(u, edges[v]) {
        if (!marked[u]) {
            int ret = dfs(u, l+1);
            if (ret) cout << v << " ";
            if (ret == v) return 0;
            else if (ret) return ret;
            else if (foundCycle) return 0;
        }
        else {
            if (l-level[u]+1 >= sqrtn) {
                foundCycle = 1;
                cout << 2 << '\n' << l-level[u]+1 << '\n';
                cout << v << " ";
                return u;
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int m, u, v;
    cin >> n >> m;
    F0R(i, n) if (i*i >= n) {
        sqrtn = i; break;
    }
    F0R(i, m) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    dfs(1);
    if (foundCycle) return 0;
    // from now on, we know no backedge goes >=sqrtn-1 levels up, so we can pick the independent set by jumping by sqrtn-1
    // the ind set could start the root or from its children
    cout << 1 << endl;
    F0R(i, sqrtn-1) {
        if (sz(levelCount[i]) < sqrtn) continue;
        F0R(j, sqrtn) cout << levelCount[i][j] << " ";
        break;
    } cout << endl;
    return 0;
}
