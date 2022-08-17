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
    int n, k; cin >> n >> k;
    if (n < 1800) { // sit at one spot until we get signal
        ll x;
        int cnt = 0;
        while (1) {
            cout << "? " << 1 << nl;
            cout.flush();
            cin >> x;
            if (x != k) break;
            cnt++;
            if (cnt*2 >= n) break;
        }
        if (x > k) cout << "! " << (n-cnt)+1 << nl;
        else if (x < k) cout << "! " << cnt+1 << nl;
        else {
            if (n%2) {
                cout << "! " << 1 << nl;
            } else {
                // either 1 or cnt+1
                cout << "? " << 2 << nl;
                cout.flush();
                cin >> x;
                if (x < k) cout << "! " << cnt+1 << nl;
                else cout << "! " << 1 << nl;
            }
        }
    } else { // else jump around to m spots until we get a signal
        // picking the spots
        int m = 301, M = m+3;
        vi spots;
        F0R(i, m) spots.pb(1 + i*n/m);
        ll x;
        int cnt = 0;
        int pos = 1;
        while (1) {
            pos = spots[cnt%m];
            cout << "? " << pos << nl;
            cout.flush();
            cin >> x;
            if (x != k) break;
            cnt++;
        }
        // now we wait ~m down the line to see whats going on
        if (x > k) pos = (pos-1+M)%n+1;
        else pos = (pos-1-M+n)%n+1;
        cnt++;
        while (1) { // this should be at most m iters
            cout << "? " << pos << nl;
            cout.flush();
            cin >> x;
            if (x != k) break;
            cnt++;
        }
        if (x > k) cout << "! " << (pos-1-cnt+n)%n+1 << nl;
        else if (x < k) cout << "! " << (pos-1+cnt)%n+1 << nl;
        else assert(0);
    }
    return 0;
}
