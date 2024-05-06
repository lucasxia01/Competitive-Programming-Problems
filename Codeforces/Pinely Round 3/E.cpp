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

const int MX = 2e5+5;

vi gr[MX];
int masks[20];

void dfs(int start, int cur) {
    if (masks[start]&(1<<cur)) return;
    masks[start] |= (1<<cur);
    trav(u, gr[cur]) {
        dfs(start, u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // precalc all winners from n up to 19
    vi winners[20];
    FOR(n, 1, 19) {
        F0R(j, (1<<n)) {
            if (j == 0) continue;
            int mask = 0;
            F0R(k, n) {
                if (j&(1<<k)) {
                    int kk = k+1;
                    while (kk <= n) {
                        mask ^= (1<<(kk-1));
                        kk += (k+1);
                    }
                }
            }
            // check if mask has only a few things turned on
            int cnt = 0;
            F0R(k, n) if (mask&(1<<k)) cnt++;
            if (cnt <= n/5) {
                winners[n].pb(j);
            }
        }
        dbg(n, sz(winners[n]));
    }
    int t = 1; 
    cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        FOR(i, 1, n) gr[i].clear();
        F0R(i, m) {
            int u, v; cin >> u >> v;
            u--; v--;
            gr[u].pb(v);
        }
        if (n >= 20) {
            cout << n << nl;
            FOR(i, 1, n) cout << i << " ";
            cout << nl;
            vector<bool> marked(n+1, 0);
            int cnt = 0;
            FOR(i, 1, n) {
                int j = i;
                while (j <= n) {
                    marked[j] = !marked[j];
                    j += i;
                }
                cnt += (marked[i]);
            }
            assert(cnt <= n/5);
            continue;
        }
        F0R(i, n) masks[i] = 0;
        // otherwise, just try every mask lol
        // dfs from every node and see what it implies
        F0R(i, n) {
            dfs(i, i);
        }
        // now just brute force
        bool win = 0;
        // try to achieve each winning mask
        trav(mask, winners[n]) {
            int cur = 0;
            F0R(i, n) {
                if ((masks[i]&mask) == masks[i]) {
                    cur |= masks[i];
                }
            }
            if (cur == mask) {
                win = 1;
                int cnt = 0;
                F0R(i, n) if (mask&(1<<i)) cnt++;
                cout << cnt << nl;
                F0R(i, n) if (mask&(1<<i)) cout << i+1 << " ";
                cout << nl;
                break;
            }
        }
        if (!win) cout << -1 << nl;
    }
    return 0;
}
