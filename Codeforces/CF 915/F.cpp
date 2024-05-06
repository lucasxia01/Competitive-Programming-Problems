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
        int n; cin >> n;
        vpi a(n);
        F0R(i, n) cin >> a[i].f;
        F0R(i, n) a[i].s = i+1;
        // find where each thing belongs
        vector<array<int, 4> > v;
        F0R(i, n) {
            if (a[i].f == a[i].s) continue;
            v.pb({a[i].f, (a[i].f > a[i].s), i, (a[i].f < a[i].s)});
            v.pb({a[i].s, (a[i].f < a[i].s), i, (a[i].f < a[i].s)});
        }
        sort(all(v));
        map<pi, int> m;
        set<pi> active;
        int j = 0;
        FOR(i, 1, n) {
            while (j < sz(v) && v[j][0] == i && v[j][1] == 0) {
                active.insert({v[j][2], v[j][3]});
                j++;
            }
            // check if there's 2 things here
            if (sz(active) == 2) {
                pi x = *active.begin();
                pi y = *next(active.begin());
                if (x.s != y.s) { // opposite facing
                    m[{x.f, y.f}]++;
                }
            }
            while (j < sz(v) && v[j][0] == i && v[j][1] == 1) { // endings of ranges
                active.erase({v[j][2], v[j][3]});
                j++;
            }
        }
        // if m is empty, then all we can do is ruin something sadly
        if (sz(m) == 0) {
            F0R(i, n) assert(a[i].f == i+1);
            cout << n-2 << nl;
        } else {
            // swap the last two
            pi best(-1, -1);
            int hi = 0;
            trav(p, m) {
                if (p.s > hi) {
                    hi = p.s;
                    best = p.f;
                }
            }
            swap(a[best.f], a[best.s]);
            // count the answer
            hi = 0;
            int ans = 0;
            F0R(i, n) {
                if (a[i].f == i+1 && hi == i) {
                    ans++;
                }
                ckmax(hi, a[i].f);
            }
            cout << ans << nl;
        }
        
    }
    return 0;
}
