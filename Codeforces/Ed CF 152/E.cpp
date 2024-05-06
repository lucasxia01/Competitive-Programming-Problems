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

const int MX = 1e6+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n]; F0R(i, n) cin >> a[i];
    int nxtL[n], prevL[n], nxtS[n], prevS[n];
    stack<pi> s; 
    s.push({MX+1, n});
    F0Rd(i, n) {
        while (a[i] > s.top().f) s.pop();
        nxtL[i] = s.top().s;
        s.push({a[i], i});
    }
    while (!s.empty()) s.pop();

    s.push({-1, n});
    F0Rd(i, n) {
        while (a[i] < s.top().f) s.pop();
        nxtS[i] = s.top().s;
        s.push({a[i], i});
    }
    while (!s.empty()) s.pop();

    s.push({MX+1, -1});
    F0R(i, n) {
        while (a[i] > s.top().f) s.pop();
        prevL[i] = s.top().s;
        s.push({a[i], i});
    }
    while (!s.empty()) s.pop();

    s.push({-1, -1});
    F0R(i, n) {
        while (a[i] < s.top().f) s.pop();
        prevS[i] = s.top().s;
        s.push({a[i], i});
    }

    // now dac
    ll ans = 0;
    F0R(i, n) {
        int L = nxtS[i], R = prevS[i];
        int prevr = i;
        int l = i+1;
        while (l < L) {
            int r = prevL[l];
            dbg(l, r);
            if (r <= R) {
                dbg(i, prevr, R, L, l);
                ans += (ll)(i - R) * (L-l);
                l = L;
            } else {
                int nxtl = nxtL[r];
                dbg(i, prevr, r, min(L, nxtl), l);
                ans += (ll)(i - r) * (min(L, nxtl) - l);
                l = nxtl;
            }
            prevr = r;
            
        }
    }
    cout << ans << nl;
    return 0;
}
