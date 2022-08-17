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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vi p(n+1), a(n+1);
    int in[n+1]; F0R(i, n+1) in[i] = 0;
    FOR(i, 1, n) {
        cin >> p[i];
        in[p[i]]++;
    }
    int unused[n+1]; F0R(i, n+1) unused[i] = 1;
    int hi = 0;
    FOR(i, 1, n) {
        cin >> a[i];
        ckmax(hi, a[i]);
        if (a[i] <= n) unused[a[i]] = 0;
    }
    // find how many iterations
    int killed = 0;
    FOR(i, 1, n) killed += max(0, in[i]-1);
    assert((hi-n)%killed == 0);
    int m = (hi-n)/killed;
    // dbg(m);
    int nxt[n+1][30];
    FOR(i, 1, n) nxt[i][0] = p[i];
    F0R(i, 29) FOR(j, 1, n) nxt[j][i+1] = nxt[nxt[j][i]][i];
    int b[n+1];
    FOR(i, 1, n) {
        int cur = i;
        F0R(j, 30) if (m&(1<<j)) cur = nxt[cur][j];
        b[i] = cur;
        // dbg(i, b[i]);
    }
    set<int> q;
    FOR(i, 1, n) {
        if (unused[i]) {
            q.insert(i);
            // dbg(i);
        }
    }
    int ans[n+1];
    FOR(i, 1, n) {
        int val = a[b[i]];
        assert(val <= n);
        if (unused[val] == 0) {
            unused[val] = 1;
            ans[i] = val;
        } else {
            auto it = q.lb(val);
            assert(it != q.end());
            ans[i] = *it;
            q.erase(it);
        }
    }
    FOR(i, 1, n) cout << ans[i] << " "; cout << nl;
    return 0;
}
