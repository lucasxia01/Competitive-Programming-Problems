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
#define rep(i, a, b) for(int i = a; i < (b); ++i)

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
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        string s; cin >> s; int n = sz(s);
        // now try to partition
        char prev = 'C';
        string t = "";
        vector<string> v;
        F0R(i, n) {
            if (s[i] == prev) {
                v.pb(t);
                t = "";
            }
            t += s[i];
            prev = s[i];
        }
        v.pb(t);
        int total = 0;
        vi fc, fd; int tc = 0, td = 0;
        trav(u, v) {
            // cout << "hi " << u << nl;
            if (u[0] == u.back()) {
                // must use a singular u[0]
                if (u[0] == 'A') a--;
                else b--;
                // can get anything in sz(u)/2 of each
                total += sz(u)/2;
            } else { // must use 2 if u want to switch
                if (u[0] == 'A') {
                    fc.pb(sz(u)/2);
                    tc += sz(u)/2;
                } else {
                    fd.pb(sz(u)/2);
                    td += sz(u)/2;
                }
            }
        }
        sort(all(fc));
        sort(all(fd));
        while (tc > c) {
            a--;
            b--;
            assert(sz(fc));
            total += fc.back()-1;
            tc -= fc.back();
            fc.pop_back();
        }
        while (td > d) {
            a--;
            b--;
            assert(sz(fd));
            total += fd.back()-1;
            td -= fd.back();
            fd.pop_back();
        }
        // dbg(a, b, c, d, tc, td, total);
        if (a < 0 || b < 0 || a != b) {
            cout << "NO" << nl;
            continue;
        }
        total -= a;
        if (c-tc + d-td - total != 0) {
            cout << "NO" << nl;
            continue;
        }
        cout << "YES" << nl;
    }
    return 0;
}
