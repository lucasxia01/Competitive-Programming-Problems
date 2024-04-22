#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define trav(a, x) for(auto& a : x)
#define f first
#define s second
#define pb push_back
const char nl = '\n';

#ifdef DBG
void dbg_out() { cerr << nl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 2e5 + 5;
vi gr[MX];
int mark[MX];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        rep(i, 0, n) gr[i].clear();
        rep(i, 0, n) mark[i] = -1;
        rep(i, 0, n) {
            if (i != n-1) gr[i].pb(i+1);
            else gr[0].pb(n-1);
        }
        rep(i, 0, m) {
            int u, v; cin >> u >> v;
            if (u > v) swap(u, v);
            gr[u].pb(v);
        }
        mark[0] = 0;
        rep(i, 0, n) {
            trav(j, gr[i]) {
                if (mark[j] == -1) mark[j] = 1-mark[i];
            }
        }
        rep(i, 0, n) cout << "BR"[mark[i]];
        cout << nl;
    }
}