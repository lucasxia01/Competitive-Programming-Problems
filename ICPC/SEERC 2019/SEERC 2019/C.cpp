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
const ll INF = 2e9+1;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int n;

int query2Range(int lo, int hi) {
    cout << "2 " << hi-lo+1;
    FOR(i, lo, hi) cout << " " << i+1; cout << nl;
    cout.flush();
    int count = (hi-lo)*(hi-lo+1)/2;
    int maxDiff = 0, x;
    F0R(i, count) {
        cin >> x;
        ckmax(maxDiff, x);
    }
    return maxDiff;
}

int query1(int p) {
    cout << "1 " << p+1 << nl;
    cout.flush();
    int x; cin >> x;
    return x;
}

set<int> query2Bit(int bit, int m) {
    vi idx;
    FOR(i, 1, n) if (i&(1<<bit) && i != m) idx.pb(i);
    int x; vi vals, allvals;
    if (sz(idx) >= 2) {
        cout << "2 " << sz(idx);
        trav(a, idx) cout << " " << a; cout << nl;
        cout.flush();
        int count = sz(idx)*(sz(idx)-1)/2;
        F0R(i, count) cin >> x, vals.pb(x);
    }
    idx.pb(m);
    if (sz(idx) >= 2) {
        cout << "2 " << sz(idx);
        trav(a, idx) cout << " " << a; cout << nl;
        cout.flush();
        int count = sz(idx)*(sz(idx)-1)/2;
        F0R(i, count) cin >> x, allvals.pb(x);
    }
    sort(vals.begin(), vals.end());
    sort(allvals.begin(), allvals.end());
    int j = 0;
    set<int> v;
    trav(a, allvals) {
        if (j < sz(vals) && a == vals[j]) j++;
        else v.insert(a);
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    if (n <= 2) {
        vi ans;
        F0R(i, n) ans.pb(query1(i));
        cout << "3";
        trav(a, ans) cout << " " << a; cout << nl;
        return 0;
    }
    // binary search to find min/max
    int lo = 0, hi = n-1;
    int diff = query2Range(0, hi);
    while (lo < hi) {
        int mid = (lo+hi)/2;
        int curDiff = query2Range(0, mid);
        if (curDiff != diff) lo = mid+1;
        else hi = mid;
    }
    int val = query1(hi);
    int val2 = query1(0); // for comparison
    vector<set<int> > vals;
    F0R(i, 8) vals.pb(query2Bit(i, hi+1));
    cout << "3";
    FOR(i, 1, n) {
        if (i == hi+1) {
            cout << " " << val;
            continue;
        }
        map<int, int> m;
        int ans = -1;
        F0R(j, 8) {
            if (i&(1<<j)) trav(a, vals[j]) m[a]++;
            else trav(a, vals[j]) m[a]--;
        }
        trav(a, m) if (a.s == __builtin_popcount(i)) ans = a.f;
        assert(ans != -1);
        if (val2 <= val) cout << " " << val-ans;
        else cout << " " << val+ans;
    }
    cout << nl;
    cout.flush();
    return 0;
}
