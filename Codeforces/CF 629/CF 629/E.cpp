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

const int MX = 2e5+5;
const int LOGMX = 20;
int ti[MX], to[MX];
int par[MX];
vi edges[MX];
int l[MX];
int n, m, k, t = 0;

void dfs(int s, int p, int level) { // gets the levels and the times
    l[s] = level;
    ti[s] = t++;
    trav(a, edges[s]) {
        if (a != p) {
            par[a] = s;
            dfs(a, s, level+1);
        }
    }
    to[s] = t;
}
void preprocess() {
    par[1] = 0;
    ti[0] = -1; to[0] = MX;
    dfs(1, 0, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int u, w;
    F0R(i, n-1) {
        cin >> u >> w; // 1 indexed
        edges[u].pb(w);
        edges[w].pb(u);
    }
    preprocess();
    F0R(i, m) {
        cin >> k;
        int v[k];
        vpi heights;
        F0R(j, k) {
            cin >> v[j];
            v[j] = par[v[j]]; // convert everything to parents for MAGIC
            heights.pb(mp(l[v[j]], v[j]));
        }
        sort(heights.begin(), heights.end(), greater<pi>()); // sort by level
        bool ok = true;
        F0R(j, k-1) {
            u = heights[j+1].s;
            w = heights[j].s;
            // want to check if ancestor
            if (!(ti[u] <= ti[w] && to[w] <= to[u])) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "YES" : "NO") << endl;
    }
    return 0;
}
