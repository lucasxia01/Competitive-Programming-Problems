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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n, m, k; cin >> n >> m >> k;
        vpi v(n); 
        F0R(i, n) {
            cin >> v[i].f;
            v[i].s = i;
        }
        sort(all(v));
        int r[n]; 
        F0R(i, n) r[v[i].s] = i;
        int inDeg[n]; F0R(i, n) inDeg[i] = 0;
        vi rgr[n], gr[n];
        F0R(i, m) {
            int a, b; cin >> a >> b; a--; b--;
            a = r[a]; b = r[b];
            dbg(a, b);
            inDeg[b]++;
            gr[a].pb(b);
            rgr[b].pb(a);
        }
        // do topsort
        queue<int> q;
        pi info[n]; F0R(i, n) info[i] = {-1, -n-1};
        bool source[n]; F0R(i, n) source[i] = 0;
        vi events[n];
        F0R(i, n) {
            if (inDeg[i] == 0) {
                q.push(i);
                info[i] = {0, -i};
                source[i] = 1;
            }
        }
        ll end = 0;
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            trav(u, rgr[cur]) {
                int val = (v[u].f > v[cur].f);
                ckmax(info[cur], {info[u].f+val, info[u].s});
            }
            dbg(cur, v[cur].f, source[cur], info[cur].f, -info[cur].s);
            events[-info[cur].s].pb(cur);
            ckmax(end, 1LL*k*info[cur].f + v[cur].f);
            trav(u, gr[cur]) {
                inDeg[u]--;
                if (inDeg[u] == 0) q.push(u);
            }
        }
        ll ans = 1e17+10;
        F0R(i, n) {
            // get cur max
            if (!source[i]) continue;
            auto large = end;
            ckmin(ans, end - v[i].f);
            trav(e, events[i]) {
                int cur = e;
                ckmax(end, 1LL*k*(info[cur].f+1) + v[cur].f);
            }
        }
        cout << ans << nl;
    }
    return 0;
}
