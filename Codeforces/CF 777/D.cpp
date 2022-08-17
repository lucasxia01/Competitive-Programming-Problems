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
        ll x, d; cin >> x >> d;
        if (x%(d*d) != 0) {
            cout << "NO" << nl;
            continue;
        }
        int cnt = 0;
        while (x%d == 0) {
            x /= d;
            cnt++;
        }
        ll xx = x;
        ll dd = d;

        map<int, int> mx, md;
        for (ll i = 2; i*i <= x; i++) {
            while (x%i==0) {
                if (mx.find(i) == mx.end()) mx[i] = 1;
                else mx[i]++;
                x/=i;
            }
        }
        // dbg(xx, x, sz(mx));
        bool xx_prime = 0;
        if (x != 1) {
            if (sz(mx) == 0) xx_prime = 1;
            if (mx.find(x) == mx.end()) mx[x] = 1;
            else mx[x]++;
        }
        for (ll i = 2; i*i <= d; i++) {
            while (d%i==0) {
                if (md.find(i) == md.end()) md[i] = 1;
                else md[i]++;
                d/=i;
            }
        }    
        bool d_prime = 0;
        if (d != 1) {
            if (sz(md) == 0) d_prime = 1;
            if (md.find(d) == md.end()) md[d] = 1;
            else md[d]++;
        }
        if (d_prime && (xx_prime || xx==1)) cout << "NO" << nl;
        else {
            if (xx == 1) {
                if (cnt == 2) {
                    cout << "NO" << nl;
                    continue;
                }
            }
            if (xx_prime) {
                if (cnt == 2) {
                    cout << "NO" << nl;
                    continue;
                }
                int cnt1 = 0, cnt2 = 0;
                ll y = dd*xx;
                while (y%xx == 0) {
                    cnt1++;
                    y/= xx;
                }
                while (dd%xx == 0) {
                    cnt2++;
                    dd/= xx;
                }
                if (dd != 1) {
                    cout << "YES" << nl;
                    continue;
                }
                if ((cnt2-1)*(cnt-1) < cnt1) {
                    cout << "NO" << nl;
                    continue;
                }
            }
            cout << "YES" << nl;
        }
    }
    return 0;
}
