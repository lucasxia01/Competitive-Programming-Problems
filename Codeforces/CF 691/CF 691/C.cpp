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

const int MX = 100*100+5;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int a[n][n]; F0R(i, n) F0R(j, n) cin >> a[i][j];
        string s; cin >> s;
        int crds[3] = {0, 0, 0};
        int dirs[3] = {0, 1, 2};
        F0R(i, m) {
            if (s[i] == 'U') {
                crds[0]--;
            } else if (s[i] == 'D') {
                crds[0]++;
            } else if (s[i] == 'L') {
                crds[1]--;
            } else if (s[i] == 'R') {
                crds[1]++;
            } else if (s[i] == 'I') {
                swap(crds[1], crds[2]);
                swap(dirs[1], dirs[2]);
            } else if (s[i] == 'C') {
                swap(crds[0], crds[2]);
                swap(dirs[0], dirs[2]);
            }
        }
        int ans[n][n];
        F0R(i, n) F0R(j, n) {
            a[i][j]--;
            int cur[3] = {i, j, a[i][j]};
            int nCrds[3];
            F0R(k, 3) nCrds[k] = ((crds[k]+cur[dirs[k]])%n+n)%n;
            ans[nCrds[0]][nCrds[1]] = nCrds[2]+1;
        }
        F0R(i, n) {
            F0R(j, n) cout << ans[i][j] << " ";
            cout << nl;
        }
        cout << nl;
    }
    return 0;
}
