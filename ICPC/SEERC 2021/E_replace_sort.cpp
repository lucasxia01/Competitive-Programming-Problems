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
#include <climits>

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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = 1e9+12123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e6+5000;
const int M = 5e5 + 1000;

int dpk[MX];
int t[2*MX];
int n, m;
int zero = M;
int cnt = 0;

int query(int j) {
    int p = j+zero;
    int res = INF;
    for (p += MX; p > 0; p >>= 1) {
        ckmin(res, t[p]);
    }
    return res;
}

void modify(int j, int R, int v) {
    // update a suffix 
    int l = j+zero, r = R+zero;
    for (l += MX, r += MX; l < r; l >>= 1, r >>= 1) {
        if (l&1) {
            ckmin(t[l], v);
            l++;
        }
        if (r&1) {
            r--;
            ckmin(t[r], v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int a[n]; F0R(i, n) cin >> a[i];
    int b[m]; F0R(i, m) cin >> b[i];
    sort(b, b+m);

    F0R(i, MX) dpk[i] = INF;
    F0R(i, 2*MX) t[i] = INF;
    
    F0R(i, n) {
        // dpk[i] = min(dpk[i-1] if a[i] > a[i-1], dps[i-1][j], b[j] < a[i] < b[j+1])
        if (i) { if (a[i] > a[i-1]) dpk[i] = dpk[i-1]; }
        else dpk[i] = 0;
        int idx = lower_bound(b, b+m, a[i])-b;
        // dbg("j for b[j] < a[i]", i, a[i], idx-1);
        if (idx > 0) // something to replace a[i-1]
            ckmin(dpk[i], query(idx-1)+cnt);

        // dps[i][j] = min(dpk[i-1] if a[i-1] < b[j], dps[i-1][j-1]) + 1
        zero--;
        if (i && b[0] > a[i-1]) modify(0, 1, dpk[i-1]-cnt);
        int val = 0;
        if (i) val = a[i-1];
        int j = lower_bound(b, b+m, val)-b;
        // dbg("j for b[j] > a[i-1]", j, val);
        int v = 0;
        if (i) v = dpk[i-1];
        modify(j, m, v-cnt);
        cnt++;
        // query 0 through n
        // F0R(j, m) cout << query(j)+cnt << " "; cout << nl;
    }
    // F0R(i, n) cout << dpk[i] << " "; cout << nl;
    int ans = dpk[n-1];
    // dbg(ans);
    F0R(i, m) ckmin(ans, query(i)+cnt);
    if (ans == INF) cout << -1 << nl;
    else cout << ans << nl;
    return 0;
}
