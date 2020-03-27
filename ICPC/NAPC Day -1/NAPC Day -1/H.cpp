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

const int MAX_N = 100011;
const int MX = 1<<20;
const ll INF = (1LL<<50) + 123;
const ll MOD = 998244353;
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        int marked[n+1];
        F0R(i, n+1) marked[i] = 0;;
        F0R(i, n) {
            cin >> a[i];
            marked[a[i]] = 1;
        }
        int MEX = 0;
        F0R(i, n+1) if (!marked[i]) {
            MEX = i;
            break;
        }
        int next[n];
        int numGood = 0;
        int freq[MEX];
        F0R(i, MEX) freq[i] = 0;
        int l = 0, r = 0;
        while (l < n) {
            while (r < n && numGood < MEX) {
                if (a[r] < MEX) {
                    if (!freq[a[r]]) numGood++;
                    freq[a[r]]++;
                }
                r++;
            }
            if (numGood == MEX) next[l] = max(r-1, l);
            else next[l] = -1;
            if (a[l] < MEX) {
                if (freq[a[l]] == 1) numGood--;
                freq[a[l]]--;
            }
            l++;
        }
        ll dp[n+1];
        F0R(i, n+1) dp[i] = 0;
        dp[0] = 1;
        FOR(i, 1, n) {
            if (i > 1) dp[i] = (dp[i] + dp[i-1])%MOD;
            if (next[i-1] != -1) dp[next[i-1]+1] = (dp[next[i-1]+1]+dp[i-1])%MOD;
        }
        cout << dp[n] << endl;
    }
    
    return 0;
}
