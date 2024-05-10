/*
ID: lucasxi1
TASK: race3
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
vector<vi> gr;

vector<bool> vis1;
void dfs1(int v) {
    if (vis1[v]) return;
    dbg("visiting", v);
    vis1[v] = 1;
    trav(u, gr[v]) {
        dfs1(u);
    }
}

int main() {
    freopen("race3.in", "r", stdin);
    freopen("race3.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n = 0;
    vpi edges;
    while (1) {
        int x; cin >> x;
        dbg(x);
        vi v;
        while (x >= 0) {
            v.pb(x);
            edges.pb({n, x});
            cin >> x;
        }
        gr.pb(v);
        if (x == -1) break;
        n++;
    }
    dbg(n);
    // now just run dfs from 0 to n while removing each node
    vi ans1, ans2;
    FOR(i, 1, n-2) {
        // remove i from the graph and see if you can still reach n from 0
        vis1.assign(n, 0);
        vi tmp = gr[i];
        gr[i].clear();
        dbg("dfsing from", i);
        dfs1(0);
        gr[i] = tmp;
        if (!vis1[n-1]) ans1.pb(i);
        else continue;
        // remove i from graph and see if you can still reach n from 0 in the undirected graph
        // just check if anything not visited points to things visited
        assert(vis1[i]);
        vis1[i] = 0;
        // check if there's any edge from not visited to visited
        bool ok = 1;
        F0R(j, n) {
            if (vis1[j]) continue;
            trav(u, gr[j]) {
                if (vis1[u]) {
                    ok = 0;
                    break;
                }
            }
        }
        if (ok) ans2.pb(i);
    }
    cout << sz(ans1);
    trav(i, ans1) cout << " " << i; cout << nl;
    cout << sz(ans2);
    trav(i, ans2) cout << " " << i; cout << nl;
    return 0;
}
