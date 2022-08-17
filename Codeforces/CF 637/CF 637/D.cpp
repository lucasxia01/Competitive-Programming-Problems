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
vi edges[MX];
vpi ans;
int T;

void dfs(int v, int p, int t, int endTime) {
    
    int curT = t;
    int childrenLeft = sz(edges[v])-1;
    trav(u, edges[v]) {
        if (u == p) continue;
        ans.pb({v, curT++});
        if (curT == T+1) {
            // reset curT
            curT = endTime-childrenLeft;
            ans.pb({v, curT++});
        }
        dfs(u, v, curT, curT-1);
        childrenLeft--;
    }
    ans.pb({v, curT});
    if (curT != endTime) {
        curT = endTime;
        ans.pb({v, curT});
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, u, v;
    cin >> n;
    F0R(i, n-1) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    F0R(i, n) ckmax(T, sz(edges[i+1]));
    dfs(1, 0, 0, sz(edges[1]));
    cout << sz(ans) << nl;
    trav(a, ans) cout << a.f << " " << a.s << nl;
    return 0;
}
