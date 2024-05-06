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

template<class T>
struct RMQ {
	vector<vector<pair<T, int>>> jmp;
	RMQ(const vector<pair<T, int> >& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k])) {
                jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j + pw]);
            }
		}
	}
	pair<T, int> query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n; cin >> n;
        vpi a(2*n); 
        F0R(i, n) cin >> a[i].f;
        F0R(i, n) a[i+n].f = a[i].f;
        F0R(i, 2*n) a[i].s = i;
        // we need some sort of range minimum query, that also gives the index
        RMQ<int> rmq(a);

        // first calculate the sequence
        vpi seq;
        FOR(i, n, 2*n-1) {
            while(sz(seq) && seq.back().f > a[i].f) seq.pop_back();
            seq.pb(a[i]);
        }
        // calc ans from the seq
        ll ans = 0;
        int prev = n;
        ll cur = 0;
        trav(v, seq) {
            cur += 1LL*(v.s-prev) * v.f;
            prev = v.s;
        }
        ckmax(ans, cur);
        FOR(k, 1, n-1) { // shift back by 1
            int L = n - k, R = n-k+n;
            dbg(L, R);
            // seq stays mostly the same except last thing gets removed and replaced
            pi last = seq.back(); seq.pop_back();
            int pos;
            if (sz(seq)) {
                cur -= 1LL*(last.s - seq.back().s)*last.f;
                pos = seq.back().s;
            } else {
                assert(last.f == 0);
                seq.pb(a[L]);
                assert(a[L].f == 0);
                pos = L;
            }
            while (pos < R-1) {
                pi res = rmq.query(pos+1, R);
                assert(res.f > seq.back().f);
                // add to ans
                cur += 1LL*(res.s-pos)*res.f;
                seq.pb(res);
                pos = res.s;
            }
            ckmax(ans, cur);
        }
        cout << ans+n << nl;
    }
    return 0;
}
