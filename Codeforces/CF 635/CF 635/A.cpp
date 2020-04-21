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

const int MX = 2e5+5;
int n, k, u, v, t;
vi e[MX];
int nC[MX];
vi a;

void dfs(int v=1, int p=0, int l=0) {
    nC[v] = -t-l;
    t++;
    trav(u, e[v]) {
        if (u != p) {
            dfs(u, v, l+1);
        }
    }
    nC[v] += t;
    a.pb(nC[v]-1);
    // cout << v << " " << nC[v]-1 << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> k;
    F0R(i, n-1) {
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs();
    sort(a.begin(), a.end(), greater<int>());
    ll ans = 0;
    F0R(i, n-k) {
        ans += a[i];
    }
    cout << ans << endl;
    return 0;
}
