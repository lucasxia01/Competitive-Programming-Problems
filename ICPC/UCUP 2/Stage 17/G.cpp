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

int r, c; 
vi gr[2*MX];
int mark[2*MX];

bool dfs(int v, int m) {
    if (mark[v] && mark[v] != m) return 0;
    else if (mark[v]) return 1;
    mark[v] = m;
    trav(u, gr[v]) {
        if (!dfs(u, 3-m)) return 0;
    }
    return 1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        cin >> r >> c;
        // r nodes, at most ceil(c/2) edges
        string s[r];
        F0R(i, r) cin >> s[i];
        // find all the edges
        F0R(i, 2*r) {
            gr[i].clear();
            mark[i] = 0;
        }
        F0R(i, r) {
            gr[2*i].pb(2*i+1);
            gr[2*i+1].pb(2*i);
        }

        bool ok = 1;
        F0R(j, (c+1)/2) { 
            vi v;
            F0R(i, r) if (s[i][j] == '1' || s[i][c-1-j] == '1') v.pb(i);
            if (sz(v) > 2 || ((j == c-1-j)&&sz(v) > 1)) {
                ok = 0;
                break;
            } else if (sz(v) <= 1) continue; // we don't care about this bit
            else {
                dbg("edge", v[0], v[1]);
                if (s[v[0]][j] == '1' && s[v[1]][j] == '1') {
                    gr[2*v[0]].pb(2*v[1]);
                    gr[2*v[1]].pb(2*v[0]);
                }
                if (s[v[0]][j] == '1' && s[v[1]][c-1-j] == '1') {
                    gr[2*v[0]].pb(2*v[1]+1);
                    gr[2*v[1]+1].pb(2*v[0]);
                }
                if (s[v[0]][c-1-j] == '1' && s[v[1]][j] == '1') {
                    gr[2*v[0]+1].pb(2*v[1]);
                    gr[2*v[1]].pb(2*v[0]+1);
                }
                if (s[v[0]][c-1-j] == '1' && s[v[1]][c-1-j] == '1') {
                    gr[2*v[0]+1].pb(2*v[1]+1);
                    gr[2*v[1]+1].pb(2*v[0]+1);
                }
            }
        }
        ll ans = 1;
        F0R(i, 2*r) {
            if (!mark[i]) {
                if (!dfs(i, 1)) {
                    ok = 0;
                    break;
                } else {
                    ans = (ans*2)%MOD;
                }
            }
        }
        if (!ok) ans = 0;
        cout << ans << nl;
    }
    return 0;
}
