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

bool comp(int a, int b) {
    return (a%2 < b%2);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    map<int, int> powToExp;
    int pow = 1;
    powToExp[0] = 20;
    F0R(i, 20) {
        powToExp[pow] = i;
        pow *= 2;
    }
    int a[2*n]; F0R(i, 2*n) cin >> a[i];
    if (n == 1) {
        int x = a[0]^a[1];
        cout << powToExp[x&-x] << nl;
    }
    FORd(ans, 0, 15) {
        vi c[1<<ans];
        F0R(i, 2*n) c[a[i]&((1<<ans)-1)].pb(i);
        bool ok = 1;
        int gr[2*n];
        F0R(i, 1<<ans) {
            if (sz(c[i])&1 || (sz(c[i])==2 && (c[i][0]^c[i][1])==1)) {
                ok = 0;
                break;
            } else {
                sort(c[i].begin(), c[i].end(), comp);
                cout << i << nl;
                trav(u, c[i]) cout << u << " "; cout << nl;
                F0R(j, sz(c[i])) gr[c[i][j]] = c[i][sz(c[i])-1-j];
            }
        }
        if (ok) {
            int cur = 0;
            cout << ans << nl;
            F0R(i, n) {
                cur = gr[cur];
                cout << cur+1 << " ";
                cur ^= 1;
                cout << cur+1 << " ";
            }
            cout << nl;
            return 0;
        }
    }
    return 0;
}
