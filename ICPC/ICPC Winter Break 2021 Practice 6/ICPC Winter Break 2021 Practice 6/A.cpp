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
const ll INF = (1LL<<50) + 123;
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

const int MX = 2005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, w; cin >> n >> w;
    pi r[w+1]; F0R(i, w+1) r[i] = {0, -1};
    r[0] = {1, 0};
    ll pre_r[w+1]; F0R(i, w+1) pre_r[i] = 0;
    int s[n]; ll ans[n]; F0R(i, n) s[i] = ans[i] = 0;
    F0R(i, w) {
        int k; cin >> k;
        if (k == 0) continue;
        int p[k];
        F0R(j, k) {
            cin >> p[j];
            p[j]--;
            int score = s[p[j]];
            pre_r[score] += (i-r[score].s)*r[score].f;
            pre_r[score+1] += (i-r[score+1].s)*r[score+1].f;
            r[score].s = i;
            r[score+1].s = i;
        }
        F0R(j, k) {
            ans[p[j]] += pre_r[s[p[j]]];
            ans[p[j]] -= pre_r[s[p[j]]+1];
            r[s[p[j]]].f++;
            s[p[j]]++;
            if (r[s[p[j]]].f == 0) {
                r[s[p[j]]] = {1, i};
            }
        }
    }
    F0R(i, n) {
        pre_r[s[i]] += (ll)(w-r[s[i]].s)*r[s[i]].f;
        r[s[i]].s = w;
        ans[i] += pre_r[s[i]];
    }
    cout.precision(10);
    F0R(i, n) cout << fixed << (ld)ans[i]/w << nl;
    return 0;
}
