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

const int MX = 1e6+5;

struct SegTree {
    int tree[MX*2];
    int n;
    SegTree(int _n, vi& v) {
        n = _n;
        F0R(i, n) tree[i+n] = v[i];
        for (int i = n-1; i > 0; i--) tree[i] = max(tree[i<<1],tree[i<<1|1]);
    }
    void update(int i, int val) {
        i += n;
        tree[i] = val;
        while (i > 1) {
            i >>= 1;
            tree[i] = max(tree[i<<1],tree[i<<1|1]);
        }
    }
    int query(int l, int r) {
        l += n; r += n;
        int res = 0;
        while (l < r) {
            if (l&1) res = max(res,tree[l++]);
            if (r&1) res = max(res,tree[--r]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vi a(n); F0R(i, n) cin >> a[i];
        SegTree maxVal(n, a);

        set<pi> s;
        F0R(i, n) {
            s.insert({a[i], i});
        }
        vi diff(n);
        int prev = -1;
        trav(p, s) {
            diff[p.s] = 0;
            if (prev != -1) {
                diff[p.s] = p.f-prev;
            }
            prev = p.f;
        }
        SegTree maxGaps(n, diff);
        int q; cin >> q;
        while (q--) {
            int i, x; cin >> i >> x; i--;
            auto it = s.find({a[i], i});
            // update the gaps
            bool start = (it == s.begin());
            it++;
            if (it != s.end()) {
                // there is a bigger one
                int val = it->f-a[i]+maxGaps.tree[i+n];
                if (start) val = 0;
                maxGaps.update(it->s, val);
            }
            it--;
            s.erase(it);
            // now insert into new position
            s.insert({x, i});
            it = s.find({x, i});
            if (it != s.begin()) {
                it--;
                maxGaps.update(i, x-it->f);
                it++;
            } else maxGaps.update(i, 0);
            it++;
            if (it != s.end()) {
                maxGaps.update(it->s, it->f-x);
            }
            // trav(g, s) {
            //     cout << g.f << ' ' << g.s << nl;
            // }
            // cout << nl;
            // F0R(i, n) {
            //     cout << maxGaps.tree[i+n] << ' ';
            // } cout << nl;
            maxVal.update(i, x);
            // dbg(maxGaps.query(0, n), maxVal.query(0, n));
            cout << maxVal.query(0, n) + maxGaps.query(0, n) << " ";
            a[i] = x;
        }
        cout << nl;
    }
    return 0;
}
