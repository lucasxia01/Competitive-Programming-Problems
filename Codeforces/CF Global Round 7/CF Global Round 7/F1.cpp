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

const int MX = 14;
const int eMX = 1<<MX;
int len[eMX];
vl dp[eMX][MX]; // state is subset of men used so far, last man used, current string
char m[MX][MX];
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    F0R(i, n) F0R(j, n) cin >> m[i][j];
    vpi order;
    F0R(i, 1<<n) {
        int c = 0, mark = -1;
        F0R(j, n) {
            if (i&(1<<j)) {
                c++;
                mark = j;
            }
        }
        len[i] = c;
        F0R(j, n) F0R(k, 1<<(len[i]-1)) dp[i][j].pb(0);
        if (len[i] == 1) F0R(j, n) dp[i][mark][0] = 1;
        order.pb(mp(c, i));
    }
    sort(order.begin(), order.end()); // order stores a pair of length, set of used men
    
    trav(a, order) { // the order must be in order of size of set of used men
        if (a.f == 0) continue;
        F0R(j, n) {
            F0R(k, 1<<(a.f-1)) {
                F0R(l, n) {
                    if (!(a.s&(1<<l))) dp[a.s|(1<<l)][l][(k<<1)+(m[j][l]-'0')] += dp[a.s][j][k]; // for current state, add it to everything it goes to
                    // if the set of used men don't have the cur man, use the connection with him and the last used man, also update the current string
                }
            }
        }
    }
    F0R(i, 1<<(n-1)) {
        ll ans = 0;
        F0R(j, n) ans += dp[(1<<n)-1][j][i];
        cout << ans << " ";
    } cout << endl;
    
    return 0;
}
