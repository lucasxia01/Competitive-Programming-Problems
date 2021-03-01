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
#include <iomanip>
#include <ctime>

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

struct State {
    char x; int y;
    vector<pair<char, int> > steps;
};

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        ll m, n; cin >> m >> n;
        pl a[n];
        vpl v;
        F0R(i, n) {
            cin >> a[i].f >> a[i].s;
            if (a[i].f <= a[i].s) {
                v.pb({a[i].s, a[i].f});
                v.pb({a[i].s+m, a[i].f+m});
            } else v.pb({a[i].s+m, a[i].f});
        }
        if (n > m) {
            cout << "NO" << nl;
            continue;
        }
        sort(all(v));
        map<ll, ll> s;
        bool ok = 1;
        trav(u, v) {
            auto w = s.upper_bound(u.s);
            if (w == s.begin()) {
                if (w != s.end() && w->f == u.s+1) {
                    ll nxtr = w->s;
                    s.erase(w);
                    s.insert({u.s, nxtr});
                } else s.insert({u.s, u.s});
            } else {
                auto nxt = w;
                w--;
                ll l = w->f, r = w->s;
                // dbg(u.s, u.f, l, r);
                if (u.s <= r+1) {
                    if (r >= u.f) {
                        ok = 0;
                        break;
                    }
                    s.erase(w);
                    if (nxt != s.end() && nxt->f == r+2) {
                        ll nxtr = nxt->s;
                        s.erase(nxt);
                        s.insert({l, nxtr});
                    } else s.insert({l, r+1});
                } else {
                    if (nxt != s.end() && nxt->f == u.s+1) {
                        ll nxtr = nxt->s;
                        s.erase(nxt);
                        s.insert({u.s, nxtr});
                    } else s.insert({u.s, u.s});
                }
            }
        }
        cout << (ok ? "YES":"NO") << nl;
    }
    return 0;
}
