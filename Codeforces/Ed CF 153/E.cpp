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

const int MXN = 26*26;

int c(char a, char b) {
    return (a-'a') * 26 + (b-'a');
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s; cin >> s;
    int n = sz(s);
    // preprocess all 26*26 
    vi pos[MXN];
    F0R(i, n-1) {
        pos[c(s[i], s[i+1])].pb(i);
    }
    int dist[MXN][MXN+n]; F0R(i, MXN) F0R(j, MXN+n) dist[i][j] = -1;
    F0R(i, MXN) {
        // bfs from i
        deque<pi> q;
        q.push_front({i, 0});
        while (!q.empty()) {
            auto [v, d] = q.front(); q.pop_front();
            if (dist[i][v] != -1) continue;
            dist[i][v] = d;
            if (v < MXN) { // cluster
                // go to anywhere in the cluster for free
                trav(u, pos[v]) q.push_front({u+MXN, d});
            } else {
                v -= MXN;
                // go left or right or to cluster
                if (v-1 >= 0) q.push_back({v-1+MXN, d+1});
                if (v+1 < n-1) q.push_back({v+1+MXN, d+1});
                q.push_back({c(s[v], s[v+1]), d+1});
            }
        }
    }

    int q; cin >> q;
    while (q--)
    {
        int a, b; cin >> a >> b;
        a--; b--;
        // try all clusters in middle
        int ans = abs(b-a);
        F0R(i, MXN) {
            if (dist[i][MXN+a] == -1 || dist[i][MXN+b] == -1) continue;
            ckmin(ans, dist[i][MXN+a]+dist[i][MXN+b]+1);
        }
        cout << ans << nl;
    } 
    return 0;
}
