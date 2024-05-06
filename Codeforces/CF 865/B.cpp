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

int query1(int x) {
    cout << "+ " << x << endl;
    cout.flush();
    int ret; cin >> ret;
    return ret;
}
int query2(int i, int j) {
    cout << "? " << i << " " << j << endl;
    cout.flush();
    int ret; cin >> ret;
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        query1(n+1);
        query1(n);
        //now try 1 with everything
        vpi v;
        FOR(i, 2, n) {
            int ret = query2(1, i);
            v.pb({ret, i});
        }
        sort(all(v));
        reverse(all(v));
        int end = v[0].s;
        int l = 1, r = n;
        vi order;
        while (l <= r) {
            order.pb(r); r--;
            if (l > r) break;
            order.pb(l); l++;
        }
        dbg(sz(order));
        // trav(o, order) cerr << o << " "; cerr << nl;
        vi ans(n, -3), ans2(n, -3);
        FOR(i, 1, n) {
            if (i != end) {
                int ret = query2(end, i);
                ans[i-1] = order[ret];
                ans2[i-1] = order[n-1-ret];
            }
        }
        dbg(end);
        ans[end-1] = order[0];
        ans2[end-1] = order[n-1];
        cout << "! ";
        trav(a, ans) cout << a << " ";
        trav(a, ans2) cout << a << " ";
        cout << endl;
        cout.flush();
        int ret; cin >> ret;
        if (ret == -2) break;
    }
    return 0;
}
