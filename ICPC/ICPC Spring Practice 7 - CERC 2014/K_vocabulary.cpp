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

const int MX = 1<<20;

ll modAdd(ll a, ll b) {
    return ((a + b)%MOD + MOD)%MOD;
}

ll cntBelow(char a) {
    assert(a != '?');
    if (a == '0') return 0;
    return (a-'a');
}

ll cntAbove(char a) {
    assert(a != '?');
    if (a == '0') return 26;
    return ('z'-a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        string s[3]; F0R(i, 3) cin >> s[i];
        int len = max(s[0].length(), max(s[1].length(), s[2].length()));
        F0R(i, 3) {
            int l = s[i].length();
            F0R(j, len-l) s[i] += ('0');
        }
        ll dp[4][len+1];
        F0R(i, len+1) F0R(j, 4) dp[j][i] = 0;
        F0R(j, 4) dp[j][len] = 1;
        F0Rd(i, len) {
            vl num;
            if (s[0][i] == '?' && s[1][i] == '?' && s[2][i] == '?') {
                num = {26, 26*25/2, 26*25/2, 26*25*24/3};
            } else if (s[0][i] == '?' && s[1][i] != '?' && s[2][i] == '?') {
                num = {1, cntAbove(s[1][i]), cntBelow(s[1][i]), cntAbove(s[1][i])*cntBelow(s[1][i])};
            } else if (s[0][i] != '?' && s[1][i] == '?' && s[2][i] == '?') {
                num = {1, cntAbove(s[1][i]), cntAbove(s[1][i]), cntAbove(s[1][i])*(cntAbove(s[1][i])-1)/2};
            } else if (s[0][i] != '?' && s[1][i] != '?' && s[2][i] == '?') {
                num = {s[0][i] == s[1][i], (s[0][i] == s[1][i]) * cntAbove(s[0][i]), (s[0][i] < s[1][i]), (s[0][i] < s[1][i]) * cntAbove(s[1][i])};
            } else if (s[0][i] == '?' && s[1][i] == '?' && s[2][i] != '?') {
                num = {1, cntBelow(s[2][i]), cntBelow(s[2][i]), cntBelow(s[2][i])*(cntBelow(s[2][i])-1)/2};
            } else if (s[0][i] == '?' && s[1][i] != '?' && s[2][i] != '?') {
                num = {s[0][i] == s[1][i], (s[1][i] < s[2][i]), (s[1][i] == s[2][i]) * cntBelow(s[1][i]), (s[1][i] < s[2][i]) * cntBelow(s[1][i])};
            } else if (s[0][i] != '?' && s[1][i] == '?' && s[2][i] != '?') {
                num = {s[0][i] == s[2][i], (s[0][i] < s[2][i]), (s[0][i] < s[2][i]), max(0, (s[2][i] - s[0][i]-1))};
            } else if (s[0][i] != '?' && s[1][i] != '?' && s[2][i] != '?') {
                num = {(s[0][i] == s[1][i] && s[1][i] == s[2][i]), }
            } 
            dp[0][i] = modAdd(dp[0][i], (num[0]*dp[0][i+1])%MOD);
            dp[0][i] = modAdd(dp[0][i], (num[1]*dp[1][i+1])%MOD);
            dp[0][i] = modAdd(dp[0][i], (num[2]*dp[2][i+1])%MOD);
            dp[0][i] = modAdd(dp[0][i], (num[3]*dp[3][i+1])%MOD);
            // dp[1]

        }
    }
    return 0;
}
