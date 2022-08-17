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
const int MX = 2e5+5;
bool ok[MX];
vi edges[MX];
vi redges[MX];
bool vis1[MX], vis2[MX];
void dfs1(int v) {
    trav(u, edges[v]) {
        if (!vis1[u]) {
            vis1[u] = 1;
            dfs1(u);
        }
    }
}
void dfs2(int v) {
    trav(u, redges[v]) {
        if (!vis2[u]) {
            vis2[u] = 1;
            dfs2(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    
    int j, k;
    queue<int> zeros;
    int inCount[n+1]; F0R(i, n+1) inCount[i] = 0;
    F0R(i, n+1) ok[i] = 1;
    F0R(i, m) {
        cin >> j >> k;
        inCount[k]++;
        edges[j].pb(k);
        redges[k].pb(j);
    }
    FOR(i, 1, n) if (!inCount[i]) zeros.push(i);
    //top sort
    int c = 0;
    while (!zeros.empty()) {
        int v = zeros.front(); zeros.pop();
        c++;
        trav(u, edges[v]) {
            inCount[u]--;
            if (!inCount[u]) zeros.push(u);
        }
    }
    if (c != n) {
        cout << -1 << nl;
        return 0;
    }
    int ans = 0;
    string str = "";
    FOR(i, 1, n) {
        if(!vis1[i] && !vis2[i])ans++, str += 'A';
        else str += 'E';
        dfs1(i);
        dfs2(i);
    }
    assert(ans);
    cout << ans << nl << str << nl;
    return 0;
}
