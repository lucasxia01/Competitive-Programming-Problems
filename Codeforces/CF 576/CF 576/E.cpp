#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>

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
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const char nl = '\n';
const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m, u, v;
        cin >> n >> m;
        // idea is that greedily find a matching, if its good enough, use it
        // if not, then the remaining vertices all don't have edges between them, so
        // they form an independent set
        vpi edges;
        F0R(i, m) {
            cin >> u >> v;
            edges.pb({u, v});
        }
        int vis[3*n+1];
        memset(vis, 0, sizeof vis);
        vi matching;
        F0R(i, m) {
            if (!vis[edges[i].f]&& !vis[edges[i].s]) {
                matching.pb(i+1);
                vis[edges[i].f]=vis[edges[i].s]=1;
            }
        }
        if (sz(matching) >= n) {
            cout << "Matching" << nl;
            F0R(i, n) cout << matching[i] << " "; cout << nl;
        } else {
            cout << "IndSet" << nl;
            int c = 0;
            FOR(i, 1, 3*n) {
                if (c == n) break;
                if (!vis[i]) cout << i << " ", c++;
            } cout << nl;
        }
    }
    return 0;
}
