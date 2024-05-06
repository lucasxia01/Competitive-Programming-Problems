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
const ll MOD = 998244353;
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

const int MX = 130;

map<int, pair<vi, vi> > dp;
vi cnt;

ll mod_pow(ll a, ll b) {
    if (b == 0) return 1LL;
    ll p = mod_pow(a, b >> 1);
    p = p * p % MOD;
    if (b & 1)
        p = p * a % MOD;
    return p;
}

ll mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

ll root = 3;

typedef vector<ll> vl;
void ntt(ll* x, ll* temp, ll* roots, int N, int skip) {
	if (N == 1) return;
	int n2 = N/2;
	ntt(x     , temp, roots, n2, skip*2);
	ntt(x+skip, temp, roots, n2, skip*2);
	rep(i,0,N) temp[i] = x[i*skip];
	rep(i,0,n2) {
		ll s = temp[2*i], t = temp[2*i+1] * roots[skip*i];
		x[skip*i] = (s + t) % MOD; x[skip*(i+n2)] = (s - t) % MOD;
	}
}
void ntt(vl& x, bool inv = false) {
	ll e = mod_pow(root, (MOD-1) / sz(x));
	if (inv) e = mod_pow(e, MOD-2);
	vl roots(sz(x), 1), temp = roots;
	rep(i,1,sz(x)) roots[i] = roots[i-1] * e % MOD;
	ntt(&x[0], &temp[0], &roots[0], sz(x), 1);
}
vl conv(vl a, vl b) {
	int s = sz(a) + sz(b) - 1; if (s <= 0) return {};
	int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
	if (s <= 200) { // (factor 10 optimization for |a|,|b| = 10)
		vl c(s);
		rep(i,0,sz(a)) rep(j,0,sz(b))
			c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
		return c;
	}
	a.resize(n); ntt(a);
	b.resize(n); ntt(b);
	vl c(n); ll d = mod_pow(n, MOD-2);
	rep(i,0,n) c[i] = a[i] * b[i] % MOD * d % MOD;
	ntt(c, true); c.resize(s); return c;
}

void solve(int n) {
    if (dp.find(n) != dp.end()) return;
    vi curpaths(MX, 0);
    vi curlens(MX, 0);
    if (n == 0) {
        dp[n] = {curpaths, curlens};
        return;
    } else if (n == 1) {
        curpaths[1] = 1;
        curlens[1] = 1;
        dp[n] = {curpaths, curlens};
        return;
    }
    // split by getting the level
    int pow = 1;
    int SZ = 0;
    while (pow-1 < n) {
        pow *= 2;
        SZ++;
    }
    // give each side pow/4 - 1
    int a = pow/4 - 1, b = pow/4 - 1;
    int N = n-1-a-b;
    a += min(pow/4, N);
    b += max(0LL, N-pow/4);
    solve(a);
    solve(b);
    F0R(i, MX) if (i+1 < MX) curpaths[i+1] = mod(dp[a].f[i]+dp[b].f[i]);
    // compute cross terms with fft?
    // curlens = conv(dp[a].f, dp[b].f);
    // F0Rd(i, MX-1) curlens[i+1] = curlens[i];
    // curlens[0] = 0;
    F0R(i, SZ+1) {
        F0R(j, SZ+1) {
            if (i+j+1 >= MX) continue;
            curlens[i+j+1] += mod(dp[a].f[i]*dp[b].f[j]);
            curlens[i+j+1] %= MOD;
        }
    }
    curlens.resize(MX);
    curpaths[1]++;
    F0R(i, MX) {
        curlens[i] = mod(curlens[i]+curpaths[i]);
        curlens[i] = mod(curlens[i]+mod(dp[a].s[i]+dp[b].s[i]));
    }
    dp[n] = {curpaths, curlens};
    return;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        // for each n, compute number of length
        cnt.resize(MX, 0);
        solve(n);
        // find how many paths of each length there are
        // FOR(i, 1, min(n, MX-1)) {
        //     dbg(i, dp[n].f[i], dp[n].s[i]);
        // }
        int ans = 0;
        int accpows[m+1]; FOR(i, 1, m) accpows[i] = 1;
        accpows[0] = 0;
        FOR(i, 1, min(n, MX-1)) {
            int tmp = 0;
            ll pow = mod_pow(m, n-i);
            FOR(j, 1, m) accpows[j] = mod(accpows[j]*j);
            FOR(j, 1, m) {
                // dbg(i, accpows[j], accpows[j-1]);
                int diff = mod(accpows[j] - accpows[j-1]);
                diff = mod(diff * pow);
                tmp = mod(tmp+mod(j*diff));
            }
            ans += mod(dp[n].s[i] * tmp);
            ans %= MOD;
        }
        cout << ans << nl;
    }
    return 0;
}
