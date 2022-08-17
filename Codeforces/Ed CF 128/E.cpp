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
#include <climits>

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

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string g[2]; F0R(i, 2) cin >> g[i];
        int ans = 0;
        int l = n, r = 0;
        vi v;
        F0R(i, n) {
            if (g[0][i] == '*' || g[1][i] == '*') {
                ckmin(l, i);
                ckmax(r, i);
                v.pb(2*(g[1][i] == '*')+(g[0][i] == '*'));
            }
        }
        ans = r-l;
        // now dp time
        int m = sz(v);
        int dp[m+1][2]; dp[0][0] = dp[0][1] = 0;
        F0R(i, m) {
            F0R(j, 2) dp[i+1][j] = INF;
            F0R(j, 2) {
                if (v[i]==3) {
                    ckmin(dp[i+1][j], dp[i][j]+1);
                    ckmin(dp[i+1][1-j], dp[i][j]+1);
                } else if (v[i]==1 && j==0) {
                    ckmin(dp[i+1][j], dp[i][j]);
                    ckmin(dp[i+1][1-j], dp[i][j]+1);
                } else if (v[i]==1 && j==1) {
                    ckmin(dp[i+1][j], dp[i][j]+1);
                    ckmin(dp[i+1][1-j], dp[i][j]+1);
                } else if (v[i]==2 && j==0) {
                    ckmin(dp[i+1][j], dp[i][j]+1);
                    ckmin(dp[i+1][1-j], dp[i][j]+1);
                } else if (v[i]==2 && j==1) {
                    ckmin(dp[i+1][j], dp[i][j]);
                    ckmin(dp[i+1][1-j], dp[i][j]+1);
                }
            }
        }
        ans += min(dp[m][0], dp[m][1]);
        cout << ans << nl;
    }
    return 0;
}
