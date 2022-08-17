/*
ID: lucasxi1
TASK: msquare
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

map<string, string> dist;

int main() {
    freopen("msquare.in", "r", stdin);
    freopen("msquare.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    char a[8]; F0R(i, 8) cin >> a[i];
    string s = "";
    F0R(i, 4) s += a[i];
    F0Rd(i, 4) s += a[4+i];
    // run bfs
    string root = "12348765";
    queue<string> q; q.push(root);
     dist[root] = "";
    while (!q.empty()) {
        string t = q.front(); q.pop();
        string d = dist[t];
        // dbg(t, d);
        // now try all 3 ops
        string tmp = t.substr(4) + t.substr(0, 4);
        if (!dist.count(tmp)) {
            q.push(tmp);
            dist[tmp] = d+'A';
        }
        tmp = t[3] + t.substr(0, 3) + t[7] + t.substr(4, 3);
        if (!dist.count(tmp)) {
            q.push(tmp);
            dist[tmp] = d+'B';
        }
        tmp = "";
        int b[8] = {0, 5, 1, 3, 4, 6, 2, 7};
        F0R(i, 8) tmp += t[b[i]];
        if (!dist.count(tmp)) {
            q.push(tmp);
            dist[tmp] = d+'C';
        }
    }
    string tmp = dist[s];
    dbg(s);
    cout << sz(tmp) << nl;
    F0R(i, sz(tmp)) {
        if (i && i%60 == 0) cout << nl;
        cout << tmp[i];
    } cout << nl;
    return 0;
}
