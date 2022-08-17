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
const ll INF = (1<<29) + 123;
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
    int n, k, m;
    cin >> n >> k >> m;
    pair<pi, int> segs[m];
    F0R(i, m) {
        cin >> segs[i].f.f >> segs[i].f.s >> segs[i].s;
    }
    ll ans = 1;
    F0R(i, k) {
        vpi ones, zeros;
        F0R(j, m) {
            if (segs[j].s&(1<<i)) ones.pb(segs[j].f);
            else zeros.pb(mp(segs[j].f.s, segs[j].f.f));
        }
        sort(ones.begin(), ones.end());
        sort(zeros.begin(), zeros.end());
        ll dp[n+1]; // dp[i] has 0 at position i, all segments to left are ok
        ll prefixdp[n+1];
        int maxOneR = 0;
        int maxZeroL = 0;
        dp[0] = 1;
        prefixdp[0] = 0;
        int o = 0, z = 0;
        FOR(j, 1, n) {
            while (o < sz(ones) && ones[o].f == j) {
                ckmax(maxOneR, ones[o].s);
                o++;
            }
            prefixdp[j] = (prefixdp[j-1]+dp[j-1])%MOD;
            if (j > maxOneR) dp[j] = (prefixdp[j]-prefixdp[maxZeroL]+MOD)%MOD;
            else dp[j] = 0;
            while (z < sz(zeros) && zeros[z].f == j) {
                ckmax(maxZeroL, zeros[z].s);
                z++;
            }
        }
        ans = (ans * (prefixdp[n]-prefixdp[maxZeroL]+dp[n]+MOD)%MOD)%MOD;
    }
    cout << ans << endl;
    return 0;
}
