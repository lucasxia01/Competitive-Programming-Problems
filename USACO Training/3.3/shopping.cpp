/*
ID: lucasxi1
TASK: shopping
LANG: C++                 
*/
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

int s, b;
vector<pair<vi, int> > offers(100);
vi basket(1000, 0);
vi price(1000, INF);
vi mapping;
int total = 1;
vi mults;

int trans(int x, int i) {
    vi v;
    trav(m, mults) {
        v.pb(x/m); x%= m;
    }
    int j = 0;
    trav(c, mapping) {
        v[j] = min(v[j]+offers[i].f[c], basket[c]);
        j++;
    }
    j = 0;
    int ret = 0;
    trav(m, mults) {
        ret += v[j]*m;
        j++;
    }
    return ret;
}

int trans2(int x, int C) {
    vi v;
    trav(m, mults) {
        v.pb(x/m); x%= m;
    }
    int j = 0;
    trav(c, mapping) {
        if (c == C) v[j] = min(v[j]+1, basket[c]);
        j++;
    }
    j = 0;
    int ret = 0;
    trav(m, mults) {
        ret += v[j]*m;
        j++;
    }
    return ret;
}

void log(int x) {
    vi v;
    trav(m, mults) {
        v.pb(x/m); x%= m;
    }
    trav(m, mapping) cout << m << " "; cout << nl;
    trav(vv, v) cout << vv << " "; cout << nl;
}

int main() {
    freopen("shopping.in", "r", stdin);
    freopen("shopping.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> s;
    F0R(i, s) {
        int n; cin >> n;
        vi tmp(1000, 0);
        F0R(j, n) {
            int c, k; cin >> c >> k;
            tmp[c] = k;
        }
        offers[i].f = tmp;
        cin >> offers[i].s;
    }
    cin >> b;
    
    F0R(i, b) {
        int c, k, p; cin >> c >> k >> p;
        basket[c] = k;
        mults.pb(total);
        total *= (k+1);
        price[c] = p;
        mapping.pb(c);
    }
    reverse(all(mults));
    reverse(all(mapping));
    // now just knapsack to victory
    int dp[total]; F0R(i, total) dp[i] = INF;
    dp[0] = 0;
    F0R(i, s) { // try adding to every state
        F0R(j, total) {
            if (dp[j] == INF) continue;
            // log(j);
            // log(trans(j, i));
            // dbg(i, j, trans(j, i));
            ckmin(dp[trans(j, i)], dp[j]+offers[i].s);
        }
    }
    // now try each individual
    trav(c, mapping) {
        F0R(j, total) {
            if (dp[j] == INF) continue;
            // log(j);
            // log(trans2(j, c));
            // dbg(c, j, trans2(j, c));
            ckmin(dp[trans2(j, c)], dp[j]+price[c]);
        }
    }
    cout << dp[total-1] << nl;
    return 0;
}
