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

const int MX = 1005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    F0R(t, T) {
        int n;
        cin >> n;
        pi a[n];
        vector<pair<pi, int> > times;
        F0R(i, n) {
            cin >> a[i].f >> a[i].s;
            times.pb(mp(mp(a[i].f, 1), i)); // 1 is start
            times.pb(mp(mp(a[i].s, -1), i)); // -1 is end
        }
        sort(times.begin(), times.end());
        string ans(n, '0');
        int c = -1, j = -1;
        bool ok = true;
        F0R(i, 2*n) {
            if (times[i].f.s == 1) { // start
                if (c == -1) {
                    c = times[i].s;
                    ans[times[i].s] = 'C';
                } else if (j == -1)  {
                    j = times[i].s;
                    ans[times[i].s] = 'J';
                } else {
                    cout << "Case #" << t+1 << ": IMPOSSIBLE\n";
                    ok = false;
                    break;
                }
            } else {
                if (c == times[i].s) c = -1;
                else if (j == times[i].s) j = -1;
                else assert(1 == 0);
            }
        }
        if (!ok) continue;
        cout << "Case #" << t+1 << ": " << ans << "\n";
    }
    return 0;
}
