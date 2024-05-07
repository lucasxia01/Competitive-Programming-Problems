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
const ll MOD = 1000000007LL; // 998244353
const ll MOD2 = 1000000009LL;
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

const int MX = 5e5+5;

struct arrayHash {
    int base;
    int mod;
    int len;
    vi s;
    vector<int> prefixHash, revHash, basePowers;
    arrayHash(int b, int m, vi s) : base(b), mod(m), s(s) {
        len = (int) s.size();
        int hash = 0;
        prefixHash.push_back(0);
        for (int i = 0; i < len; i++) {
            hash = (1LL * hash * base) % mod;
            hash = (hash + s[i]) % mod;
            prefixHash.push_back(hash);
        }
        hash = 0;
        revHash.push_back(0);
        for (int i = len-1; i >= 0; i--) {
            hash = (1LL * hash * base) % mod;
            hash = (hash + s[i]) % mod;
            revHash.push_back(hash);
        }
        int pow = 1LL;
        for (int i = 0; i <= len; i++) { // can be changed to len/2 for optimization
            basePowers.push_back(pow);
            pow = (1LL * pow * base) % mod;
        }
    }
    
    int getHash(int a, int b) { // b is larger than a, the range is [a, b]
        return ((prefixHash[b+1] - 1LL*basePowers[b-a+1]*prefixHash[a]) % mod + mod) % mod;
    }
    int getRevHash(int a, int b) { // b is larger than a the range is [a, b]
        a = len-1LL-a;
        b = len-1LL-b;
        return ((revHash[a+1] - 1LL*basePowers[a-b+1]*revHash[b]) % mod + mod) % mod;
    }
    
};

void solve() {
    int n, k; cin >> n >> k;
    vi a(n); F0R(i, n) cin >> a[i];
    vi b(n); F0R(i, n) cin >> b[i];
    arrayHash aSH(101, MOD, a); // initializing the string hash
    arrayHash aSH2(103, MOD2, a);
    arrayHash bSH(101, MOD, b); // initializing the string hash
    arrayHash bSH2(103, MOD2, b);
    bool ok = 0;
    bool equal = 0;
    if (aSH.getHash(0, n-1) == bSH.getHash(0, n-1) && aSH2.getHash(0, n-1) == bSH2.getHash(0, n-1)) equal = 1;
    if (n == 2) {
        if (a[0] != a[1]) ok = (equal == (k%2 == 0));
        else ok = 1;
    } else {
        if (k != 1 && equal) ok = 1;
        if (k > 0) {
            FOR(i, 1, n-1) {
                if (aSH.getHash(0, i-1) == bSH.getHash(n-i, n-1) && aSH2.getHash(0, i-1) == bSH2.getHash(n-i, n-1)) {
                    if (aSH.getHash(i, n-1) == bSH.getHash(0, n-i-1) && aSH2.getHash(i, n-1) == bSH2.getHash(0, n-i-1)) {
                        ok = 1;
                    }
                }
            }
        }
    }
    cout << (ok?"YES":"NO") << nl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    FOR(i, 1, t) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
