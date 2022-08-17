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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n;
    int mat[n][n];
    char x;
    F0R(i, n) F0R(j, n) {
        cin >> x;
        mat[i][j] = x - '0';
        if (mat[i][j] == 0) mat[i][j] = INF;
    }
    F0R(k, n) F0R(i, n) F0R(j, n) mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
    
    cin >> m;
    int p[m];
    F0R(i, m) cin >> p[i];
    int dp[m+1];
    int parent[m+1];
    F0R(i, m) dp[i] = i+1;
    F0R(i, m) parent[i] = i-1;
    F0R(i, m) {
        int maxJump = 0;
        FOR(j, 1, n) {
            if (i+j >= m || p[i] == p[i+j]) break;
            if (j == mat[p[i]-1][p[i+j]-1]) {
                maxJump = j;
            }
        }
        if (dp[i]+1 < dp[i+maxJump]) {
            dp[i+maxJump] = dp[i]+1;
            parent[i+maxJump] = i;
        }
    }
    cout << dp[m-1] << endl;
    int newPath[dp[m-1]];
    int cur = m-1;
    F0Rd(i, dp[m-1]) {
        newPath[i] = p[cur];
        cur = parent[cur];
    }
    F0R(i, dp[m-1]) {
        cout << newPath[i] << " ";
    } cout << endl;
    return 0;
}
