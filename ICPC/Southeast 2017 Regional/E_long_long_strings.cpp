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

#define int long long

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vector<pair<char, pair<int, char> > > a[2];
    F0R(i, 2) {
        while (1) {
            char c; cin >> c;
            if (c == 'D') {
                int x; cin >> x;
                a[i].pb({'D', {x, 0}});
            } else if (c == 'I') {
                int x; cin >> x;
                char y; cin >> y;
                a[i].pb({'I', {x, y}});
            } else {
                break;
            }
        }
    }
    // now prune each list of matching I and D
    F0R(i, 2) {
        F0R(j, sz(a[i])) {
            if (a[i][j].f == 'D') continue;
            int p = a[i][j].s.f;
            FOR(k, j+1, sz(a[i])-1) {
                if (a[i][k].f == 'D') { // del
                    if (a[i][k].s.f == p) {
                        // remove both j and k
                        int cur = a[i][j].s.f;
                        FOR(kk, j+1, k-1) {
                            if (a[i][kk].f == 'D' && a[i][kk].s.f < cur) cur--;
                            if (a[i][kk].f == 'D' && a[i][kk].s.f > cur) a[i][kk].s.f--; 
                            if (a[i][kk].f == 'I' && a[i][kk].s.f <= cur) cur++;
                            if (a[i][kk].f == 'I' && a[i][kk].s.f > cur) a[i][kk].s.f--;
                        }
                        a[i].erase(a[i].begin()+j);
                        a[i].erase(a[i].begin()+(k-1));
                        j--;
                        break;
                    } else if (a[i][k].s.f < p) p--;
                } else { // insert
                    if (a[i][k].s.f <= p) p++;
                }
            }
        }
    }
    if (sz(a[0]) != sz(a[1])) {
        cout << 1 << nl;
        return 0;
    }
    // now bubble sort them
    F0R(i, 2) {
        F0R(j, sz(a[i])-1) {
            F0R(k, sz(a[i])-1) {
                if (a[i][k].f == 'D' && a[i][k+1].f == 'D') { // D D
                    if (a[i][k+1].s.f < a[i][k].s.f) {
                        a[i][k].s.f--;
                        swap(a[i][k], a[i][k+1]);
                    }
                } else if (a[i][k].f == 'I' && a[i][k+1].f == 'D') { // I D
                    if (a[i][k].s.f < a[i][k+1].s.f) {
                        a[i][k+1].s.f--;
                    } else if (a[i][k].s.f > a[i][k+1].s.f) {
                        a[i][k].s.f--;
                    } else {
                        
                    }
                    swap(a[i][k], a[i][k+1]);
                } else if (a[i][k].f == 'I' && a[i][k+1].f == 'I') { // I I
                    if (a[i][k].s.f >= a[i][k+1].s.f) {
                        a[i][k].s.f++;
                        swap(a[i][k], a[i][k+1]);
                    }
                }
            }
        }
    }
    bool ok = 1;
    F0R(i, sz(a[0])) {
        if (a[0][i] != a[1][i]) ok = 0;
    }
    cout << !ok << nl;
    return 0;
}
