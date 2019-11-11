#include <iostream>
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

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()
int par[MAX_N];

int parent(int pos) {
    return pos == par[pos] ? pos : par[pos]=parent(par[pos]);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    ld mat[n][n];
    ll a[n][3];
    F0R(i, n) F0R(j, 3) cin >> a[i][j];
    F0R(i, n) F0R(j, n) {
        mat[i][j] = sqrt((a[i][0] - a[j][0])*(a[i][0] - a[j][0]) + (a[i][1] - a[j][1])*(a[i][1] - a[j][1])) - (a[i][2] + a[j][2]);
    }
    bool vis[n];
    ld cost[n];
    F0R(i, n) vis[i] = false;
    F0R(i, n) cost[i] = INF;
    int s = 0;
    ld ans = 0;
    F0R(i, n-1) {
        ld cur = INF, cur_idx = -1;
        vis[s] = true; cost[s] = 0;
        F0R(j, n) {
            if (!vis[j] && mat[s][j] < cost[j]) cost[j] = mat[s][j];
            if (!vis[j] && cost[j] < cur) {
                cur = cost[j];
                cur_idx = j;
            }
        }
        ans += cur;
        s = cur_idx;
    }
    cout << ans << endl;
    
    return 0;
}
