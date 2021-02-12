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

const int MX = 1<<20;

map<string, vector<string> > g, gr;
set<string> used;
vector<string> order, component;

void dfs1(string v) {
    used.insert(v);
    for (size_t i=0; i<g[v].size(); ++i)
        if (used.find(g[v][i]) == used.end())
            dfs1(g[v][i]);
    order.push_back (v);
}

void dfs2(string v) {
    used.insert(v);
    component.push_back (v);
    for (size_t i=0; i<gr[v].size(); ++i)
        if (used.find(gr[v][i]) == used.end())
            dfs2(gr[v][i]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string s;
    getline(cin, s);
    string a[n];
    map<string, pair<string, set<string> > >  m;
    F0R(i, n) {
        getline(cin, s);
        s += " ";
        int pos = 0;
        string token;
        int x = 0;
        string t = "";
        string lang = "";
        set<string> temp1;
        while ((pos = s.find(" ")) != string::npos) {
            token = s.substr(0, pos);
            if (x == 0) {
                a[i] = token;
                t = token;
                x++;
            } else {
                if (x == 1) {
                    lang = token;
                }
                temp1.insert(token);
                x++;
            }
            s.erase(0, pos + 1);
        }
        m.insert({t, {lang, temp1}});
    }
    F0R(i, n) {
        string lang = m[a[i]].f;
        F0R(j, n) {
            if (i == j) continue;
            if (m[a[j]].s.find(lang) != m[a[j]].s.end()) {
                g[a[i]].pb(a[j]);
                gr[a[j]].pb(a[i]);
//                dbg(a[i], a[j]);
            }
        }
    }

    for (int i=0; i<n; ++i)
        if (used.find(a[i]) == used.end())
            dfs1(a[i]);
    used.clear();
    int ans = n;
    for (int i=0; i<n; ++i) {
        string v = order[n-1-i];
        if (used.find(v) == used.end()) {
            dfs2(v);
            ckmin(ans, n-(int)component.size());
            component.clear();
        }
    }
    cout << ans << nl;
    return 0;
}
