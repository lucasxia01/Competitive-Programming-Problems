#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // compute all possible differences in pows of 2
    map<int, pi> diffs;
    F0R(i, 31) {
        F0R(j, 31) {
            if (i == j) continue;
            int diff = (1<<i)-(1<<j);
            diffs[diff] = {i, j};
        }
    }
    int t = 1; 
    cin >> t;
    while (t--) {
        int n; cin >> n;
        int a[n]; F0R(i, n) cin >> a[i];
        // compute avg
        ll sum = 0;
        F0R(i, n) sum += a[i];
        if (sum%n) {
            cout << "NO" << nl;
            continue;
        }
        int avg = sum/n;
        bool ok = 1;
        // compute all things
        vi b, c;
        F0R(i, n) {
            if (a[i] == avg) continue;
            if (diffs.find(a[i]-avg) == diffs.end()) {
                ok = 0;
                break;
            }
            pi cur = diffs[a[i]-avg];
            b.pb(cur.f);
            c.pb(cur.s);
        }
        sort(all(b)); sort(all(c));
        F0R(i, sz(b)) {
            if (b[i] != c[i]) {
                ok = 0;
                break;
            }
        }
        cout << (ok?"YES":"NO") << nl;
    }
    return 0;
}
