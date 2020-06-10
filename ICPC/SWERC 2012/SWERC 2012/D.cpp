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

const int MX = 1<<20;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    F0R(tt, T) {
        string s; cin >> s;
        int n = (int)s.length();
        vector<pair<char, int> > v;
        int cur = 0;
        string m = "AUCG";
        int base;
        F0R(i, n+1) {
            if (i == n || (s[i] >= 'A' && s[i] <= 'Z')) {
                if (i) v.pb({base, cur});
                base = (int)m.find(s[i]);
                cur = 0;
            } else cur = 10*cur + (s[i]-'0');
        }
        int k; cin >> k;
        int len = sz(v);
        if (len == 1) {
            cout << "Case " << tt+1 << ": " << 0 << nl;
            continue;
        }
        int edgepairs = 0;
        if (v[0].f == (v[len-1].f^1)) {
            edgepairs = min(v[0].s, v[len-1].s);
            if (v[0].f >= 2) {
                ckmin(edgepairs, k);
                k -= edgepairs;
            }
            v[0].s -= edgepairs; v[len-1].s -= edgepairs;
//            cout << "edge pairs " << edgepairs << nl;
        }
        int leftCount = 0, rightCount = 0;
        FOR(i, 1, len-2) {
            if ((v[0].f ^ v[i].f) == 1) leftCount+=v[i].s;
            if ((v[len-1].f ^ v[i].f) == 1) rightCount+=v[i].s;
        }
        ckmin(leftCount, v[0].s);
        ckmin(rightCount, v[len-1].s);
        vi a;
        F0R(i, leftCount) a.pb(v[0].f);
        FOR(i, 1, len-2) F0R(j, v[i].s) a.pb(v[i].f);
        F0R(i, rightCount) a.pb(v[len-1].f);
        len = sz(a);
        if (len == 0) {
            cout << "Case " << tt+1 << ": " << edgepairs << nl;
            continue;
        }
        int dp[len][len][k+1];
//        trav(u, a) cout << u << " "; cout << nl;
        F0R(i, len) F0R(i2, len) F0R(j, k+1) dp[i][i2][j] = 0;
        FOR(l, 1, len-1) {
            F0R(i, len-l) {
                F0R(j, k+1) {
                    int tmp1 = dp[i+1][i+l][j], tmp2 = dp[i][i+l-1][j];
                    if ((a[i]^a[i+l])==1) {
                        int jj = j;
                        if (a[i] >= 2) jj--;
                        if (jj >= 0) {
                            ckmax(tmp1, dp[i+1][i+l-1][jj]+1);
                            ckmax(tmp2, dp[i+1][i+l-1][jj]+1);
                        }
                    }
                    FOR(o, i+1, i+l-1) {
                        if ((a[i]^a[o])==1) {
                            int jj = j;
                            if (a[o]>=2) jj--;
                            F0R(jjj, jj+1)
                                ckmax(tmp1, dp[i+1][o-1][jjj]+dp[o+1][i+l][jj-jjj]+1);
                        }
                        if ((a[o]^a[i+l])==1) {
                            int jj = j;
                            if (a[o]>=2) jj--;
                            F0R(jjj, jj+1)
                                ckmax(tmp2, dp[i][o-1][jjj]+dp[o+1][i+l-1][jj-jjj]+1);
                        }
                    }
                    assert(tmp1 == tmp2);
                    dp[i][i+l][j] = tmp1;
//                    cout << i << " " << i+l << " " << j << " " << dp[i][i+l][j] << nl;
                }
            }
        }
        cout << "Case " << tt+1 << ": " << dp[0][len-1][k]+edgepairs << nl;
    }
    return 0;
}
