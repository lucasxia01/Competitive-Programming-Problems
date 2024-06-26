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

const int MX = 1e5 + 5;
vi edges[MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, u, v;
    cin >> n;
    vpi e;
    int ans[n-1];
    F0R(i, n-1) ans[i] = -1;
    F0R(i, n-1) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
        e.pb(mp(u, v));
    }
    bool good = false;
    FOR(i, 1, n) {
        if (edges[i].size() >= 3) {
            F0R(j, 3) {
                F0R(k, e.size()) {
                    if ((i == e[k].f && edges[i][j] == e[k].s) || (i == e[k].s && edges[i][j] == e[k].f)) {
                        ans[k] = j;
                    }
                }
            }
            good = true;
            break;
        }
    }
    if (good) {
        int count = n-2;
        F0R(i, n-1) {
            if (ans[i] == -1) {
                ans[i] = count;
                count--;
            }
            cout << ans[i] << endl;
        }
    } else {
        F0R(i, n-1) cout << i << endl;
    }
    
    return 0;
}
