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

const int MX = 4e5+5;

const ll mod = (119 << 23) + 1, root = 62; // = 998244353

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, modpow(root, mod >> s)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? mod : 0);
			ai += (ai + z >= mod ? z - mod : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	int inv = modpow(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n) out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}

int notPrime[MX];
vi primes;
bool fac[MX];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // run sieve
    for (int i = 2; i < MX; i++) {
        if (!notPrime[i]) {
            notPrime[i] = i;
            primes.pb(i);
        }
        for (int j = 0; i*primes[j] < MX; j++) {
            notPrime[i*primes[j]] = primes[j];
            if (notPrime[i] == primes[j]) break;
        }
    }
    ll l, t; cin >> l >> t;
    int n; cin >> n;
    vl v(MX, 0), revv(MX, 0); 
    F0R(i, n) {
        int x; cin >> x;
        v[x] = 1;
        revv[MX-x] = 1;
    }
    set<int> s;
    vl sum = conv(v, v);
    F0R(i, MX) if (v[i]) sum[2*i]--;
    F0R(i, sz(sum)) {
        if (sum[i] > 0) s.insert(i);
    }
    vl diff = conv(v, revv);
    F0R(i, sz(diff)) {
        if (i < MX && diff[i] > 0) s.insert(MX-i);
        if (i > MX && diff[i] > 0) s.insert(i-MX);
    }
    // get all factors of all numbers
    trav(ss, s) {
        fac[ss] = 1;
    }
    FOR(i, 1, MX) {
        for (int j = i; j < MX; j += i) {
            if (fac[j]) {
                fac[i] = 1;
                break;
            }
        }
    }

    // t%(2*l) / (2*l)
    ll rem = t%(2*l);
    int N = t/(2*l);
    // now pie for each factor of each numbers
    ll ans = 0;
    for (int f = 1; f < MX; f++) {
        if (!fac[f]) continue;
        // prime factorize it
        vi facs;
        int x = f;
        while (notPrime[x]) {
            int fac = notPrime[x];
            facs.pb(fac);
            while (x%fac == 0) x/=fac;
        }
        int m = sz(facs);
        // trav(ff, facs) cout << ff << " ";
        // cout << nl;
        int prod[1<<m];
        prod[0] = 1;
        int partial = rem*f / (2*l);
        int total = f;
        FOR(i, 1, (1<<m)-1) {
            prod[i] = prod[i-(i&-i)] * facs[__builtin_ctz(i)];
            
            // k <= rem*f / (prod[i]*(2*l))
            // prod[i] * k // f <= 1
            int mult = (__builtin_popcount(i)%2?1:-1);
            partial -= mult*rem*f / (prod[i]*(2*l));
            total -= mult*f / prod[i];
        }
        dbg(f, partial, total);
        ans = (ans+ partial + N*total)%MOD;
    } 
    cout << ans << nl;
    
    return 0;
}
