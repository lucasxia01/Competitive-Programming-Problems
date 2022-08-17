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

const int MX = 1e5+5;
ll c[3], C[3];
ll s[3];
vl k;
vector<pair<ll, pl> > v;
int n;

bool check(ll mid) {
    F0R(i, n) {
        bool ok = 0;
        trav(vv, v) {
            if (vv.f*k[i] < mid) continue;
            c[vv.s.f]--;
            c[vv.s.s]--;
            if (c[vv.s.f] < 0 || c[vv.s.s] < 0) {
                c[vv.s.f]++;
                c[vv.s.s]++;
                continue;
            }
            ok = 1;
            break;
        }
        if (!ok) return 0;
    }
    return 1;
}

bool vis[1<<20];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int total = 0;
    F0R(i, 3) { cin >> c[i]; C[i] = c[i]; total += c[i]; }
    F0R(i, 3) cin >> s[i];
    F0R(i, 3) F0R(j, 3) v.pb({s[i]+s[j], {i, j}});
    sort(all(v));
//    strav(vv, v) dbg(vv.f);
    n = total/2;
    int temp;
    F0R(i, n) { cin >> temp; k.pb(temp); }
    sort(all(k));
    ll lo = 0, hi = 2e9+5;
    while (lo < hi) {
        ll mid = (lo+hi)/2;
        F0R(i, 3) c[i] = C[i];
//        dbg(mid);
        if (check(mid)) lo = mid+1;
        else hi = mid;
    }
    cout << (lo+hi)/2-1 << nl;
    return 0;
}
