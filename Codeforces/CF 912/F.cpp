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

int n;
vector<vector<int>> adj, adj_t, ADJ, ADJ_T;
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;

void dfs1(int v) {
    used[v] = true;
    for (int u : adj[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : adj_t[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT() {
    order.clear();
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            dfs1(i);
    }

    comp.assign(n, -1);
    for (int i = 0, j = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}

void add_disjunction(int a, bool na, int b, bool nb, bool INIT=0) {
    // cout << (na?-a:a) << " " << (nb?-b:b) << nl;
    // dbg(a, na, b, nb);
    // na and nb signify whether a and b are to be negated 
    a = 2*a ^ na;
    b = 2*b ^ nb;
    int neg_a = a ^ 1;
    int neg_b = b ^ 1;
    if (INIT) {
        ADJ[neg_a].push_back(b);
        ADJ[neg_b].push_back(a);
        ADJ_T[b].push_back(neg_a);
        ADJ_T[a].push_back(neg_b);
        return;
    }
    adj[neg_a].push_back(b);
    adj[neg_b].push_back(a);
    adj_t[b].push_back(neg_a);
    adj_t[a].push_back(neg_b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int N; cin >> N;
        n = 2*N; // we need n more variables for the segtree
        n*=2; // for negations
        int m; cin >> m;
        ADJ.clear(); ADJ.resize(n);
        ADJ_T.clear(); ADJ_T.resize(n);
        F0R(i, m) {
            int u, v; cin >> u >> v;
            u--; v--;
            u+=N; v+=N;
            add_disjunction(u, 0, v, 0, 1);
        }
        // add in constraints to segments
        F0R(i, N) {
            for (int j = i+N; j > 0; j>>=1) {
                add_disjunction(i+N, 1, j, 0, 1);
            }
        }
        // now we binary search
        int lo = 1, hi = N+1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            adj = ADJ;
            adj_t = ADJ_T;
            // add in constraints from i to [i+1, i+mid)
            F0R(i, N) {
                int l = i+1+N;
                int r = min(2*N, l+mid-1);
                for (; l < r; l>>=1, r>>=1) {
                    if (l&1) add_disjunction(i+N, 1, l++, 1);
                    if (r&1) add_disjunction(i+N, 1, --r, 1);
                }
            }
            if (solve_2SAT()) lo = mid+1;
            else hi = mid;
        }
        cout << lo-1 << nl;
    }
    return 0;
}
