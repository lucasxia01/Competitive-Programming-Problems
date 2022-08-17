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
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int a[n]; F0R(i, n) cin >> a[i];
        vi pos; // positions that are unassigned
        bool vis[n+1]; F0R(i, n+1) vis[i] = 0;
        int ans[n];
        int A = 0;
        F0R(i, n) {
            if (!vis[a[i]]) {
                ans[i] = a[i];
                vis[a[i]] = 1;
                A++;
            } else {
                pos.pb(i);
            }
        }
        vi v;
        FOR(i, 1, n) if (!vis[i]) v.pb(i); // people no one cares about
        if (sz(v) == 1 && pos[0]+1 == v[0]) { // redo assignment from the back
            pos.clear();
            F0R(i, n+1) vis[i] = 0;
            F0Rd(i, n) {
                if (!vis[a[i]]) {
                    ans[i] = a[i];
                    vis[a[i]] = 1;
                } else {
                    pos.pb(i);
                }
            }
            v.clear();
            FOR(i, 1, n) if (!vis[i]) v.pb(i);
        }
        assert(sz(v) == sz(pos));
        // see which ones are the same and offset them
        vi w;
        vi np;
        trav(p, pos) {
            if (!vis[p+1]) {
                w.pb(p);
            } else np.pb(p);
        }
        // trav(ww, w) cout << ww << " "; cout << nl;
        // trav(npnp, np) cout << npnp << " "; cout << nl;
        vi nv;
        if (sz(w) != 1) {
            F0R(i, sz(w)) {
                vis[w[i]+1] = 1;
                ans[w[i]] = w[(i+1)%sz(w)]+1;
            }
        } else if (sz(w) == 1) {
            np.pb(w[0]);
            nv.pb(w[0]+1);
            vis[w[0]+1] = 1;
        }
        FOR(i, 1, n) if (!vis[i]) nv.pb(i);
        // trav(nvnv, nv) cout << nvnv << " "; cout << nl;
        
        assert(sz(nv) == sz(np));
        F0R(i, sz(nv)) {
            ans[np[i]] = nv[i];
        }
        cout << A << nl;
        F0R(i, n) cout << ans[i] <<  " ";
        cout << nl;
    }
    return 0;
}
