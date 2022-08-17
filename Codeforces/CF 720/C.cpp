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

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int posN = -1;
        F0R(i, n/2) {
            vi v = {1, i+1, n-i, n-1};
            cout << "?";
            trav(vv, v) cout << " " << vv; cout << nl;
            cout.flush();
            int x; cin >> x;
            if (x == n) {
                posN = n-i;
            } else if (x == n-1) {
                v = {1, n-i, i+1, n-1};
                cout << "?";
                trav(vv, v) cout << " " << vv; cout << nl;
                cout.flush();
                int x; cin >> x;
                if (x == n) {
                    posN = i+1;
                } else if (x == -1) {
                    return 0;
                }
            } else if (x == -1) {
                return 0;
            }
            if (posN != -1) break;
        }
        if (posN == -1) posN = n/2+1;
        int ans[n]; F0R(i, n) ans[i] = -1; ans[posN-1] = n;
        F0R(i, n) {
            if (i+1 != posN) {
                vi v = {2, i+1, posN, 1};
                cout << "?";
                trav(vv, v) cout << " " << vv; cout << nl;
                cout.flush();
                int x; cin >> x;
                if (x == -1) return 0;
                ans[i] = x;
            }
        }
        cout << "!";
        F0R(i, n) cout << " " << ans[i]; cout << nl;
        cout.flush();
    }
    return 0;
}
