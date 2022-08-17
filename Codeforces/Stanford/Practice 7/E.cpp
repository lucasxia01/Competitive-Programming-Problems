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
    vi t[2];
    F0R(i, n) {
        int a, b; cin >> a >> b;
        t[b].pb(a);
    }
    t[0].pb(MX); t[1].pb(MX);
    reverse(all(t[0]));
    reverse(all(t[1]));
    int dir = -1;
    int T = 0;
    while (sz(t[0]) > 1 || sz(t[1]) > 1) {
        int l = t[0].back(), r = t[1].back();
        if (dir == -1) {
            // find the lowest one
            if (l < r) {
                T = l+10;
                t[0].pop_back();
                dir = 0;
            } else {
                T = r+10;
                t[1].pop_back();
                dir = 1;
            }
        } else if (dir == 0) {
            if (l < T) {
                T = l+10;
                t[0].pop_back();
            } else if (l < r) {
                T = l+10;
                t[0].pop_back();
            } else if (r < T) {
                while (t[1].back() < T)
                    t[1].pop_back();
                T += 10;
                dir = 1;
            } else {
                T = r+10;
                t[1].pop_back();
                dir = 1;
            }
        } else {
            if (r < T) {
                T = r+10;
                t[1].pop_back();
            } else if (r < l) {
                T = r+10;
                t[1].pop_back();
            } else if (l < T) {
                while (t[0].back() < T)
                    t[0].pop_back();
                T += 10;
                dir = 0;
            } else {
                T = l+10;
                t[0].pop_back();
                dir = 0;
            }
        }
    }
    cout << T << nl;
    return 0;
}