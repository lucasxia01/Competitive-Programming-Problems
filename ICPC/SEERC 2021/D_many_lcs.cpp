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

const int MX = 8848+10;

unordered_map<ll, pi> s;

ll dp[MX][MX+1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int k; cin >> k;
    if (k == 1) {
        cout << 1 << nl << 0 << nl;
        return 0;
    } else if (k == 2) {
        cout << "10" << nl << "01" << nl;
        return 0;
    }
    dp[0][0] = 1;
    s[1] = {1, 0};
    FOR(i, 1, MX-1) {
        FOR(j, 1, i-1) {
            if (dp[i-1][j-1] == -1 || dp[i-1][j] == -1) dp[i][j] = -1;
            else {
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                if (dp[i][j] > 1e9) dp[i][j] = -1;
                else {
                    s[dp[i][j]] = {i, j};
                    if (s.find(k-dp[i][j]) != s.end()) {
                        pi a = s[k-dp[i][j]];
                        F0R(l, a.s) cout << 0; F0R(l, j) cout << 1; cout << nl;
                        F0R(l, i) cout << 1; F0R(l, a.s) cout << 0; cout << nl;
                        return 0;
                    }
                }
            }
        }
        dp[i][0] = dp[i][i] = 1;
    }
    return 0;
}
