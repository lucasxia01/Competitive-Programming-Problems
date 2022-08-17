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
const int INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;
int dp[2][4][4][4][4]; // 0 is nothing, 1 is meat, 2 is fish, 3 is bread
int a[MX];
int freq[4];
int n;
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> s;
    assert(n <= MX);
    F0R(i, n) {
        if (s[i] == 'M') a[i] = 1;
        else if (s[i] == 'F') a[i] = 2;
        else a[i] = 3;
    }
    F0R(i, 2) F0R(j, 4) F0R(k, 4) F0R(l, 4) F0R(m, 4) dp[i][j][k][l][m] = -1;
    dp[0][0][0][0][0] = 0;
    F0R(i, n) {
        F0R(j, 4) F0R(k, 4) F0R(l, 4) F0R(m, 4) {
            if (dp[0][j][k][l][m] == -1) continue;
            // cur is a[i];
            assert(a[i] >= 1 && a[i] <= 4);
            memset(freq, 0, sizeof freq);
            freq[j]=1; freq[k]=1; freq[a[i]]=1;
            int count = freq[1]+freq[2]+freq[3];
            
            ckmax(dp[1][k][a[i]][l][m], dp[0][j][k][l][m]+count);
            memset(freq, 0, sizeof freq);
            freq[l]=1; freq[m]=1; freq[a[i]]=1;
            count = freq[1]+freq[2]+freq[3];
            ckmax(dp[1][j][k][m][a[i]], dp[0][j][k][l][m]+count);
        }
        swap(dp[0], dp[1]);
    }
    int ans = 0;
    F0R(j, 4) F0R(k, 4) F0R(l, 4) F0R(m, 4) ckmax(ans, dp[0][j][k][l][m]);
    cout << ans << nl;
    return 0;
}
