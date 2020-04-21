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
const ll INF = (1LL<<62) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n[3];
        cin >> n[0] >> n[1] >> n[2];
        vl a[3];
        F0R(i, 3) F0R(j, n[i]) a[i].pb(0);
        F0R(j, 3) F0R(i, n[j]) cin >> a[j][i];
        F0R(i, 3) sort(a[i].begin(), a[i].end());
        int p[3] = {0, 1, 2};
        ll ans = INF;
        do {
            // cout << p[0] << " " << p[1] << " " << p[2] << endl;
            F0R(i, n[p[0]]) {
                ll aa = a[p[0]][i];
                auto c = lower_bound(a[p[2]].begin(), a[p[2]].end(), aa);
                if (c == a[p[2]].end()) continue;
                ll cc = *c;
                auto b1 = lower_bound(a[p[1]].begin(), a[p[1]].end(), (aa+cc)/2);
                auto b2 = b1;
                if (b1 != a[p[1]].begin()) b1--;
                ll bb1 = -1, bb2 = -1, bb;
                if (b1 != a[p[1]].end()) bb1 = *b1;
                if (b2 != a[p[1]].end()) bb2 = *b2;
                if (bb1 < 0 && bb2 < 0) continue;
                else if (bb1 < 0) bb = bb2;
                else if (bb2 < 0) bb = bb1;
                else if (abs(2*bb1-aa-cc) < abs(2*bb2-aa-cc)) bb = bb1;
                else bb = bb2;
                // cout << aa << " "  << bb << " " << cc << endl;
                ckmin(ans, (aa-bb)*(aa-bb)+(aa-cc)*(aa-cc)+(bb-cc)*(bb-cc));
            }
        } while (next_permutation(p, p+3));
        cout << ans << endl;
    }
    return 0;
}
