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
#define sz(x) (int)x.size()

const int MAX_N = 100011;
const ll INF = (1LL<<50) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n, k;
    cin >> n >> k;
    ll a[n];
    F0R(i, n) cin >> a[i];
    sort(a, a+n);
    unordered_map<ll, ll> lPos, rPos, ans; // for each element value, lPos and rPos are the left and right of its range in sorted array
    ll sufSums[n+1], preSums[n+1]; // suffix and prefix sums, one of them is unnecessary
    sufSums[n] = preSums[0] = 0;
    F0R(i, n) {
        if (lPos.find(a[i]) == lPos.end()) lPos[a[i]] = rPos[a[i]] = i;
        else rPos[a[i]] = i;
        sufSums[n-1-i] = sufSums[n-i] + a[n-1-i];
        preSums[i+1] = preSums[i] + a[i];
    }
    ll ret = INF;
    // main idea is we want to end (have k same) on something we already have
    // also no point in having intermediates when pushing in sides
    F0R(i, n) {
        if (ans.find(a[i]) == ans.end()) { // if already computed the value, skip
            ll l = lPos[a[i]], r = rPos[a[i]]+1;
            ll c = r-l, c1 = l, c2 = n-r;
            if (c >= k) { // if done already return
                cout << 0 << endl;
                return 0;
            }
            // costs are computed of pushing everything up to one below/above
            ll cost1 = (a[i]-1)*c1 - preSums[l];
            ll cost2 = sufSums[r] - (a[i]+1)*c2;
            // four cases of seeing which side(s) to push in to the current value
            if (cost1 <= cost2 && c1+c >= k) {
                ans[a[i]] = cost1 + k-c;
                ckmin(ret, cost1 + k-c);
            } else if (cost2 <= cost1 && c2+c >= k) {
                ans[a[i]] = cost2 + k-c;
                ckmin(ret, cost2 + k-c);
            } else if (c1+c >= k) {
                ans[a[i]] = cost1 + k-c;
                ckmin(ret, cost1 + k-c);
            } else if (c2+c >= k) {
                ans[a[i]] = cost2 + k-c;
                ckmin(ret, cost2 + k-c);
            } else { // one side is not enough so we have to set up both sides
                ans[a[i]] = cost1+cost2+k-c;
                ckmin(ret, cost1+cost2+k-c);
            }
        }
    }
    cout << ret << endl;
    
    
    return 0;
}
