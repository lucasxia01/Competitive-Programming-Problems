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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s; cin >> s;
    int n = (int)s.length();
    s+='$';
    string rev_str = "";
    vector<pair<int, string> > ans;
    vi p; p.pb(n);
    vector<bool> q; q.pb(1);
    F0Rd(i, n) {
        int m = (int)rev_str.length();
        int M = sz(p);
        bool b = M == 1 || (s[i] > s[p[M-2]]) || (s[i] == s[p[M-2]] && q.back());
//        cout << s[i] << ' ' << s[p[M-2]] << nl;
        if (m > 0 && s[i] == rev_str[m-1] && p[M-1] == i+1 && b) {
            rev_str.pop_back();
            q.pop_back();
            p.pop_back();
        } else {
            rev_str += s[i];
            q.pb(b);
            p.pb(i);
        }
        m = (int)rev_str.length();
        string t;
        if (m > 10) {
            string t2 = rev_str.substr(0, 2);
            string t1 = rev_str.substr(m - 5, 5);
            reverse(all(t1)); reverse(all(t2));
            t = t1+"..."+t2;
        } else {
            t = rev_str;
            reverse(all(t));
        }
        ans.pb({m, t});
    }
    F0Rd(i, sz(ans)) cout << ans[i].f << " " << ans[i].s << nl;
    return 0;
}
