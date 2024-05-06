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
        int n; cin >> n;
        string s; cin >> s;
        int a[n+1]; FOR(i, 1, n) cin >> a[i];
        // form the cactus graph by topsorting
        queue<int> q;
        int mark[n+1]; FOR(i, 1, n) mark[i] = (s[i-1]=='1');
        set<pi> degcnt[n+1];
        FOR(i, 1, n) {
            degcnt[i].insert({a[i], i});
            degcnt[a[i]].insert({i, i});
        }
        FOR(i, 1, n) if (sz(degcnt[i]) == 1) q.push(i);
        // handle all the trees
        vi ans;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            assert(sz(degcnt[v]) == 1);
            pi e = *degcnt[v].begin();
            int par = e.f;
            int idx = e.s;
            if (mark[v]) {
                // we should use this last edge
                mark[v] = 0;
                mark[par] = 1-mark[par];
                ans.pb(idx);
            }
            degcnt[v].erase(e);
            degcnt[par].erase({v, idx});
            if (sz(degcnt[par]) == 1) q.push(a[v]);
        }
        // now we only have cycles left, everythign should have degree 0 or 2
        FOR(i, 1, n) {
            dbg(i, sz(degcnt[i]));
            assert(sz(degcnt[i]) == 2 || sz(degcnt[i]) == 0);
        }
        // then for each cycle, guess which side to take
        bool ok = 1;
        FOR(i, 1, n) {
            // dfs on it if it has degree 2
            if (mark[i] && sz(degcnt[i]) == 2) {
                // then try both sides
                vi tmp[2];
                int cnt = 0;
                trav(y, degcnt[i]) {
                    // go one way
                    int cur = y.f;
                    int par_edge = y.s;
                    // mark the edge par to cur
                    mark[cur] = 1 - mark[cur];
                    mark[i] = 0;
                    tmp[cnt].pb(par_edge);
                    while (cur != i) {
                        pi p;
                        trav(x, degcnt[cur]) {
                            if (x.s != par_edge) {
                                p = x;
                                break;
                            }
                        }
                        if (mark[cur]) {
                            // we should mark this edge
                            mark[cur] = 0;
                            mark[p.f] = 1 - mark[p.f];
                            tmp[cnt].pb(p.s);
                        }
                        par_edge = p.s;
                        cur = p.f;
                    }
                    if (mark[i]) {
                        // it don't work
                        ok = 0;
                        break;
                    }
                    // now reset the marks and try again
                    trav(p, tmp[cnt]) {
                        // edge starting from p
                        mark[p] = 1- mark[p];
                        mark[a[p]] = 1-mark[a[p]];
                    }
                    cnt++;
                }
                if (!ok) break;
                if (sz(tmp[0]) < sz(tmp[1])) {
                    // do 0
                    trav(x, tmp[0]) {
                        mark[x] = 1 - mark[x];
                        mark[a[x]] = 1-mark[a[x]];
                        ans.pb(x);
                    }
                } else {
                    // do 1
                    trav(x, tmp[1]) {
                        mark[x] = 1 - mark[x];
                        mark[a[x]] = 1-mark[a[x]];
                        ans.pb(x);
                    }
                }
            }
        }
        FOR(i, 1, n) if (mark[i]) ok = 0;
        if (!ok) cout << -1 << nl;
        else {
            cout << sz(ans) << nl;
            trav(x, ans) cout << x << " ";
            cout << nl;
        }

    }
    return 0;
}
