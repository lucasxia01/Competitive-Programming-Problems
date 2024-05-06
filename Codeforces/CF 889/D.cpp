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

const int MX = 500+5;
int n;
double calc(int x, int k) {
    // return (x/k)*9 + ()
    int y = (x+k-1)/k;
    ld val = 0;
    if (k == 2) val = 1;
    else if (k == 3) val = 3.0/2;
    else if (k == 4) val = 26.0/18;
    return 9*y + (500-x)*k + (x-(x/k))*(val);
}

int querycnt = 0;

bool query(int u, int k, const set<int>& S) {
    if (sz(S) == 0) return 0;
    if (querycnt == 2000) {
        assert(0);
    }
    querycnt++;
    cout << "? " << u << " " << k << " " << sz(S);
    trav(s, S) cout << " " << s;
    cout << endl;
    cout.flush();
    bool x; cin >> x;
    return x;
}

// find the room that is k steps from u
int find(int u, int k) {
    // binary search for it
    int ans = 0;
    F0R(j, 9) {
        set<int> S;
        FOR(i, 1, n) {
            if (i&(1<<j)) S.insert(i);
        }
        int x = query(u, k, S);
        ans += x*(1<<j);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // FOR(x, 1, 500) {
    //     // find if k works
    //     bool ok = 0;
    //     FOR(k, 1, 501) {
    //         if (calc(x, k) < 1850) {
    //             ok = 1;
    //             dbg(x, k);
    //             break;
    //         }
    //     }
    //     if (!ok) {
    //         dbg(x);
    //     }
    // }
    // return 0;
    cin >> n;
    // find the cycle length
    set<int> cycle;
    int X = -1;
    int cycle_node = -1;
    FOR(i, MX, MX+7) { // use 72 queries
        int v = find(1, i);
        if (i == MX) cycle_node = v;
        if (cycle.count(v)) {
            X = i-MX;
            break;
        }
        cycle.insert(v);
    }
    if (X == -1) {
        // now +8 until we hit it again
        int i = MX+8;
        while (1) {
            bool val = query(1, i, cycle); // this should be at most 500/8 queries
            if (val) break;
            i += 8;
        }
        FOR(j, i-7, i) {
            if (query(1, j, {cycle_node})) {
                X = j-MX;
                break;
            }
        }
        if (X == -1) {
            while (1);
        }
    }
    int K = -1;
    
    FOR(k, 1, 501) {
        if (calc(X, k) < 1850) {
            K = k;
            break;
        }
    }
    if (K == -1) {
        dbg("wtf sad");
        while (1);
    }
    // now split cycle in Kths using 9 X/K queries
    int i = MX+K;
    while (i-MX < X) {
        int v = find(1, i);
        cycle.insert(v);
        i += K;
    }
    set<int> ans; ans.insert(1);
    // now for everything not in the cycle, query for it
    vi V;
    FOR(v, 2, n) V.pb(v);
    shuffle(all(V), rng);
    trav(v, V) {
        if (cycle.count(v)) continue;
        int J = MX;
        F0R(j, K) { // use K queries for all dudes
            if (query(v, J+j, cycle)) {
                ans.insert(v);
                cycle.insert(v);
                break;
            }
        }
    }
    trav(cc, cycle) ans.insert(cc);

    cout << "! " << sz(ans);
    trav(aa, ans) cout << " " << aa;
    cout << nl;
    return 0;
}
