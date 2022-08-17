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

const int MX = 4005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("rhymes.in", "r", stdin);
//    freopen("rhymes.out", "w", stdout);
    int n; cin >> n;
    set<int> vals;
    int a[n+1]; FOR(i, 1, n) {
        cin >> a[i];
        vals.insert(a[i]);
    }
    map<int, int> m;
    int c = 0;
    trav(u, vals) m[u] = ++c;
    FOR(i, 1, n) a[i] = m[a[i]];
    vector<vi> ans;
    int cur = 0;
    vi count[MX];
    pi hi = {-1, -1};
    int hiVal = -1;
    FOR(i, 1, n) {
        count[a[i]].pb(i);
        vi temp;
        int SZ = sz(count[a[i]]);
        if (SZ >= 4 && count[a[i]][SZ-4] > cur) {
            temp = {count[a[i]][SZ-4], count[a[i]][SZ-3], count[a[i]][SZ-2], count[a[i]][SZ-1]};
            ans.pb(temp);
            cur = temp[3];
        } else if (SZ >= 2 && hiVal != -1 && hiVal != a[i] && min(hi.f, count[a[i]][SZ-2]) > cur) {
            temp = {count[a[i]][SZ-1], count[a[i]][SZ-2], hi.f, hi.s};
            sort(temp.begin(), temp.end());
            ans.pb(temp);
            cur = temp[3];
        }
        if (SZ >= 2 && count[a[i]][SZ-2] > hi.f) {
            hi = {count[a[i]][SZ-2], count[a[i]][SZ-1]};
            hiVal = a[i];
        }
    }
    sort(ans.begin(), ans.end());
    printf("%d\n", sz(ans));
    trav(v, ans) {
        trav(u, v) printf("%d ", u); printf("\n");
    }
    return 0;
}
