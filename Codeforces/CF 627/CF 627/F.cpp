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
const int MX = (int)2e5+5;
vi edges[MX];
int a[MX], dp[MX], ans[MX];

void dfs1(int p, int v) {
    dp[v] = -1;
    if (a[v]) dp[v] = 1;
    trav(a, edges[v]) {
        if (a != p) {
            dfs1(v, a);
            dp[v] += max(dp[a], 0);
        }
    }
}

void dfs2(int p, int v, int pd) {
    ans[v] = dp[v] + pd;
    trav(a, edges[v]) {
        if (a != p) dfs2(v, a, max(ans[v]-max(dp[a], 0), 0));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, u=0, v=0;
    cin >> n;
    F0R(i, n) cin >> a[i+1];
    F0R(i, n-1) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    dfs1(0, 1);
    dfs2(0, 1, 0);
    F0R(i, n) {
        cout << ans[i+1] << " ";
    }
    cout << endl;
    
    return 0;
}
