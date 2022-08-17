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

bool is_suffix(string a, string b) {
    if (sz(a) <= sz(b)) return 0;
    F0R(i, sz(b)) {
        if (a[sz(a)-sz(b)+i] != b[i]) return 0;
    }
    return 1;
}

map<string, vector<string> > M;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    F0R(i, n) {
        string s; cin >> s;
        int m; cin >> m;
        if (M.find(s) == M.end()) {
            vector<string> temp;
            M[s]= temp;
        }
        F0R(i, m) {
            string x; cin >> x;
            M[s].pb(x);
        }
    }
    cout << sz(M) << nl;
    trav(a, M) {
        vector<string> v = a.s;
        bool ok[sz(v)];
        F0R(i, sz(v)) ok[i] = 1;
        F0R(i, sz(v)) {
            F0R(j, sz(v)) {
                if (is_suffix(v[i], v[j])) {
                    ok[j] = 0;
                }
            }
        }
        set<string> t;
        F0R(i, sz(v)) if (ok[i]) t.insert(v[i]);
        cout << a.f << " " << sz(t) << ' ';
        trav(u, t) cout << u << " "; cout << nl;
    }
    return 0;
}
