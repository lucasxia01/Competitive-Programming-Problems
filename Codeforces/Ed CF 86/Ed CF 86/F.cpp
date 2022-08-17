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

const int N = 15;
int dp[N+1][1<<N][N+1]; // the minimum possible value of the previous element in the array, states are current count of numbers that are left, current bitmask of elements used, and current index
pi p[N+1][1<<N][N+1]; // this is to restore the answer from the dp, it stores the mask and the previous position that it came from
int maskSum[1<<N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        F0R(i, n) cin >> a[i];
        F0R(cnt, n+1) F0R(mask, 1<<n) F0R(pos, n+1) dp[cnt][mask][pos] = INF;
        F0R(i, 1<<n) {
            maskSum[i] = 0;
            F0R(j, n) if (i & (1<<j)) maskSum[i] += a[j];
        }
        dp[0][0][0] = 0;
        F0R(cnt, n) {
            F0R(mask, 1<<n) {
                F0R(pos, n) {
                    if (dp[cnt][mask][pos] == INF) continue;
                    int newMask = mask ^ ((1<<n)-1);
                    for (int m = newMask; m != 0; m = (m-1)&newMask) {
                        if (maskSum[m] <= dp[cnt][mask][pos]) continue; // if the sum is smaller than current one, we can't use it
                        if (m >> pos == 0) continue; // if the new mask doesn't use anything past the current position, then we can't add everything in the mask to something past the current position
                        // we greedily choose the leftmost position after pos as the element that aggregates the whole mask
                        // we can do this with counting trailing zeros of the mask after pos
                        int npos = pos + __builtin_ctz(m>>pos)+1;
                        if (ckmin(dp[cnt+1][mask|m][npos], maskSum[m]))
                            p[cnt+1][mask|m][npos] = {m, pos};
                    }
                }
            }
        }
        int maxCnt = 0, ansPos = 0;
        F0R(cnt, n+1) F0R(pos, n+1) if (dp[cnt][(1<<n)-1][pos] != INF) {
            maxCnt = cnt; ansPos = pos;
        }
        vpi ans;
        int curMask = (1<<n)-1, curPos = ansPos;
        FORd(cnt, 1, maxCnt) { // this is restoring the answer with the p array
            int nMask = p[cnt][curMask][curPos].f;
            F0R(i, n) if (nMask & (1<<i)) if (i != curPos-1) ans.pb({i, curPos-1});
            curPos = p[cnt][curMask][curPos].s;
            curMask = curMask^nMask;
        }
        cout << sz(ans) << nl;
        int idx[n]; // indices change as u delete stuff so this has the correct index
        F0R(i, n) idx[i] = i;
        trav(a, ans) {
            int i = idx[a.f], j = idx[a.s];
            FOR(k, a.f, n-1) idx[k]--; // deleting a.f so adjust indices
            cout << i+1 << " " << j+1 << nl;
        }
        
        
    }
    return 0;
}
