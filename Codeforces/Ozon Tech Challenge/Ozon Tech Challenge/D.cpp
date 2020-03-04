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
const int MX = 1<<20;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a < b ? 0 : 1, a=b;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return a > b ? 0 : 1, a=b;
}

vi edges[1011];
bool valid[1011];

void dfs(int i) {
    valid[i] = false;
    //cout << i << endl;
    trav(a, edges[i]) {
        if (valid[a]) {
            dfs(a);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, u, v;
    cin >> n;
    FOR(i, 1, n) valid[i] = true;
    F0R(i, n-1) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    int sz, res;
    while (1) {
        
        FOR(i, 1, n) {
            vi new_edges;
            trav(a, edges[i]) if (valid[a]) new_edges.pb(a);
            if (valid[i] && (sz = (int)new_edges.size()) > 1) {
                u = new_edges[0]; v = new_edges[1];
                cout << "? " << u << " " << v << endl;
                fflush(stdout);
                cin >> res;
                valid[res] = false;
                if (res == i) {
                    dfs(u);
                    dfs(v);
                } else if (res == u) {
                    
                    dfs(i);
                    dfs(v);
                } else {
                    dfs(i);
                    dfs(u);
                }
                valid[res] = true;
                break;
            }
        }
        int num = 0;
        F0R(i, n) {
            if (valid[i+1]) {
                num++;
            }
        }
        if (num < 2) {
            F0R(i, n) {
                if (valid[i+1]) {
                    cout << "! " << i+1 << endl;
                    return 0;
                }
            }
        } else if (num == 2) {
            cout << "?";
            F0R(i, n) {
                if (valid[i+1]) {
                    cout << " " << i+1;
                }
            } cout << endl;
            fflush(stdout);
            cin >> res;
            cout << "! " << res << endl;
            return 0;
        }
    }
    return 0;
}
