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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n, m, k; cin >> n >> m >> k;
        vector<array<int, 3> > v;
        F0R(i, m) {
            int l, r; cin >> l >> r;
            v.pb({l, 1, i});
            v.pb({r+1, 0, i});
        }
        sort(all(v));
        // either 2 non intersecting ones
        set<int> s;
        int ptr = 0;
        int solo_cnt[m]; F0R(i, m) solo_cnt[i] = 0;
        map<pi, int> double_cnt;
        int base = 0;
        FOR(i, 1, n) {
            while (ptr < sz(v) && v[ptr][0] == i) {
                if (v[ptr][1]) s.insert(v[ptr][2]);
                else s.erase(v[ptr][2]);
                ptr++;
            }
            if (sz(s) == 2) {
                int u = *s.begin();
                int v = *next(s.begin());
                double_cnt[{u, v}]++;
            } else if (sz(s) == 1) {
                solo_cnt[*s.begin()]++;
            } else if (sz(s) == 0) base++;
        }
        int ans = 0;
        trav(p, double_cnt) {
            int u = p.f.f, v = p.f.s;
            ckmax(ans, p.s + solo_cnt[u] + solo_cnt[v]);
        }
        // or just by themselves
        sort(solo_cnt, solo_cnt+m);
        ckmax(ans, solo_cnt[m-2]+solo_cnt[m-1]);
        cout << base+ans << nl;
    }
    return 0;
}
