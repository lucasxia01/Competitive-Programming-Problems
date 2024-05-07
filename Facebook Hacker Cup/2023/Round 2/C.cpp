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

const int MX = 1e6+5;

vi gr[MX];
map<string, int> state[MX]; // counts how many leaves we satisfy
vector<string> topics[MX];
int ptr[MX];

int dfs(int v) {
    if (sz(gr[v]) == 0) { // leaf
        trav(t, topics[v]) {
            state[ptr[v]][t] = 1;
        }
        return 1;
    } else if (sz(gr[v]) == 1) {
        // only one leaf, just merge it
        int num_leaves = dfs(gr[v][0]);
        ptr[v] = ptr[gr[v][0]];
        // merge stuff in
        trav(t, topics[v]) {
            if (!state[ptr[v]].count(t)) state[ptr[v]][t] = 0;
            
            if (state[ptr[v]][t] == num_leaves-1) state[ptr[v]][t] = num_leaves;
            else if (state[ptr[v]][t] < num_leaves-1) state[ptr[v]].erase(t);
        }
        return num_leaves;
    }
    // otherwise, we are joining multiple things together
    int ret = 0;
    trav(u, gr[v]) {
        // try to do stuff here
        int num_children = dfs(u);
        trav(r, state[ptr[u]]) {
            string t = r.f;
            int st = r.s;
            if (!state[ptr[v]].count(t)) state[ptr[v]][t] = 0;

            state[ptr[v]][t] += st;
        }
        ret += num_children;
    }
    trav(t, topics[v]) {
        if (!state[ptr[v]].count(t)) state[ptr[v]][t] = 0;
        
        if (state[ptr[v]][t] == ret-1) state[ptr[v]][t] = ret;
        else if (state[ptr[v]][t] < ret-1) state[ptr[v]].erase(t);
    }

    // double check out state
    for (auto it = state[ptr[v]].begin(); it != state[ptr[v]].end(); ) {
        if (it->s < ret-1) {
            state[ptr[v]].erase(it++);
        } else ++it;
    }
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    FOR(tt, 1, t) {
        cout << "Case #" << tt << ": ";
        int n; cin >> n;
        FOR(i, 1, n) {
            gr[i].clear();
            state[i].clear();
            topics[i].clear();
            ptr[i] = i;
        }
        FOR(i, 2, n) {
            int p; cin >> p;
            gr[p].pb(i);
        }
        FOR(i, 1, n) {
            int m; cin >> m;
            F0R(j, m) {
                string s; cin >> s;
                topics[i].pb(s);
            }
        }
        int num_leaves = dfs(1);
        int ans = 0;
        // see what is winnable
        trav(r, state[ptr[1]]) {
            if (r.s == num_leaves) {
                ans++;
            }
        }
        cout << ans << nl;

        // FOR(i, 1, n) {
        //     dbg("printing", i);
        //     trav(r, state[i]) {
        //         dbg(r.f, r.s);
        //     }
        // }
    }
    return 0;
}
