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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int h, w;
    cin >> h >> w;
    int r[h], c[w], grid[h][w];
    F0R(i, h) cin >> r[i];
    F0R(j, w) cin >> c[j];
    F0R(i, h) F0R(j, w) grid[i][j] = 2;
    F0R(i, h) {
        F0R(j, r[i]) grid[i][j] = 1;
        if (r[i] < w) grid[i][r[i]] = 0;
    }
    F0R(j, w) {
        F0R(i, c[j]) {
            if (grid[i][j] == 2)
                grid[i][j] = 1;
            else if (grid[i][j] == 0){
                cout << 0 << endl;
                return 0;
            }
        }
        if (c[j] < h) {
            if (grid[c[j]][j] == 2)
                grid[c[j]][j] = 0;
            else if (grid[c[j]][j] == 1){
                cout << 0 << endl;
                return 0;
            }
        }
    }
    ll ans = 1;
    F0R(i, h) F0R(j, w) if (grid[i][j] == 2) ans = (ans * 2)%MOD;
    cout << ans << endl;
    return 0;
}
