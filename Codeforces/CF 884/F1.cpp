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

vi solve(vi v, int k) {
    dbg("solve", k);
    trav(x, v) dbg(x);
    if (sz(v) == 1) return v;
    vi ans; ans.pb(v[0]);
    int n = sz(v);
    int cur = 0;
    while (cur < n-1) {
        int prev = -1;
        int last = v[0];
        vi rem;
        while (1) {
            int best = -1;
            FOR(i, cur+2, n-2) {
                if (v[cur]-v[i] > k) break;
                dbg(i, v[i-1], v[i+1]);
                if (v[i-1]-v[i+1] <= k) {
                    best = i;
                    prev = i-1;
                }
            }
            if (best == -1) {
                // try cur+1
                if (cur+2 < n && (prev == -1 || v[prev]-v[cur+2] <= k)) {
                    // we can take cur+1
                    best = cur+1;
                } else break;
            }
            dbg("removing index", best, "value", v[best]);
            ans.pb(v[best]);
            last = v[best];
            FOR(i, cur+1, best-1) {
                rem.pb(v[i]);
            }
            cur = best;
        }
        reverse(all(rem));
        dbg("rem");
        trav(r, rem) dbg(r);
        dbg("end rem at idx", cur);
        // now just greedy for largest thing within k
        cur = cur+1;
        vi other, ret;
        ret.pb(v[cur]);
        int m = sz(rem);
        dbg(sz(rem), sz(ret));
        // dbg(cur, rem[0]);
        if (m > 0) assert(rem[0]-v[cur] <= k);
        F0R(i, m-1) assert(rem[i+1]-rem[i] <= k);
        int val = v[cur];
        F0R(i, m) {
            if (rem[i] >= last) {
                int j = i-1;
                while (i < m && rem[i]-val <= k) {
                    other.pb(rem[i]);
                    i++;
                }
                other.pop_back();
                i--;
            }
            val = rem[i];
            ret.pb(val);
        }
        dbg("other");
        trav(o, other) dbg(o);
        dbg("end other");
        trav(o, other) ans.pb(o);
        reverse(all(ret));
        trav(aa, ret) ans.pb(aa);
        dbg("current state");
        trav(aa, ans) dbg(aa);
        dbg("at idx ", cur);
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vi c(n); F0R(i, n) cin >> c[i];
        sort(all(c));
        if (k >= 0) {
            F0R(i, n) cout << c[i] << " "; cout << nl;
        } else {
            k *= -1;
            reverse(all(c));
            vi v;
            int ii = 0;
            while (ii < n) {
                v.pb(c[ii]);
                if (ii == n-1 || c[ii] - c[ii+1] > k) {
                    vi ret = solve(v, k);
                    trav(i, ret) cout << i << ' ';
                    v.clear();
                }
                ii++;
            }
            cout << nl;
        }
    }
    return 0;
}
