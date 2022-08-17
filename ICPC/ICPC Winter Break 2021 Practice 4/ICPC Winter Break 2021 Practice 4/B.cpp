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
        int b, c; cin >> b >> c;
        vector<pair<time_t, int> > times;
        F0R(i, b) {
            string code, s1, s2, e1, e2;
            cin >> code >> s1 >> s2 >> e1 >> e2;
//            dbg(e1, e2);
            struct tm tm{};
            stringstream ss(s1+" "+s2);
            ss >> get_time(&tm, "%Y-%m-%d %H:%M");
            time_t t = mktime(&tm);
            struct tm tm1{};
            stringstream ss1(e1+" "+e2);
            ss1 >> get_time(&tm1, "%Y-%m-%d %H:%M");
            time_t t1 = mktime(&tm1);
            t1 += c*60;
            times.pb({t, 1});
            times.pb({t1, -1});
//            dbg(t, t1);
        }
        sort(all(times));
        int cnt = 0;
        int ans = 0;
        trav(t, times) {
            cnt+=t.s;
            ckmax(ans, cnt);
        }
        cout << ans << nl;
    }
    
    return 0;
}
