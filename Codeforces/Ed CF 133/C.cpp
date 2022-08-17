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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int m; cin >> m;
        int a[2][m]; F0R(j, 2) F0R(i, m) {
            cin >> a[j][i];
            if (a[j][i]) a[j][i]++;
        }
        vi v, rev;
        FOR(i, 1, m-1) v.pb(a[0][i]);
        F0Rd(i, m) v.pb(a[1][i]);
        F0R(i, m) rev.pb(a[1][i]);
        FORd(i, 1, m-1) rev.pb(a[0][i]);
        F0R(i, 2*m-1) {
            v[i] += 2*m-2-i;
            rev[i] += 2*m-2-i;
        }
        RMQ<int> r1(v), r2(rev);
        // now snake through
        int x = 0, y = 0, t = 0;
        int ans = (int)2e9;
        pi p1 = {0, 2*m-1}, p2 = {0, 2*m-1};
        F0R(i, 2*m-1) {
            ckmax(t, a[x][y]+2*m-1-i);
            if (x == 0) { // v
                ckmin(ans, max(t, r1.query(p1.f, p1.s) - (2*m-1-p1.s)));
            } else { // rev
                ckmin(ans, max(t, r2.query(p2.f, p2.s) - (2*m-1-p2.s)));
            }
            // upd
            if (x == 0 && y%2 == 0) {
                x = 1;
                p1.s--;
                p2.f++;
            } else if (x == 0 && y%2) {
                y++;
                p1.f++;
                p2.s--;
            } else if (x == 1 && y%2 == 0) {
                y++;
                p1.s--;
                p2.f++;
            } else {
                x = 0;
                p1.f++;
                p2.s--;
            }
        }
        cout << ans << nl;
    }
    return 0;
}
