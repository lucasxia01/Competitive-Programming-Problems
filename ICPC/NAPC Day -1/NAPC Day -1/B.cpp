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
const int MX = 3e5+5;
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
        ll a[n];
        F0R(i, n) cin >> a[i];
        ll ans = 0;
        ll maxs[n], mins[n];
        ll curMax = -MX;
        F0R(i, n) {
            if (ckmax(curMax, a[i])) maxs[i] = i;
            else maxs[i] = maxs[i-1];
            //cout << maxs[i] << " ";
        } //cout << endl;
        ll curMin = MX;
        F0Rd(i, n) {
            if (ckmin(curMin, a[i])) mins[i] = i;
            else mins[i] = mins[i+1];
            //cout << mins[i] << " ";
        } //cout << endl;
        ll curIdx = -1, prevIdx;
        while (curIdx < n-1) {
            prevIdx = curIdx+1;
            curIdx = mins[prevIdx];
            cout << prevIdx << " " << curIdx << endl;
            if (prevIdx) ans += a[curIdx]-a[maxs[prevIdx-1]];
            FOR(i, prevIdx, curIdx-1) ans += a[curIdx]-a[i];
        }
        cout << ans << endl;
    }
    
    return 0;
}
