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

const int MX = 100;
int n, k, t;
int p[MX][MX];
int c[MX][MX];
int trace[MX*MX+1];

bool solve(int l = 0) {
    if (l == n) {
        // check the trace
        int tr = 0;
//        F0R(i, n) {
//            F0R(j, n) cout << p[i][j] << " ";
//            cout << endl;
//        }
        F0R(i, n) {
            tr += p[i][i];
        }
        trace[tr] = 1;
//        if (tr == k) {
//            cout << "Case #" << t+1 << ": ";
//            cout << "POSSIBLE\n";
//            F0R(i, n) {
//                F0R(j, n) cout << p[i][j] << " ";
//                cout << endl;
//            }
//            return 1;
//        }
        return 0;
    }
    do {
        bool ok = true;
        F0R(i, n) if (c[i][p[l][i]-1]) {
            ok = false;
            break;
        }
        if (!ok) continue;
        F0R(i, n) c[i][p[l][i]-1] = 1;
        if (solve(l+1)) return 1;
        F0R(i, n) c[i][p[l][i]-1] = 0;
    } while (next_permutation(p[l], p[l]+n));
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for (; t < T; t++) {
        cin >> n >> k;
        F0R(j, n) F0R(i, n) p[j][i] = i+1;
        F0R(j, n) F0R(i, n) c[j][i] = 0;
        if (!solve()) {
        cout << "Case #" << t+1 << ": IMPOSSIBLE\n";
        }
    }
    for (int i = n; i <= n*n; i++) {
        if (!trace[i]) cout << i << endl;
    }
    return 0;
}
