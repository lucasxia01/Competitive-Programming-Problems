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
#include <random>
#include <chrono>
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

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 2e5+5;

struct State {
    int year = -1;
    int r;
    int c;
    vi idx;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("dvd.in", "r", stdin);
//    freopen("dvd.out", "w", stdout);
    int n; cin >> n;
    int nYears = 2005-1870;
    vi d[nYears][5];
    string f[n];
    string s; int year, r;
    getline(cin, s);
    F0R(i, n) {
        getline(cin, s);
        f[i] = s.substr(0, s.rfind("\"")+1);
        s = s.substr(s.rfind("\"")+2);
        year = stoi(s.substr(0, s.find(" ")));
        r = stoi(s.substr(s.find(" ")+1));
        year -= 1870; r--;
        d[year][r].pb(i);
    }
    int dp[nYears+1][5][6]; // year and current region and number of switches used
    State par[nYears+1][5][6];
    F0R(i, nYears) F0R(j, 5) F0R(c, 6) dp[i+1][j][c] = -INF;
    F0R(j, 5) F0R(c, 6) dp[0][j][c] = 0;
    FOR(i, 1, nYears) {
        F0R(c, 6) { // number of changes
            F0R(j, 5) { // j is cur region
                int sum = sz(d[i-1][j]);
                dp[i][j][c] = dp[i-1][j][c]+sum;
                par[i][j][c] = {i-1, j, c, {j}};
                if (c == 0) continue;
                F0R(k, 5) { // k is prev region
                    if (j == k) continue;
                    sum = sz(d[i-1][j])+sz(d[i-1][k]);
                    if (ckmax(dp[i][j][c], dp[i-1][k][c-1]+sum))
                        par[i][j][c] = {i-1, k, c-1, {j, k}};
                    vpi otherRegions;
                    vi idx = {j};
                    F0R(l, 5) if (l != j && l != k) otherRegions.pb({sz(d[i-1][l]), l});
                    sort(otherRegions.begin(), otherRegions.end(), greater<pi>());
                    F0R(o, 3) {
                        if (c < o+2) break;
                        sum += otherRegions[o].f;
                        idx.pb(otherRegions[o].s);
                        idx.pb(k);
                        if (ckmax(dp[i][j][c], dp[i-1][k][c-2-o]+sum))
                            par[i][j][c] = {i-1, k, c-2-o, idx};
                        idx.pop_back();
                    }
                }
            }
        }
    }
    int ans = 0;
    State cur;
    F0R(j, 5) if (ckmax(ans, dp[nYears][j][5])) cur = par[nYears][j][5];
    cout << ans << nl;
    vi order;
    while (cur.year != -1) {
        F0R(i, sz(cur.idx)) trav(a, d[cur.year][cur.idx[i]]) {
//            cout << cur.year+1870 << " " << cur.idx[i]+1 << " " << cur.c << " " << a << " " << f[a] << nl;
            order.pb(a);
        }
        cur = par[cur.year][cur.r][cur.c];
    }
    reverse(order.begin(), order.end());
    trav(a, order) cout << f[a] << nl;
    assert(sz(order) == ans);
    return 0;
}
