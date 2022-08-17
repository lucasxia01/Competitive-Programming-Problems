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

const int MX = 51;

struct State {
    int h, s;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("princess.in", "r", stdin);
//    freopen("princess.out", "w", stdout);
    int n, h, s, p, m; cin >> n >> h >> s >> p >> m;
    int dp[n+1][h+1][n+1];
    F0R(i, n+1) F0R(j, h+1) F0R(k, n+1) dp[i][j][k] = -1;
    int sp = s+p;
    pair<State, char> par[n+1][h+1][n+1];
    dp[0][h][0] = m;
    F0R(i, n) {
        int S, P, M; cin >> S >> P >> M;
        F0R(j, h+1) F0R(k, n) {
            int kk = k+s;
            if (dp[i][j][k] < 0) continue;
//            cout << i << " " << j << " " << kk << " " << dp[i][j][k] << nl;
            int newH = j - max(2*S-kk, 0);
            if (kk >= S && newH > 0) {
                if (ckmax(dp[i+1][newH][k+1], dp[i][j][k]))
                    par[i+1][newH][k+1] = {{j, k}, 'D'};
            }
            if (sp+i-kk >= P && dp[i][j][k] >= M) {
                if (ckmax(dp[i+1][j][k], dp[i][j][k]-M))
                    par[i+1][j][k] = {{j, k}, 'E'};
            }
        }
    }
    F0R(j, h+1) F0R(k, n+1) {
        if (dp[n][j][k] >= 0) {
            string ans = "";
            State cur = {j, k};
            FORd(i, 1, n) {
                ans += par[i][cur.h][cur.s].s;
                cur = par[i][cur.h][cur.s].f;
            }
            reverse(ans.begin(), ans.end());
            cout << ans << nl;
            return 0;
        }
    }
    cout << "UNLUCKY" << nl;
    return 0;
}
