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

int m = 0;

void print(int a, int b) {
    cout << a+1 << " " << b+1 << nl;
    m++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t; 
    while (t--) {
        m = 0;
        int n; cin >> n;
        string s; cin >> s;
        int cnt = 0;
        int idx = -1;
        F0R(i, n) {
            if (s[i] == '1') {
                cnt++;
            } else {
                if (s[(i+n-1)%n]=='1') idx = i;
            }
        }
        if (cnt%2 || cnt == 0) {
            cout << "NO" << nl;
            continue;
        }
        cout << "YES" << nl;
        if (idx == -1) {
            // assert(cnt==n);
            F0R(i, n-1) print(n-1, i);
            continue;
        }
        // dbg(idx+1);
        int prev = idx;
        vi v;
        int help = idx;
        FOR(i, 1, n-1) {
            int j = (idx+i)%n;
            if (s[j] == '0') {
                if (sz(v)%2) {
                    if (help == -1) {
                        print(j, prev);
                        help = prev;
                    } else {
                        print(j, help);
                        help = -1;
                    }
                    print(v.back(), prev);
                    v.pop_back();
                } else print(j, prev);
                trav(u, v) print(u, prev);
                v.clear();
                prev = j;
            } else v.pb(j);
        }
        if (help == -1) assert(sz(v)%2);
        else assert(sz(v)%2 == 0 && sz(v) >= 2);
        if (help != -1) {
            print(v.back(), help);
            v.pop_back();
        }
        trav(u, v) print(u, prev);
        if (m < n-1) assert(0);
    }
    return 0;
}
