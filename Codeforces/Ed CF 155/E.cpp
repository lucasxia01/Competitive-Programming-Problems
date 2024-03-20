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

const int MX = 100+5;

vi gr[MX];
int c[MX];
int n;

void output() {
    FOR(i, 2, n) cout << c[i] << " ";
    cout << endl;
    cout.flush();
}

bool dfs2(int v, int col) {
    c[v] = col;
    if (sz(gr[v]) == 1 && col == 2) {
        return 0;
    }
    trav(u, gr[v]) {
        if (!dfs2(u, 3-col)) return 0;
    }
    return 1;
}

void dfs3(int v, int col) {
    c[v] = col;
    trav(u, gr[v]) {
        int nxt = col+1;
        if (nxt == 4) nxt = 1;
        dfs3(u, nxt);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    bool allones = 1;
    F0R(i, n-1) {
        int p; cin >> p;
        gr[p].pb(i+2);
        allones &= (p==1);
    }
    int k = 1;
    // first see if its just 1 level
    if (allones) {
        cout << 1 << nl;
        k = 1;
        FOR(i, 2, n) c[i] = 1;
        output();
    } else {
        // try with 2 colors
        // for those with 1 child, try to make them 1 on parent edge, 2 on child edge
        bool ok = 1;
        trav(v, gr[1]) {
            bool ret = dfs2(v, 1);
            if (!ret) ret = dfs2(v, 2);
            if (!ret) ok = 0;
            if (!ok) break;
        }
        if (!ok) {
            // try 3
            dfs3(1, 3);
            cout << 3 << nl;
            k = 3;
            output();
        } else {
            cout << 2 << nl;
            k = 2;
            output();
        }
    }
    while (1) {
        int x; cin >> x;
        if (x == 1 || x == -1) {
            break;
        } else {
            int e[k+1];
            F0R(i, k) cin >> e[i+1];
            int cnt = 0;
            FOR(i, 1, k) cnt += (e[i] > 0);
            if (cnt == 1) {
                FOR(i, 1, k) {
                    if (e[i]) cout << i << endl;
                }
                cout.flush();
            } else if (cnt == 2) {
                if (k == 3) {
                    if (e[1] && e[2]) {
                        cout << 1 << endl;
                        cout.flush();
                    } else if (e[2] && e[3]) {
                        cout << 2 << endl;
                        cout.flush();
                    } else if (e[3] && e[1]) {
                        cout << 3 << endl;
                        cout.flush();
                    }
                } else if (k == 2) {
                    // whichever one has 1 freq
                    if (e[1]==1 && e[2]==1) {
                        cout << 1 << endl;
                        cout.flush();
                    } else if (e[1] == 1) {
                        cout << 1 << endl;
                        cout.flush();
                    } else {
                        cout << 2 << endl;
                        cout.flush();
                    }
                }
            } else assert(0);
        }
    }
    return 0;
}
