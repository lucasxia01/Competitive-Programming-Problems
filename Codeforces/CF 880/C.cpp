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

const int MX = 3e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int k; cin >> k;
        int n = (1<<(k+1));
        ll g[n], x[n+1]; x[0] = 0;
        rep(i, 0, n) {
            cin >> g[i];
            x[i+1] = (x[i]^g[i]);
        }
        // check for different values
        unordered_map<ll, int> m;
        bool ok = 0;
        pair<pi, pi> ans;
        rep(i, 0, n) {
            if (m.find(g[i]) != m.end()) {
                ans = {{m[g[i]], m[g[i]]}, {i, i}};
                ok = 1;
                break;
            }
            m[g[i]] = i;
        }
        if (ok) {
            vi v = {ans.f.f, ans.f.s, ans.s.f, ans.s.s};
            for (int u : v) cout << u+1 << " "; cout << nl;
            continue;
        }

        // repeat randomly for like ~2^28 operations
        int ITERS = 1<<(k+6);
        unordered_map<ll, pi> M;
        rep(i, 0, ITERS) {
            int l = rng()%n, r = rng()%n;
            if (l > r) swap(l, r);
            if (g[l] == 0) l++;
            if (g[r] == 0) r--;
            if (l > r) continue;
            ll X = (x[l]^x[r+1]);
            if (M.find(X) == M.end()) {
                M[X] = {l, r};
            }
            pi cur = M[X];
            if (cur != mp(l, r)) {
                ans = {{cur.f, cur.s}, {l, r}};
                ok = 1;
                break;
            }
        }
        if (ok) {
            // dbg("hi", ans.f.f+1, ans.f.s+1, ans.s.f+1, ans.s.s+1);
            vi v;
            if (ans.f > ans.s) swap(ans.f, ans.s);
            if (ans.f.f == ans.s.f) {
                if (ans.f.s+2 <= ans.s.s)
                    v = {ans.f.s+1, ans.f.s+1, ans.f.s+2, ans.s.s};
                else assert(0);
            } else if (ans.f.s == ans.s.s) {
                if (ans.f.f+2 <= ans.s.f) {
                    v = {ans.f.f, ans.f.f, ans.f.f+1, ans.s.f-1};
                } else assert(0);
            } else { // not same endpoints
                if (ans.f.s < ans.s.f) {
                    v = {ans.f.f, ans.f.s, ans.s.f, ans.s.s};
                } else if (ans.f.s < ans.s.s) {
                    v = {ans.f.f, ans.s.f-1, ans.f.s+1, ans.s.s};
                } else {
                    v = {ans.f.f, ans.s.f-1, ans.s.s+1, ans.f.s};
                }
            }
            for (int u : v) cout << u+1 << " "; cout << nl;
        } else {
            while (1);
        }
    }
    return 0;
}
