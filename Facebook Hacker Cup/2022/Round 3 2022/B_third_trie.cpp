#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

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
const ll MOD = 1000000007LL; // 998244353
const ll MOD2 = 1000000009LL;
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

const int MX = 5e5+5;

vector<vector<pair<int, char> > > gr[100];

struct Trie {
    vector<Trie*> c;
    int cnt = 1;
    Trie() {
        c.resize(26);
    }

    bool operator<(const Trie& o) const {
        return (cnt < o.cnt);
    }
};

Trie* construct(int i, int v) {
    Trie* cur = new Trie;
    trav(u, gr[i][v]) {
        Trie* child = construct(i, u.f);
        cur->c[u.s-'a'] = child;
        cur->cnt += child->cnt;
    }
    return cur;
}

Trie* construct(int i, int j, int v) {
    Trie* cur = new Trie;
    trav(u, gr[i][v]) {
        Trie* child = construct(i, u.f);
        cur->c[u.s-'a'] = child;
        cur->cnt += child->cnt;
    }
    return cur;
}


void solve() {
    int n; cin >> n;
    Trie tries[n];
    F0R(i, n) {
        gr[i].clear();
        int m; cin >> m;
        F0R(j, m+1) {
            vector<pair<int, char> > tmp;
            gr[i].pb(tmp);
        }
        F0R(j, m) {
            int p; char c; cin >> p >> c;
            gr[i][p].pb({j+1, c});
        }
        tries[i] = *construct(i, 1);
    }
    sort(tries, tries+n);
    int ans = 0;
    F0R(i, n-1) {
        F0R(j, i) {

            FOR(k, i+1, n-1) {

            }
        }
    }
    cout << ans << nl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    FOR(i, 1, t) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}