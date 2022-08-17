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
    F0R(tt, t) {
        int e, w; cin >> e >> w;
        int x[e][w];
        int ans = 0;
        F0R(i, e) F0R(j, w) {
            cin >> x[i][j];
        }
        int next_smaller[102][w];
        vi v[e][w];
        F0R(i, 102) F0R(j, w) next_smaller[i][j] = e;
        F0Rd(i, e) F0R(j, w) {
            FOR(k, 1, x[i][j]) {
                v[i][j].pb(next_smaller[k][j]);
            }
            next_smaller[x[i][j]+1][j] = i;
            F0R(k, 101) ckmin(next_smaller[k+1][j], next_smaller[k][j]);
        }
        // F0R(i, e) F0R(j, w) {
        //     dbg(x[i][j]);
        //     FOR(k, 1, x[i][j]) {
        //         dbg(i, j, k, v[i][j][k-1]);
        //     }
        // }
        vi s;
        F0R(i, e) {
            while (sz(s) && s.back() == i) s.pop_back();
            F0R(j, sz(s)-1) assert(s[j] >= s[j+1]);
            vi t;
            F0R(j, w) {
                int prev = 0;
                if (i > 0) prev = x[i-1][j];
                FOR(k, prev+1, x[i][j]) {
                    t.pb(v[i][j][k-1]);
                }
            }
            ans += 2*sz(t);
            sort(all(t)); reverse(all(t));
            if (sz(t) == 0) continue;
            vi p;
            while (sz(s) && s.back() < t[0]) {
                p.pb(s.back());
                ans += 2;
                s.pop_back();
            }
            reverse(all(p));
            // now merge sort
            int j = 0, k = 0;
            p.pb(-1);
            t.pb(-1);
            while (1) {
                if (p[j] == -1 && t[k] == -1) break;
                if (p[j] < t[k]) {
                    s.pb(t[k]);
                    k++;
                } else {
                    s.pb(p[j]);
                    j++;
                }
            }
            F0R(j, sz(s)-1) assert(s[j] >= s[j+1]);
        }

        cout << "Case #" << tt+1 << ": " << ans << nl;
    }
    return 0;
}
