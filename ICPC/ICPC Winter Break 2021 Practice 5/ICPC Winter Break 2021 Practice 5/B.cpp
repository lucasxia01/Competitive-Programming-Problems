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

const int MX = 50005;

int par[MX], sz[MX];
int find(int i) {
    return (i==par[i]?i:par[i]=find(par[i]));
}
void merge(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    par[b] = a;
}

struct Stone {
    int x, y, w, h, i;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    Stone s[n];
    map<int, vpi > mH, mV;
    F0R(i, n) {
        cin >> s[i].x >> s[i].y >> s[i].w >> s[i].h;
        s[i].i = i;
        par[i] = i;
        sz[i] = 1;
        if (mH.find(s[i].x+s[i].w) == mH.end()) {
            vpi temp;
            mH[s[i].x+s[i].w] = temp;
        }
        mH[s[i].x+s[i].w].pb({s[i].y, i});
        mH[s[i].x+s[i].w].pb({s[i].y+s[i].h, i});
        
        if (mV.find(s[i].y+s[i].h) == mV.end()) {
            vpi temp;
            mV[s[i].y+s[i].h] = temp;
        }
        mV[s[i].y+s[i].h].pb({s[i].x, i});
        mV[s[i].y+s[i].h].pb({s[i].x+s[i].w, i});
    }
    trav(a, mH) sort(all(a.s));
    F0R(i, n) {
        if (mH.find(s[i].x) == mH.end()) continue;
        vpi v = mH[s[i].x];
        pi p = {s[i].y, -1};
        auto it = lower_bound(all(v), p);
        while (it != v.end()) {
            if (it->f > s[i].y+s[i].h) break;
            merge(s[i].i, it->s);
            it++;
        }
        if (it != v.end()) { // see if something completely overlaps
            if (s[it->s].y < s[i].y) merge(it->s, i);
        }
    }
    trav(a, mV) sort(all(a.s));
    F0R(i, n) {
        if (mV.find(s[i].y) == mV.end()) continue;
        vpi v = mV[s[i].y];
        pi p = {s[i].x, -1};
        auto it = lower_bound(all(v), p);
        while (it != v.end()) {
            if (it->f > s[i].x+s[i].w) break;
            merge(s[i].i, it->s);
            it++;
        }
        if (it != v.end()) { // see if something completely overlaps
            if (s[it->s].x < s[i].x) merge(it->s, i);
        }
    }
    ll ans[n]; F0R(i, n) ans[i] = 0;
    F0R(i, n) {
        ans[find(i)] += (ll)s[i].w*s[i].h;
    }
    ll best = 0;
    F0R(i, n) ckmax(best, ans[i]);
    cout << best << nl;
}
