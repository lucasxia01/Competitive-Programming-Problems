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

const int MX = 2e5+11;
int time_in[MX], time_out[MX];
int l[MX], p[MX];
vi edges[MX];
int n, m, k, t = 0;

void dfs(int v = 1, int par = 0, int level = 0) { // gets the levels and the times
    l[v] = level;
    time_in[v] = t++;
    trav(a, edges[v]) {
        if (a != par) {
            p[a] = v;
            dfs(a, v, level+1);
        }
    }
    time_out[v] = t;
}
void preprocess() {
    p[1] = 0;
    time_in[0] = -1; time_out[0] = MX;
    dfs();
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
        vpi h;
        F0R(j, k) {
            cin >> v[j];
            v[j] = p[v[j]]; // convert everything to parents for MAGIC
            h.pb(mp(l[v[j]], v[j]));
        }
        sort(h.begin(), h.end(), greater<pi>()); // sort by level
        bool f = true;
        F0R(j, k-1) {
            u = h[j+1].s;
            w = h[j].s;
            if (time_in[u] > time_in[w] || time_out[w] > time_out[u]) {
                f = false;
                break;
            }
        }
        cout << (f ? "YES" : "NO") << endl;
    }
    return 0;
}
