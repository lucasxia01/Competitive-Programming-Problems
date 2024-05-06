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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

const ll INV2 = (MOD+1)/2;

int mod(int x) {
    return (x%MOD + MOD)%MOD;
}

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    int prob[n]; memset(prob, 0, sizeof prob);
    F0R(i, k) {
        int x; cin >> x; x--;
        prob[x] = 1;
    }
    vpi gr[n];
    vpi e;
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        gr[u].pb({v, i});
        gr[v].pb({u, i});
        e.pb({u, v});
    }
    pi sizes[n-1];
    function<int(int, int)> diffy = [&](int v, int p) {
        int ret = prob[v];
        trav(u, gr[v]) {
            if (u.f == p) continue;
            int total = diffy(u.f, v);
            sizes[u.s].f = total;
            sizes[u.s].s = k-total;
            if (u.f != e[u.s].f) swap(sizes[u.s].f, sizes[u.s].s);
            ret += total;
        }
        return ret;
    };
    diffy(0, -1);
    int ans = 0;
    F0R(i, n-1) {
        // check prob of u->v
        int u = e[i].f, v = e[i].s;
        int val = mod(sizes[i].f * sizes[i].s);
        int cur = val;
        cur = mod(cur+ mod(mod(INV2*mod(mod(prob[u] * mod(1-prob[v]))))* mod(mod((sizes[i].f-1) * (sizes[i].s+1)) - val)));
        cur = mod(cur+ mod(mod(INV2*mod(mod(mod(1-prob[u]) * prob[v])))* mod(mod((sizes[i].f+1) * (sizes[i].s-1)) - val)));
        
        ans = mod(ans + cur);
        int tmp = mod((prob[u]+prob[v])*INV2);
        // dbg(u, v, prob[u], prob[v], tmp, sizes[i].f, sizes[i].s, cur);
        prob[u] = prob[v] = tmp;
    }
    ans = mod(ans*binpow(mod(k * (k-1) / 2), MOD-2));
    cout << ans << nl;
    return 0;
}
