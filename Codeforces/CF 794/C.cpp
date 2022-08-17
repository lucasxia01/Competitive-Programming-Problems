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

pair<bool, pi> f(string& s) {
    int n = sz(s)/2;
    int max_before = 0, p1 = 0, max_rbefore = 0, p2 = 2*n-1;
    int cnt = 0;
    F0R(i, 2*n) {
        if (s[i] == '(') cnt++;
        else cnt--;
        // dbg(i, cnt);
        if (ckmax(max_before, cnt)) p1 = i+1;
        if (cnt < 0) break;
    }
    cnt = 0;
    F0Rd(i, 2*n) {
        if (s[i] == ')') cnt++;
        else cnt--;
        if (ckmax(max_rbefore, cnt)) p2 = i-1;
        if (cnt < 0) break;
    }
    // dbg(p1, p2);
    string t = s;
    reverse(t.begin()+p1, t.begin()+(p2+1));
    dbg(t);
    bool ok = 1;
    cnt = 0;
    F0R(i, 2*n) {
        if (t[i] == '(') cnt++;
        else cnt--;
        if (cnt < 0) ok = 0;
    }
    s = t;
    return {ok, {p1+1, p2+1}};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        int cnt = 0;
        bool ok = 1;
        int pref[2*n];
        F0R(i, 2*n) {
            if (s[i] == '(') cnt++;
            else cnt--;
            pref[i] = cnt;
            if (cnt < 0) ok = 0;
        }
        if (ok) {
            cout << 0 << nl;
            continue;
        }
        string t = s;
        pair<bool, pi> ret = f(s);
        s = t;
        if (ret.f) {
            cout << 1 << nl;
            cout << ret.s.f << " " << ret.s.s << nl;
            continue;
        }
        // find max and mins
        int pos = max_element(pref, pref+(2*n))-pref;
        cout << 2 << nl;
        // flip up to pos
        cout << 1 << " " << pos+1 << nl;
        cout << pos+2 << " " << 2*n << nl;
    }
    return 0;
}
