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

const int MX = 500;

pi gr[MX][MX];
bool vis[MX];

vi solve(int i, int j) {
    vi ret;
    if (gr[i][j].s == -1) {
        assert(gr[i][j].f == 1);
        return ret;
    }
    vi l = solve(i, gr[i][j].s);
    vi r = solve(gr[i][j].s, j);
    trav(v, l) ret.pb(v);
    ret.pb(gr[i][j].s);
    trav(v, r) ret.pb(v);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string temp;
    map<string, int> s;
    string ss[n];
    F0R(i, n) {
        cin >> temp;
        ss[i] = temp;
        s[temp] = i;
    }
    F0R(i, n) F0R(j, n) {
        gr[i][j].f = INF;
        gr[i][j].s = -1;
    }
    F0R(i, n) {
        string t; cin >> t;
        int l; cin >> l;
        F0R(ll, l) {
            string st; cin >> st;
            while (cin >> st && st.back() == ',') {
                st.pop_back();
                gr[s[t]][s[st]].f = 1;
            }
            gr[s[t]][s[st]].f = 1;
        }
    }
    F0R(k, n) F0R(i, n) F0R(j, n) {
        if (ckmin(gr[i][j].f, gr[i][k].f+gr[k][j].f)) {
            gr[i][j].s = k;
        }
    }
    int ans = INF;
    F0R(i, n) {
        ckmin(ans, gr[i][i].f);
    }
    if (ans == INF) {
        cout << "SHIP IT" << nl;
        return 0;
    }
    F0R(i, n) {
        if (gr[i][i].f == ans) {
            vi v = solve(i, i);
            trav(vv, v) {
                cout << ss[vv] << " ";
            }
            cout << ss[i] << nl;
            return 0;
        }
    }
    assert(0);
    return 0;
}
