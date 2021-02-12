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

int n, m, k;
vpi gr[MX];
int used[10][10][MX];
vi f[10];
int ans = 0;

int c[10];
bool dj[10][10][10][10];
void solve(int i) {
    if (i == k+1) {
//        FOR(l, 1, k) cout << c[l] << " "; cout << nl;
        ans++;
        return;
    }
    F0R(j, i) {
        c[i] = j;
        bool ok = 1;
        FOR(l, 1, i) ok &= dj[i][j][l][c[l]];
        if (ok) solve(i+1);
    }
}

void preprocess() {
    FOR(i, 1, k) F0R(j, i) {
        F0R(l, sz(f[i])) {
            used[i][j][gr[f[i][l]][j].s]++;
        }
    }
    FOR(i, 1, k) F0R(j, i) FOR(ii, 1, k) F0R(jj, ii) {
        dj[i][j][ii][jj] = 1;
        FOR(l, 1, n) {
            if (i==ii && j==jj) {
                if (used[i][j][l] > 1) {
                    dj[i][j][ii][jj] = 0; break;
                }
            } else if (used[i][j][l]+used[ii][jj][l] > 1) {
                dj[i][j][ii][jj] = 0; break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    int u, v, w;
    F0R(i, m) {
        cin >> u >> v >> w;
        gr[u].pb({w, v});
    }
    FOR(i, 1, n) {
        f[sz(gr[i])].pb(i);
        sort(gr[i].begin(), gr[i].end());
    }
    preprocess();
    solve(1);
    cout << ans << nl;
    return 0;
}
