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

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

bool visited[5011], curBranch[5011];
int mat[5011][5011], color[5011][5011];

bool isCycle(int v) {
    if (curBranch[v]) return true;
    if (visited[v]) return false;
    curBranch[v] = true;
    visited[v] = true;
    bool ans = false;
    F0R(i, 5011) {
        if (mat[v][i] && curBranch[i]) {
            color[v][i] = 2;
            ans = true;
        } else if (mat[v][i]) {
            color[v][i] = 1;
            ans = ans | isCycle(i);
        }
    }
    curBranch[v] = false;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    int a, b;
    vpi edges;
    F0R(i, m) {
        cin >> a >> b;
        mat[a][b] = 1;
        edges.pb(mp(a, b));
    }
    bool existsCycle = false;
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;
        if (isCycle(i)) existsCycle = true;
    }
    if (existsCycle) cout << 2 << endl;
    else cout << 1 << endl;
    F0R(i, m) cout << color[edges[i].f][edges[i].s] << " ";
    cout << endl;
    return 0;
}
