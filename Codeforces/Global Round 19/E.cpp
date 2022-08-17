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
        int n, m; cin >> n >> m;
        ll a[n]; F0R(i, n) cin >> a[i];
        set<pl> s; F0R(i, m) {
            ll u, v; cin >> u >> v;
            s.insert({u, v}); s.insert({v, u});
        }
        map<ll, ll> f; F0R(i, n) if (f.find(a[i]) == f.end()) f[a[i]] = 1; else f[a[i]]++;
        vl c[n+1];
        trav(ff, f) c[ff.s].pb(ff.f);
        vl v; F0R(i, n+1) if (sz(c[i])) v.pb(i);
        // brute force
        ll ans = 0;
        trav(i, v) sort(all(c[i]), greater<ll>());
        trav(i, v) {
            trav(ii, v) {
                if (i == ii) {
                    if (sz(c[i]) < 2) continue;
                    int SZ = sz(c[i]);
                    F0R(j, SZ) {
                        FOR(k, j+1, SZ-1) {
                            if (s.find({c[i][j], c[i][k]}) == s.end()) {
                                ckmax(ans, (2LL*i)*(c[i][j]+c[i][k]));
                                break;
                            }
                        }
                    }
                } else if (i < ii) {
                    int SZ = sz(c[i]);
                    int SZ2 = sz(c[ii]);
                    F0R(j, SZ) {
                        F0R(k, SZ2) {
                            if (s.find({c[i][j], c[ii][k]}) == s.end()) {
                                ckmax(ans, ((ll)i+ii)*(c[i][j]+c[ii][k]));
                                break;
                            }
                        }
                    }
                }
            }
            
        }
        cout << ans << nl;
    }
    return 0;
}
