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

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    F0R(tt, t) {
        int R; cin >> R;
        cout << "Case #" << tt+1 << ": ";
        ll total = 1;
        FOR(r, 1, R) {
            // char m[2*R+1][2*R+1]; F0R(i, 2*R+1) F0R(j, 2*R+1) m[i][j] = '.';
            // FOR(i, -r, r) {
            //     int y = roundl(sqrtl((ld)r*r-(ld)i*i));
            //     int x = i;
            //     if (y > R) {
            //         dbg(x, y);
            //     }
            //     m[x+R][y+R] = m[x+R][R-y] = m[y+R][x+R] = m[-y+R][x+R] = '#';
            // }
            // cout << r << nl;
            // F0R(i, 2*R+1) {
            //     F0R(j, 2*R+1) {
            //         cout << m[i][j];
            //         // if (m[i][j] == '#') cnt++;
            //     }
            //     cout << nl;
            // }

            ll x = roundl(sqrtl((ld)r*r/2));
            ll cnt = 0;
            if (x == roundl(sqrtl((ld)r*r-(ld)x*x))) {
                cnt -= 4;
            } 
            while (x > roundl(sqrtl((ld)r*r-(ld)x*x))) {
                x--;
            }
            cnt += 4*2*x+4;
            total += cnt;
            // dbg(cnt);

        }
        ll c = 1;
        ld y = 0;
        FORd(i, 1, R) {
            while (roundl(sqrtl((ld)i*i+(ld)y*y)) <= R) y++;
            c += 4*y;
        }
        // FOR(i, -R, R) {
        //     FOR(j, -R, R) {
        //         if (roundl(sqrtl((ld)i*i+(ld)j*j)) <= R) c++;
        //     }
        // }
        // dbg(c, total);
        cout << c - total << nl;
    }
    
    return 0;
}
