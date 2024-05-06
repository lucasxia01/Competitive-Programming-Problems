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
    int n, m; cin >> n >> m;
    char a[n][m]; F0R(i, n) F0R(j, m) cin >> a[i][j];
    map<int, int> r[n];
    map<int, int> c[m];
    F0R(i, n) F0R(j, m) {
        r[i][a[i][j]]++;
        c[j][a[i][j]]++;
    }
    // now deletion time
    while (1) {
        bool ok = 0;
        vi rows, cols;
        F0R(i, n) {
            if (sz(r[i]) == 1 && r[i].begin()->s > 1) {
                rows.pb(i);
                ok = 1;
                
            }
        }
        F0R(j, m) {
            if (sz(c[j]) == 1 && c[j].begin()->s > 1) {
                cols.pb(j);
                ok = 1;
                
            }
        }
        trav(i, rows) {
            r[i].erase(r[i].begin());
            dbg("remove row", i);
            // remove this row
            F0R(j, m) {
                if (sz(c[j]) == 0) continue;
                c[j][a[i][j]]--;
                if (c[j][a[i][j]] == 0) c[j].erase(a[i][j]);
            }
        }
        trav(j, cols) {
            if (sz(c[j]) == 0) continue;
            c[j].erase(c[j].begin());
            dbg("remove col", j);
            F0R(i, n) {
                if (sz(r[i]) == 0) continue;
                r[i][a[i][j]]--;
                if (r[i][a[i][j]] == 0) r[i].erase(a[i][j]);
            }
        }
        if (!ok) break;
    }
    int ans = 0;
    F0R(i, n) trav(aa, r[i]) ans += aa.s;
    cout << ans << nl;
    return 0;
}
