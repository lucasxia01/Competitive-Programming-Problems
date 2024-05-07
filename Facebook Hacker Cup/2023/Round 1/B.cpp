#include <bits/stdc++.h>

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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){
	c << "(" << v.fi << "," <<v.se <<")"; return c;
}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){
	out << "{ ";
	trav(x,c) out<<x<<" ";
	out<<"}"; return out;
}
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

map<pi, pair<bool, vi>> m;

pair<bool, vi> solve(int x, int sum) {
    // dbg(x, sum);
    if (m.count ({x, sum})) {
        return m[{x, sum}];
    }
    if (sum < 0) return {0, {}};
    if (x == 1) {
        vi v(sum, 1);
        return {1, v};
    }
    vi ans;
    bool a = 0;
    for (int i = 1; i*i <= x; i++) {
        if (x%i == 0) {
            auto [b, ret] = solve(x/i, sum-i);
            if (b) {
                ret.pb(i);
                if (!a) {
                    ans = ret;
                    a = 1;
                } else if (sz(ans) > sz(ret)) ans = ret;
                
            }
            auto [c, ret2] = solve(i, sum-(x/i));
            b = c; ret = ret2;
            if (b) {
                ret.pb(x/i);
                if (!a) {
                    a = 1;
                    ans = ret;
                } else if (sz(ans) > sz(ret)) {
                    ans = ret;
                }
            }
        }
    }
    m[{x, sum}] = {a, ans};
    return {a, ans};
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    FOR(tt, 1, t) {
        cout << "Case #" << tt << ": ";
        int p; cin >> p;
        auto [b, ans] = solve(p, 41);
        if (!b) {
            cout << -1 << nl;
            continue;
        }
        cout << sz(ans) << " ";
        trav(aa, ans) cout << aa << " ";
        cout << nl;
    }
    return 0;
}
