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

const int MX = 2e5+5;

int t = 0;
vi gr[MX];
int ans[MX];
bool hasB[MX];
int A = -1, B = -1;
int a = -1;
int maxD = -1;

void dfs0(int u, int p, int dep) {
    if (ckmax(maxD, dep)) a = u;
    trav(v, gr[u]) {
        if (v == p) continue;
        dfs0(v, u, dep+1);
    }
}

bool dfs1(int u, int p) {
    if (u == B) {
        hasB[u] = 1;
        return 1;
    }
    trav(v, gr[u]) {
        if (v == p) continue;
        if (dfs1(v, u)) {
            hasB[u] = 1;
            return 1;
        }
    }
    return 0;
}

// end at the deepest
void dfs(int u, int p) {
    ans[u] = ++t;
    int save = -1;
    trav(v, gr[u]) {
        if (v == p) continue;
        if (hasB[v]) {
            save = v;
            continue;
        }
        dfs(v, u);
        ++t;
    }
    if (save != -1) dfs(save, u);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    F0R(i, n-1) {
        int a, b; cin >> a >> b;
        gr[a].pb(b);
        gr[b].pb(a);
    }
    dfs0(1, -1, 0);
    A = a;
    maxD = -1;
    dfs0(A, -1, 0);
    B = a;
    dfs1(A, -1);
    dbg(A, B);
    dfs(A, -1);
    FOR(i, 1, n) cout << ans[i] << " ";
    cout << nl;
    return 0;
}
