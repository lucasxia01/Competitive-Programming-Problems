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

const int MX = 1e6+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    vector<int> phi(MX + 1);
    for (int i = 0; i <= MX; i++)
        phi[i] = i;

    for (int i = 2; i <= MX; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= MX; j += i)
                phi[j] -= phi[j] / i;
        }
    }

    // prefix sum of phi
    phi[1] = 0;
    vector<int> pre_phi(MX+1, 0);
    for (int i = 1; i <= MX; i++)
        pre_phi[i] = pre_phi[i-1] + phi[i];

    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int M = m;
        // we only care up to ~n^(2/3)
        // which ones can we do
        int w = 2;
        map<int, int> moves; // maps weight to number of times you can do it
        while (1) {
            // weight is w
            // number of things is n/w
            int cnt = pre_phi[n/w];
            if (cnt < w-1) break;
            // dbg(w, cnt);
            moves[1-w] = cnt/(w-1);
            w++;
        }
        // be greedy
        int ans = 0;
        trav(mm, moves) {
            int cur = min(m / (-mm.f), mm.s);
            m -= cur * (-mm.f);
            ans += cur;
        }
        if (m > 0) cout << -1 << nl;
        else cout << M+ans << nl;
    }
    return 0;
}

// 2, 4, 6, 8, 10
// 24, 26, 28, 210
// 46, 410
// 68 610
// 8 10

// 3, 6, 9
