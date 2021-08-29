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

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 41;

int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    F0R(tt, t) {
        int n, q; cin >> n >> q;
        string ans = "";
        int u, v;
        if (n == 1) {
            string s; cin >> s;
            int m; cin >> m;
            if (m > q-m) {
                ans = s;
                u = m; v = 1;
            } else {
                F0R(i, q) ans += "TF"[s[i]=='T'];
                u = q-m; v = 1;
            }
        } else if (n == 2) {
            string s, t; int a, b; cin >> s >> a;

            int cnt = 0;
            pair<int, vi> dp[MX][MX][MX];
            F0R(i, q) F0R(j, q) F0R(k, q) dp[i][j][k] = {0, {}};
            dp[0][0][0] = {1, {}};
            F0R(i, q) {
                F0R(ii, a+1) {
                    F0R(jj, b+1) {
                        // first put T?
                        int c = dp[i][ii][jj].f;

                    }
                }
            }
            int g = gcd(total, cnt);
            total /= g; cnt /= g;
            u = total; v = cnt;
        } else return 0;
        
        cout << "Case #" << tt+1 << ": " << ans <<  " " << u << "/" << v << nl;
    }
    
    return 0;
}
