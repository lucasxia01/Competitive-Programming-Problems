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

set<int> d(ll x) {
    set<int> v;
    while (x) {
        if (x%10 >= 2) v.insert(x%10);
        x/=10;
    }
    return v;
}

ll N;

int greedy(ll x) {
    int ans = 0;
    while (x < N) {
        set<int> s = d(x);
        if (sz(s) == 0) return -1;
        auto it = --s.end();
        x *= *it;
        ans++;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; ll x; cin >> n >> x;
    set<int> s = d(x);
    if (sz(s) == 0) {
        cout << -1 << nl;
        return 0;
    }
    // else greedy?
    N = 1; F0R(i, n-1) N *= 10;
    queue<pl> q; q.push({x, 0});
    // run bfs for a while, then greedy city
    int ans = 50;
    set<ll> m;
    while (1) {
        if (q.empty()) {
            cout << -1 << nl;
            return 0;
        }
        pl p = q.front(); q.pop();
        if (m.find(p.f) != m.end()) continue;
        m.insert(p.f);
        // dbg(p.f, p.s);
        if (p.f >= N) {
            ans = p.s;
            break;
        }
        set<int> s = d(p.f);
        trav(ss, s) {
            q.push({p.f*ss, p.s+1});
        }
    }
    // dbg(sz(q));
    // while (!q.empty()) {
    //     pl p = q.front(); q.pop();
    //     int ret = greedy(p.f);
    //     if (ret == -1) continue;
    //     ckmin(ans, ret + (int)p.s);
    // }
    cout << ans << nl;
    return 0;
}
