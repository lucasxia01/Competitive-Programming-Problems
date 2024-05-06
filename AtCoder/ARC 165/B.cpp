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
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vi a(n); F0R(i, n) cin >> a[i];
    // find window of k where nothing changes first
    int prev = -1;
    int p[n];
    int hi = 1;
    F0R(i, n-1) {
        p[i] = prev;
        ckmax(hi, i-prev);
        if (a[i] > a[i+1]) prev = i;
    }
    p[n-1] = prev;
    ckmax(hi, n-1-prev);
    dbg(hi);
    if (hi >= k) {
        F0R(i, n) cout << a[i] << " "; cout << nl;
        return 0;
    }

    // find latest change possible
    int m = n;
    int idx = n-1;
    FORd(i, n-k, n-1) {
        if (a[i] > m) // something will change
            idx = i;
        ckmin(m, a[i]);
    }
    // idx will change
    // for every value, find next smaller thing
    int nxt[n];
    stack<pi> s; s.push({a[n-1], n-1});
    nxt[n-1] = n;
    F0Rd(i, n-1) {
        while (!s.empty() && s.top().f > a[i]) {
            s.pop();
        }
        nxt[i] = s.empty() ? n : s.top().s;
        s.push({a[i], i});
    }
    // try to move the window forwards
    int ans = n-k;
    int i = n-k-1;
    int end = n;
    while (i >= 0 && i >= n-2*k+1) {
        ckmin(end, nxt[i]);
        if (end >= i+k) ans = i;
        i--;
    }
    dbg(ans);
    sort(a.begin()+ans, a.begin()+(ans+k));

    // int i = n-k; // best
    // int lo = n;
    // FOR(j, i, n-1) ckmin(lo, a[j]);
    // while (i > 0 && a[i-1] < lo) {
    //     i--;
    //     lo = a[i];
    // }
    // dbg(i, a[i]);
    // sort(a+i, a+(i+k));
    F0R(i, n) cout << a[i] << " ";
    cout << nl;
    return 0;
}
