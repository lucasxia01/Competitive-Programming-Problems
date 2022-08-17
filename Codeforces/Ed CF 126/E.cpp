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
const ll INF = (1<<29) + 123;
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

const int MX = 1<<20;

struct bucketPair {
    int l, r, bSize, index;
    bool operator< (bucketPair const& other) const {
        if (l/bSize == other.l/bSize) return r < other.r;
        return l/bSize < other.l/bSize;
    }
};

int par[6];
int sz[6];

int find_set(int v) {
    if (v == par[v])
        return v;
    return find_set(par[v]);
}

void merge(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    }
}

string A[3];
int conv(int i, int j, int s) {
    return i*3+j - s*3;
}
int comps(int s, int e) {
    if (s == -1) s++;
    if (e == -1) return 0;
    F0R(i, 6) par[i] = i;
    F0R(i, 6) sz[i] = 1;
    FOR(i, s, e) {
        F0R(j, 3) {
            if (i < e && A[j][i] == '1' && A[j][i+1] == '1') merge(conv(i, j, s), conv(i+1, j, s));
            if (j < 2 && A[j][i] == '1' && A[j+1][i] == '1') merge(conv(i, j, s), conv(i, j+1, s));
        }
    }
    int ans = 0;
    FOR(i, s, e) {
        F0R(j, 3) {
            if (A[j][i] == '1' && conv(i, j, s) == par[conv(i, j, s)]) ans++;
        }
    }
    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q, Q;
    cin >> n;
    F0R(i, 3) cin >> A[i];
    int SQRTN = sqrt(n) + 1000;
    vector<bucketPair> v;
    cin >> q;
    Q = q;
    ll ans[q];
    while (q--) {
        bucketPair range;
        cin >> range.l >> range.r;
        range.l--;
        range.bSize = SQRTN;
        range.index = Q-q-1;
        v.pb(range);
    }
    sort(v.begin(), v.end());
    int l = 0, r = 0;
    ll total = 0;
    trav(a, v) {
        dbg("start", a.l, a.r, total);
        while (l < a.l) {
            total -= comps(l, l+1) - comps(l+1, l+1);
            dbg(l, r, total);
            l++;
        }
        while (l > a.l) {
            l--;
            total += comps(l, l+1) - comps(l+1, l+1);
            dbg(l, r, total);
        }
        while (r < a.r) {
            total += comps(r-1, r) - comps(r-1, r-1);
            dbg(l, r, total);
            r++;
        }
        while (r > a.r) {
            r--;
            total -= comps(r-1, r) - comps(r-1, r-1);
            dbg(l, r, total);
        }
        dbg("end", a.l, a.r, total);
        ans[a.index] = total;
    }
    F0R(i, Q) cout << ans[i] << endl;
    return 0;
}
