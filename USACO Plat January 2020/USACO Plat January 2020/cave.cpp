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
int mat[1000][1000];
string a[1000];
int n, m;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
void dfs(int x, int y, int v) {
    if (x < 0 || x >= n || y < 0 || y >= m || a[x][y] == '#' || mat[x][y]) return;
    //cout << x << " " << y << " " << v << endl;
    mat[x][y] = v;
    F0R(i, 4) {
        dfs(x + dx[i], y + dy[i], v);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    freopen("cave.in", "r", stdin);
    freopen("cave.out", "w", stdout);
    cin >> n >> m;
    //cout << n << endl;
    int numComps = 0;
    F0R(i, n) cin >> a[i];
    //cout << m << endl;
    F0R(i, n) {
        F0R(j, m) {
            //cout << numComps << endl;
            if (mat[i][j] == 0 && a[i][j] == '.') {
                numComps++;
                dfs(i, j, numComps);
            }
        }
    }
//    F0R(i, n) {
//        F0R(j, m) cout << mat[i][j];
//        cout << endl;
//    }
    
    int state[m];
    F0R(i, m) state[i] = 0;
    int stateMap[n*m];
    F0R(i, n*m) stateMap[i] = i;
    int numStates = 1;
    ll powersOf2[n*m];
    ll pow = 1;
    F0R(i, n*m) {
        powersOf2[i] = pow;
        pow = (pow * 2) % MOD;
    }
    ll ans[numComps+1];
    F0R(i, numComps+1) ans[i] = 0;
    unordered_set<int> count[numComps+1];
    unordered_set<int> modComps;
    cout << "does it get here" << endl;
    FORd(i, 1, n-2) {
        F0R(j, m) {
            if (a[i][j] == '#') state[j] = 0;
            else  {
                if (state[j-1]) {
                    if (state[j]) stateMap[state[j]] = stateMap[state[j-1]];
                    state[j] = stateMap[state[j-1]];
                } else if (state[j]) {
                    state[j] = stateMap[state[j]];
                } else {
                    stateMap[numStates] = numStates;
                    state[j] = stateMap[numStates];
                    numStates++;
                }
            }
        }
        F0R(j, m) {
            if (state[j]) {
                count[mat[i][j]].insert(state[j]);
                modComps.insert(mat[i][j]);
            }
            //cout << state[j];
        } //cout << endl;
        trav(a, modComps) {
            ans[a] = (ans[a] + powersOf2[count[a].size()]-1) % MOD;
            //cout << a << " " << count[a].size() << endl;
            count[a].clear();
        }
        modComps.clear();
    }
    ll totalAns = 1;
    FOR(i, 1, numComps) {
        totalAns = (totalAns * (ans[i]+1)) % MOD;
    }
    cout << totalAns << endl;
    return 0;
}
