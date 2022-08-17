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

const int MAX_N = 200011;
const ll INF = (1<<29) + 123;
const ll LLINF = (1LL<<50) + 777;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()
#define all(v) v.begin(),v.end()

int main() {
    int n;
    cin >> n;
    ll a[n];
    F0R(i, n) cin >> a[i];
    ll ans = 0;
    FOR(i, 1, 28) { // for each bit, we want to see the number of 1s in each sum
        vl t;
        F0R(j, n) t.pb(a[j]%(1<<i)); // we truncate up to that bit
        sort(t.begin(), t.end()); // sort to set up binary search
        ll count = 0;
        trav(v, t) { // for each number, we look for how many numbers sum to get a 1 in the ith position
            // first range is [2^(i-1), 2^i)
            count += (ll) (lower_bound(all(t), (1<<i)-v) - lower_bound(all(t), (1<<(i-1))-v));
            if (2*v >= (1<<(i-1)) && 2*v < (1<<i)) count--;
            // second range is [2^(i-1)+2^i, 2^(i+1))
            count += (ll) (t.end() - lower_bound(all(t), (1<<(i-1))+(1<<i)-v));
            if (2*v >= (1<<(i-1))+(1<<i) && 2*v < (1<<(i+1))) count--;
        }
        if ((count>>1)&1) ans += (1<<(i-1)); // double counted so divide by 2
    }
    cout << ans << endl;
    return 0;
}
