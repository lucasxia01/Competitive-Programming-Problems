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
#include <iomanip>
#include <ctime>

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

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    string s; getline(cin, s);
    while (t--) {
        ll M, Z, R; cin >> M >> Z >> R;
        string m = to_string(M-1);
        string z = to_string(Z);
        int cnt = (int)m.length()-(int)z.length();
        int sz = (int)m.length();
        F0R(i, cnt) z = "0"+z;
        ll dp[sz+1][10][R][2]; // cur digit index, cur digit, cur run of matches, whether it matches M-1 so far
        F0R(i, sz+1) F0R(j, 10) F0R(k, R) F0R(l, 2) dp[i][j][k][l] = 0;
        dp[sz][0][0][1] = 1;
        F0Rd(i, sz) {
            F0R(d, 10) {
                F0R(r, R) {
                    F0R(l, 2) {
//                        dbg(i+1, d, r, 1, dp[i+1][d][r][l]);
                        if (!dp[i+1][d][r][l]) continue;
                        // match z[i]
                        if (r < R-1) {
                            if (l == 1) {
                                if (z[sz-1-i]-'0' > m[sz-1-i]-'0');
                                else if (z[sz-1-i]-'0' == m[sz-1-i]-'0')
                                    dp[i][z[sz-1-i]-'0'][r+1][1] += dp[i+1][d][r][l];
                                else
                                    dp[i][z[sz-1-i]-'0'][r+1][0] += dp[i+1][d][r][l];
                            } else {
                                dp[i][z[sz-1-i]-'0'][r+1][0] += dp[i+1][d][r][l];
                            }
                        }
                        // don't match z[i] and still be under m
                        F0R(dd, 10) {
                            if (dd == z[sz-1-i]-'0') continue;
                            if (l == 1) {
                                if (dd > m[sz-1-i]-'0');
                                else if (dd == m[sz-1-i]-'0') dp[i][dd][0][1] += dp[i+1][d][r][l];
                                else dp[i][dd][0][0] += dp[i+1][d][r][l];
                            } else dp[i][dd][0][0] += dp[i+1][d][r][l];
                        }
                    }
                }
            }
//            dbg();
        }
        ll ans = 0;
        F0R(d, 10) F0R(r, R) F0R(l, 2) {
//            dbg(0, d, r, l, dp[0][d][r][l]);
            ans += dp[0][d][r][l];
        }
        cout << M-ans << nl;
    }
    
    return 0;
}
