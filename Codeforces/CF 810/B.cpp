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
const ll INF = (1LL<<50) + 123;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        map<int, int> sum;
        vpi a(n); F0R(i, n) {
            cin >> a[i].f >> a[i].s;
            sum[a[i].f] += a[i].s;
        }
        // first calc all positions, then find segment
        map<int, int> r;
        vpi b; trav(p, a) {
            b.pb(p);
            b.pb({p.f+p.s, 0});
        }
        sort(all(b));
        int prev = -INF, cur = 0, cnt = 0;
        trav(bb, b) {
            cur -= (bb.f-prev)*cnt;
            if (bb.s == 0) {
                cnt--;
            } else {
                cnt++;
                cur += bb.s;
                r[bb.f] = cur;
            }
            dbg(bb.f, bb.s, cur, prev, cnt);
            prev = bb.f;
        }

        vpi c; trav(p, a) {
            c.pb({p.f, p.s});
            c.pb({p.f-p.s, 0});
        }
        sort(all(c));
        reverse(all(c));
        prev = INF, cur = 0, cnt = 0;
        map<int, int> s;
        trav(cc, c) {
            cur -= (prev-cc.f)*cnt;
            if (cc.s == 0) {
                cnt--;
            } else {
                cnt++;
                cur += cc.s;
                s[cc.f] = cur;
            }
            dbg(cc.f, cc.s, cur, prev, cnt);
            prev = cc.f;
        }
        // now create convex hull of lines
        int neg = -INF, pos = -INF;
        trav(rr, r) {
            int y = rr.s+s[rr.f]-sum[rr.f];
            dbg(rr.f, y);
            if (y > m) {
                ckmax(pos, y-m-rr.f);
                ckmax(neg, y-m+rr.f);
            }
        }
        F0R(i, n) {
            if (a[i].s + a[i].f >= neg && a[i].s-a[i].f >= pos) cout << 1;
            else cout << 0;
        } cout << nl;
        
    }
    return 0;
}
