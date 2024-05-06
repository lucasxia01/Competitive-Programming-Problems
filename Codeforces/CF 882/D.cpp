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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, q; cin >> n >> m >> q;
    string s; cin >> s;
    set<int> vis; F0R(i, n) vis.insert(i);
    vi rank(n, n+1);
    vi order;
    int cnt = 0;
    F0R(i, m) {
        int l, r; cin >> l >> r; l--; r--;
        auto cur = vis.lower_bound(l);
        while (cur != vis.end() && *cur <= r) {
            int val = *cur;
            rank[val] = cnt++;
            dbg(val, cnt);
            order.pb(val);
            vis.erase(cur);
            cur = vis.lower_bound(val+1);
        }
    }
    int ones = 0;
    F0R(i, n) if (s[i] == '1') ones++;
    int ans = 0;
    F0R(i, n) if (rank[i] < ones && s[i] == '1') ans++;
    dbg(ones, ans);
    while (q--) {
        int x; cin >> x; x--;
        if (s[x] == '1') {
            ones--;
            if (sz(order) >= ones+1 && s[order[ones]] == '1') ans--;
            if (rank[x] < ones) ans--;
            s[x] = '0';
        } else {
            ones++;
            if (sz(order) >= ones && s[order[ones-1]] == '1') ans++;
            if (rank[x] < ones) ans++;
            s[x] = '1';
        }
        dbg(ones, ans);
        cout << min(ones, sz(order))-ans << nl;
    }
    return 0;
}
