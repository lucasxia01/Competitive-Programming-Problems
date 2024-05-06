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

const int MX = 4000+5;

int n;
string s[MX];

vi comps[MX];
int vis[MX];

void dfs(int v, int mark) {
    if (vis[v] != -1) return;
    vis[v] = mark;
    comps[mark].pb(v);
    F0R(i, n) if (s[v][i] == '1') dfs(i, mark);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        F0R(i, n) cin >> s[i];
        int deg[n]; F0R(i, n) deg[i] = 0;
        F0R(i, n) F0R(j, n) {
            if (s[i][j] == '1') {
                // merge(i, j);
                deg[i]++;
            }
        }
        
        // find all comps
        F0R(i, n) comps[i].clear();
        F0R(i, n) vis[i] = -1;
        int cnt = 0;
        F0R(i, n) {
            if (vis[i] == -1) dfs(i, cnt++);
        }
        // dbg("cnt",  cnt);
        if (cnt == 1) {
            cout << 0 << nl;
            continue;
        }
        // now for all comps, find them
        int small = -1;
        // check FC
        bool allFC = 1;
        int ans = -1;
        F0R(i, cnt) {
            if (comps[i].size() == 1) small = comps[i][0];
            bool ok = 1;
            trav(c, comps[i]) {
                if (deg[c] != sz(comps[i])-1) ok = 0;
            }
            if (!ok) {
                queue<int> q;
                trav(c, comps[i]) {
                    if (deg[c] == sz(comps[i])-1) q.push(c);
                }
                bool vis[MX] = {};
                int last = -1;
                q.push(comps[i][0]);
                while (!q.empty()) {
                    int cur = q.front(); q.pop();
                    if (vis[cur]) continue;
                    vis[cur] = 1;
                    last = cur;
                    trav(c, comps[i]) {
                        if (s[cur][c] == '1') q.push(c);
                    }
                }
                ans = last;
                allFC = 0;
                break;
            }
        }
        if (small != -1) {
            cout << 1 << nl;
            cout << small+1 << nl;
            continue;
        }
        if (!allFC) {
            // try inverting the rest of the component
            cout << 1 << nl;
            cout << ans+1 << nl;
        } else {
            if (cnt == 2) {
                cout << min(sz(comps[0]), sz(comps[1])) << nl;
                int i = 0;
                if (sz(comps[0]) > sz(comps[1])) i = 1;
                trav(c, comps[i]) cout << c+1 << " ";
                cout << nl;
            } else {
                cout << 2 << nl;
                cout << comps[0][0]+1 << " " << comps[1][0]+1 << nl;
            }
        }
    }
    return 0;
}
