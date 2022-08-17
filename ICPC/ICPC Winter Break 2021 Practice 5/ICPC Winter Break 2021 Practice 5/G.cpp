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

const int MX = 3005;
struct P {
    int x, y;
    bool operator<(const P& o) const { return tie(x, y) < tie(o.x, o.y); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    P a[n]; F0R(i, n) cin >> a[i].x >> a[i].y;
    int m; cin >> m;
    P b[m]; F0R(i, m) cin >> b[i].x >> b[i].y;
    if (n != m) {
        cout << "no" << nl;
        return 0;
    }
    map<int, int> f;
    set<int> v; F0R(i, n) v.insert(a[i].x);
    int cnt = 0; trav(u, v) f[u] = cnt++;
    F0R(i, n) a[i].x = f[a[i].x];
    v.clear(); f.clear();
    
    F0R(i, n) v.insert(a[i].y);
    cnt = 0; trav(u, v) f[u] = cnt++;
    F0R(i, n) a[i].y = f[a[i].y];
    v.clear(); f.clear();
    
    F0R(i, m) v.insert(b[i].x);
    cnt = 0; trav(u, v) f[u] = cnt++;
    F0R(i, m) b[i].x = f[b[i].x];
    v.clear(); f.clear();
    
    F0R(i, m) v.insert(b[i].y);
    cnt = 0; trav(u, v) f[u] = cnt++;
    F0R(i, m) b[i].y = f[b[i].y];
    v.clear(); f.clear();
    // now rotate b and check if points are same
    set<P> s; F0R(i, n) s.insert(a[i]);
//    F0R(i, n) dbg(a[i].x, a[i].y);
    F0R(i, 4) {
        bool ok = 1;
        F0R(j, m) {
            swap(b[j].x, b[j].y);
            b[j].y = n/2-1-b[j].y;
//            dbg(b[j].x, b[j].y);
            if (s.find(b[j]) == s.end()) ok = 0;
        }
//        dbg();
        if (ok) { cout << "yes" << nl; return 0; }
    }
    cout << "no" << nl;
    return 0;
}
