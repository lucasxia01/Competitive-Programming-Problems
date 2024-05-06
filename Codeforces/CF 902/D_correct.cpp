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
const ll MOD = 998244353;
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

const int MXN = 2e5+5;
const int MX = 15;

int parent[MX];
int SZ[MX];
int numComps;
void make_set(int v) {
    parent[v] = v;
    SZ[v] = 1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        numComps--;
        if (SZ[a] < SZ[b])
            swap(a, b);
        parent[b] = a;
        SZ[a] += SZ[b];
    }
}
ll pow2[MXN];
int last[MX]; 

void solve() {
    FOR(i, 1, MX-1)  {
        make_set(i);
    }

    int n; cin >> n;
    set<int> vals;
    int a[n]; F0R(i, n) cin >> a[i];
    F0R(i, n) vals.insert(a[i]);
    numComps = sz(vals);
    int N = numComps;
    int nxt[n]; F0R(i, n) nxt[i] = -1;
    F0R(i, MX) last[i] = -1;
    F0R(i, n) {
        if (last[a[i]] == -1) {
            last[a[i]] = i;
        } else {
            nxt[last[a[i]]] = i;
            nxt[i] = -1;
            last[a[i]] = -1;
        }
    }
    F0R(i, MX) if (last[i] != -1) {
        nxt[last[i]] = n+1;
    }
    // arbitrarily pick first one and see what happens?
    int val[MX]; F0R(i, MX) val[i] = -1;
    vi blue, red;
    int curComp = -1;
    int r = -1;
    ll ans = 0;
    bool done = 0;
    F0R(i, n) {
        if (r < i) {
            curComp = a[i];
        }
        ckmax(r, nxt[i]);
        union_sets(curComp, a[i]);
        dbg(i, curComp, a[i], nxt[i], numComps);

        if (val[a[i]] == -1) { // just throw it into the first bucket
            if (sz(blue) == sz(red)) { // doesn't matter 
                blue.pb(a[i]);
                val[a[i]] = 1;
            } else { // does matter and see what happens
                // is a stopping point either way in comparison since we've never seen the value before
                dbg("adding1", pow2[numComps-1]);
                ans += pow2[numComps-1];
                ans %= MOD;
                // throw it into the larger one always
                if (sz(blue) > sz(red)) {
                    blue.pb(a[i]);
                    val[a[i]] = 1;
                } else {
                    red.pb(a[i]);
                    val[a[i]] = 0;
                }
            }
            
        } else if (val[a[i]] == 1) {
            int j = sz(red);
            red.pb(a[i]);
            if (j < sz(blue)) {
                if (blue[j] != red[j]) { // one stopping point
                    dbg("adding2", pow2[numComps-1]);
                    ans += pow2[numComps-1];
                    ans %= MOD;
                    done = 1;
                    break;
                }
            }
            val[a[i]] = 0;
        } else {
            int j = sz(blue);
            blue.pb(a[i]);
            if (j < sz(red)) {
                if (blue[j] != red[j]) { // one stopping point
                    dbg("adding3", pow2[numComps-1]);
                    ans += pow2[numComps-1];
                    ans %= MOD;
                    done = 1;
                    break;
                }
            }
            val[a[i]] = 1;
        }
    }
    dbg(done, ans);
    // add the back
    ll ans2 = pow2[N-1];
    if (!done && sz(blue) != sz(red)) {
        ans += pow2[numComps-1];
        ans %= MOD;
    } else if (!done) ans2 = (ans2-pow2[numComps-1]+MOD)%MOD;
    if (ans != ans2) {
        dbg(N, numComps);
        dbg(ans, ans2);
        dbg("BAD");
        cout << n << nl;
        F0R(i, n) cout << a[i] << " ";
        cout << nl;
        assert(0);
    }
    cout << ans2 << nl;
    // cout << ans << nl;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    pow2[0] = 1;
    FOR(i, 1, MXN-1) {
        pow2[i] = (pow2[i-1]*2)%MOD;
    }
    int t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}