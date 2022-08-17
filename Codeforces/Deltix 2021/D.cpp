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
    int n, m, p; cin >> n >> m >> p;
    string s[n]; F0R(i, n) cin >> s[i];
    string best = ""; int M = 0; F0R(i, m) best += '0';
    // now we pick 20 random ones
    F0R(ITER, 20) {
        string t = s[rng()%n];
        // dbg(t);
        int b[1<<p]; F0R(i, 1<<p) b[i] = 0;
        vi v; F0R(i, m) if (t[i] == '1') v.pb(i);
        F0R(i, n) {
            int cur = 0;
            F0R(j, sz(v)) if (s[i][v[j]] == '1') cur += (1<<j);
            // dbg(cur);
            b[cur]++;
        }
        int c[1<<p]; F0R(i, 1<<p) c[i] = 0;
        F0Rd(i, 1<<p) {
            int cnt = 0; F0R(j, p) if (i&(1<<j)) cnt++;
            int mask = ((1<<p)-1)^i;
            for (int s=mask; s; s=(s-1)&mask) {
                c[i] += b[s|i];
            }
            c[i] += b[i];
            // dbg(i, c[i]);
            if (c[i]*2 >= n) {
                if (ckmax(M, cnt)) {
                    string r = ""; F0R(k, m) r += '0';
                    F0R(j, sz(v)) if (i&(1<<j)) r[v[j]] = '1';
                    best = r;
                }
            }
        }
    }
    cout << best << nl;
    return 0;
}
