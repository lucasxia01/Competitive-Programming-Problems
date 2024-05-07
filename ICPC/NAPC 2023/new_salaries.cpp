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
    int n; cin >> n;
    pair<ld, ld> r[n];
    ld pref[4][n+1];
    rep(j, 0, 4) pref[j][0] = 0;
    rep(i, 0, n) {
        string s, t; cin >> s >> t;
        ld a = stod(s), b = stod(t);
        r[i] = {a, b};
        ld tmp = 0;
        if (b-a) tmp = (ld)1/(b-a);
        rep(j, 0, 4) {
            pref[j][i+1] = pref[j][i]+tmp;
            tmp *= b;
        }
    }
    ld ans = 0;
    ld sum = 0;
    int j = 0;
    rep(i, 0, n) {
        ld L = r[i].f, R = r[i].s;
        ld cur = (L + R)/2;
        ans += (cur*i - sum)/n * 1/n;
        sum += cur;
        if (L == R) continue;
        while (j < n && r[j].s <= L) j++;
        if (j >= i) continue;
        ld denom = (pref[3][i]-pref[3][j]) - 3*L*(pref[2][i]-pref[2][j]) 
                            + 3*L*L*(pref[1][i]-pref[1][j]) - L*L*L*(pref[0][i]-pref[0][j]);
        dbg(denom, R-L);
        ans += denom / (R-L) * 1/3 * 1/n * 1/n;
    }
    cout.precision(10);
    cout << fixed << ans << endl;
    return 0;
}
