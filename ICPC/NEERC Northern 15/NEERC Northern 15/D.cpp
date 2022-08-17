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
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    freopen("distribution.in", "r", stdin);
    freopen("distribution.out", "w", stdout);
    int t;
    cin >> t;
    ll pow = 1, high = 1;
    F0R(i, 18) high *= 10;
    ll powers2[63];
    int p = 0;
    while (pow < high) {
        powers2[p] = pow;
        pow *= 2; p++;
    }
    ll powers3[50];
    pow = 1;
    p = 0;
    while (pow < high) {
        powers3[p] = pow;
        pow *= 3; p++;
    }
    ll x;
    while (t--) {
        vector<ll> ans;
        cin >> x;
        int curPow2 = 0;
        int curPow3 = p-1;
        while (x) {
            if (x % 2 == 0) {
                curPow2++;
                x /= 2;
                continue;
            }
            if (powers3[curPow3] <= x) {
                ans.pb(powers2[curPow2]*powers3[curPow3]);
                x -= powers3[curPow3];
            }
            curPow3--;
        }
        cout << ans.size() << endl;
        trav(a, ans) cout << a << " ";
        cout << endl;
    }
    return 0;
}
