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
vi e[MX];

int dfs(int v, int p=0) {
    int len = 2;
    trav(u, e[v]) {
        if (u != p) {
            int ret = dfs(u, v);
            if (ret == -1) return -1;
            if (len == 2) len = ret%2;
            else if (len != ret%2) return -1;
        }
    }
    return (len+1)%2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, u, v;
    cin >> n;
    int notLeaf = 0;
    F0R(i, n-1) {
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
        if (sz(e[u]) > 1) notLeaf = u;
    }
    // min is either 1 or 3
    if (dfs(notLeaf) != -1) cout << 1 << " ";
    else cout << 3 << " ";
    int f[n+1];
    memset(f, 0, 4*n+4);
    F0R(i, n) {
        if (sz(e[i+1]) == 1) f[e[i+1][0]]++;
    }
    int c = 0;
    F0R(i, n) c += max(0, f[i+1]-1);
    cout << n-1-c << '\n';
    return 0;
}
