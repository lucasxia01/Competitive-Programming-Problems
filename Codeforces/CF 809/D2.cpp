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

const int MX = 1e5+5;

int n, k;
int SQRTK;
int nxt(int cur, int v) {
    if (cur == v) return -1;
    if (cur == 0) return 1;
    else {
        // cur+1 or v/(v/cur-1)
        if (v/(v/(cur+1)) == cur+1) return cur+1;
        int idx = v/cur-1;
        while (v/idx == cur) idx--;
        return v/idx;
    }
}

int total = 0;
int TOTAL = 0;
int cnt[MX], a[MX];
vi v[MX];
vi q[MX];

void add(int val, int x) {
    // dbg("ADD", val, a[x]);
    cnt[x]++;
    if (cnt[x] == 1) {
        v[val].pb(x);
        TOTAL++;
        if (TOTAL > 4*n) assert(0);
        // dbg("ADD", val, a[x]);
        total++;
    }
    int tmp = nxt(val, a[x]);
    // dbg(a[x], val, tmp);
    if (tmp == -1) return;
    q[tmp].pb(x);
    TOTAL++;
    if (TOTAL > 4*n) assert(0);
}

void remove(int val, int x) {
    cnt[x]--;
    if (cnt[x] == 0) total--;
    else {
        int t = nxt(val, a[x]);
        v[t].pb(x);
        TOTAL++;
        if (TOTAL > 4*n) assert(0);
        // dbg("ADD", t, a[x]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> k;
        SQRTK = max((int)sqrt(k), 1);
        F0R(i, n) cin >> a[i];
        // two ptr
        total = 0;
        TOTAL = 0;
        F0R(i, n) cnt[i] = 0;
        F0R(i, MX) {
            v[i].clear();
            q[i].clear();
        }
        F0R(i, n) q[a[i]/k].pb(i);
        int ans = INF;
        int i = 0, j = 0;
        while (1) {
            while (j < MX && total < n) {
                trav(p, q[j]) {
                    pi cur = {j, p};
                    add(cur.f, cur.s);
                }
                TOTAL -= sz(q[j]);
                q[j].clear();
                q[j].shrink_to_fit();
                j++;
            }
            if (total < n) break;
            // dbg(v.top().f, j-1);
            while (sz(v[i]) == 0) i++;
            ckmin(ans, j-1-i);
            trav(p, v[i]) {
                remove(i, p);
            }
            TOTAL -= sz(v[i]);
            v[i].clear();
            v[i].shrink_to_fit();
        }
        cout << ans << nl;
    }
    return 0;
}
