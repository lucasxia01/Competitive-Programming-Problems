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

const int MX = 1e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    int ans[n]; memset(ans, 0, sizeof ans);
    vector<tuple<int, int, int> > V;
    F0R(i, m)  {
        int u, v, w; cin >> u >> v >> w; u--; v--;
        V.pb({u, v, w});
        F0R(j, 30) {
            
        }
    }
    F0R(j, 30) {
        vector<int> q[n];
        int done[n]; memset(done, 0, sizeof done);
        F0R(i, m) {
            auto [u, v, w] = V[i];
            if (!(w&(1<<j))) {
                done[u] = done[v] = -1;
                continue;
            }
            q[u].pb(v);
            q[v].pb(u);
            if(u==v) {
                done[u] = 1;
                ans[u] |= (1<<j);
            }
        }
        F0R(i, n) {
            if (done[i] == -1) {
                trav(p, q[i]) {
                    done[p] = 1;
                    ans[p] |= (1<<j);
                }
            }
        }
        F0R(i, n) {
            if (done[i] == 0) {
                done[i] = -1;
                trav(p, q[i]) {
                    done[p] = 1;
                    ans[p] |= (1<<j);
                }
            }
        }
    }
    F0R(i, n) {
        cout << ans[i] << " ";
    } cout << nl;
    return 0;
}
