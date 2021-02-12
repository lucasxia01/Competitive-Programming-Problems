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
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    ll a[2*n][2*n];
    a[0][0] = a[n-1][n-1] = 0;
    FOR(i, 1, 2*n-3) {
        F0R(j, i+1) {
            if (j%2) a[j][i-j] = (1LL<<(i-1));
            else a[j][i-j] = 0;
        }
    }
    F0R(i, n) {
        F0R(j, n) cout << a[i][j] << " ";
        cout << nl;
    }
    fflush(stdout);
    cout.flush();
    int q; cin >> q;
    while (q--) {
        ll sum = 0; cin >> sum;
        int curX = 1, curY = 1;
        cout << curX << " " << curY << nl;
        F0R(i, 2*n-3) {
            if (sum&(1LL<<i)) {
                if (curX%2) curX++;
                else curY++;
            } else {
                if (curX%2) curY++;
                else curX++;
            }
            cout << curX << " " << curY << nl;
        }
        cout << n << " " << n << nl;
        
        fflush(stdout);
        cout.flush();
    }
    return 0;
}
