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
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        string s, t; cin >> s >> t;
        int cur1 = 0, cur2 = 0;
        vpi a, b;
        F0R(i, n) {
            if (s[i] == '1') {
                cur1++;
                if (i == n-1 || s[i+1] == '0') {
                    a.pb({i, cur1});
                    cur1 = 0;
                }
            }

            if (t[i] == '1') {
                cur2++;
                if (i == n-1 || t[i+1] == '0') {
                    b.pb({i, cur2});
                    cur2 = 0;
                }
            }
        }
        if (sz(a) != sz(b) || s[0] != t[0] || s[n-1] != t[n-1]) {
            cout << -1 << nl;
            continue;
        }

        // trav(aa, a) {
        //     dbg(aa.f, aa.s);
        // }

        // trav(bb, b) {
        //     dbg(bb.f, bb.s);
        // }
        ll ans = 0;
        F0R(i, sz(a)) {
            int tmp = 0;
            pi aa = a[i];
            pi bb = b[i];
            tmp += abs(bb.f - aa.f);
            tmp += abs((aa.f - aa.s) - (bb.f - bb.s));
            ans += tmp;
        }
        cout << ans << nl;
    }
    return 0;
}
