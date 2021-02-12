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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e6;
int pref[9][9][2];
int n, m;
int isNotPrime[MX];
int ans = 0;

void solve(int pos) {
    int x = pos/m, y = pos%m;
//    F0R(i, 1) F0R(j, 2) cout << pref[i+1][j+1][1] << " "; cout << nl << nl;
//    cout << x << ' ' << y << nl;
    if (x == n) {
        ans++;
        return;
    }
    int moves[5] = {1, 3, 5, 7, 9};
    if (pos == 0) {
        pref[x+1][y+1][0] = 10*pref[x][y+1][0]+2;
        pref[x+1][y+1][1] = 10*pref[x+1][y][1]+2;
        if (isNotPrime[pref[x+1][y+1][0]] || isNotPrime[pref[x+1][y+1][1]]);
        else solve(pos+1);
    }
    F0R(i, 5) {
        pref[x+1][y+1][0] = 10*pref[x][y+1][0]+moves[i];
        pref[x+1][y+1][1] = 10*pref[x+1][y][1]+moves[i];
        if (isNotPrime[pref[x+1][y+1][0]] || isNotPrime[pref[x+1][y+1][1]]) continue;
        solve(pos+1);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    if ((n >= 4 && m >= 4) || (n >= 6 || m >= 6)) {
        cout << 0 << nl;
        return 0;
    }
    isNotPrime[1] = 1;
    FOR(i, 2, MX-1) {
        if (!isNotPrime[i]) {
            for (int j = 2*i; j < MX; j+=i) {
                isNotPrime[j] = 1;
            }
        }
    }
    solve(0);
    cout << ans << nl;
    return 0;
}
