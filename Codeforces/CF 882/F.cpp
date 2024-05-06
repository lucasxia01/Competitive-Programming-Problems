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

struct Range {
    int len, end;
    bool operator < (const Range &r) const {
        return (tie(len, end) < tie(r.len, r.end));
    }
};

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = (jmp[k - 1][j]|jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return (jmp[dep][a]|jmp[dep][b - (1 << dep)]);
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, q; cin >> n >> q;
        vi a(n); F0R(i, n) cin >> a[i];
        RMQ rmq(a);
        // find the 30 spots 
        int last[30]; F0R(i, 30) last[i] = -1;
        vector<Range> v; v.pb({0, 0});
        F0R(i, n) {
            F0R(j, 30) if (a[i] & (1<<j)) last[j] = i;
        }
        F0R(i, n) {
            F0R(j, 30) if (a[i] & (1<<j)) last[j] = i;
            set<int> s;
            F0R(j, 30) {
                if (last[j] != -1) s.insert(last[j]);
            }
            if (i == 0) continue;
            trav(ss, s) {
                int len = (i-ss+n)%n;
                v.pb({len, i});
            }
        }
        vpi qs; 
        ll ans[q]; F0R(i, q) ans[i] = -1;
        F0R(i, q) {
            int x; cin >> x;
            qs.pb({x, i});
        }
        sort(all(v));
        sort(all(qs));
        int i = 0;
        trav(r, v) {
            int s = (r.end-r.len+n)%n;
            int e = r.end;
            int o = 0;
            if (s > e) {
                o = rmq.query(s, n);
                o |= rmq.query(0, e+1);
            } else o = rmq.query(s, e+1);
            while (i < q && qs[i].f < o) {
                ans[qs[i].s] = 1LL*r.len*(n-1)+(r.end-1) + 2;
                i++;
            }
        }
        F0R(i, q) cout << ans[i] << nl;
    }
    return 0;
}
