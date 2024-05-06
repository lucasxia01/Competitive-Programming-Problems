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

const int MX = 3e5+5;

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a)%MOD;
        a = (a * a)%MOD;
        b >>= 1;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        ll n; cin >> n;
        // count shit
        vector<map<ll, pl> > v(62); // pair is sum, cnt
        v[0][n] = {1, 1};
        int j = 1;
        while (1) {
            trav(p, v[j-1]) {
                if (p.f == 1) continue;
                v[j][(p.f+1)/2].f += 2*p.s.f;
                v[j][(p.f+1)/2].f %= MOD;
                v[j][(p.f+1)/2].s += p.s.s;
                v[j][(p.f+1)/2].s %= MOD;
                v[j][p.f/2].f += 2*p.s.f + p.s.s;
                v[j][p.f/2].f %= MOD;
                v[j][p.f/2].s += p.s.s;
                v[j][p.f/2].s %= MOD;
            }
            if (sz(v[j]) == 0) break;
            j++;
        }
        // now do some math !
        ll ans = 0;
        F0R(i, j) {
            trav(p, v[i]) {
                dbg(i, p.f, p.s.f, p.s.s);
                if (p.f == 1) {
                    ans += p.s.f;
                    ans %= MOD;
                    continue;
                }
                int l = (p.f+1)/2, r = p.f/2;
                // number of leaves == length of range!
                ll tmp = p.s.f * (binpow(2, l) - 1);
                tmp %= MOD;
                tmp *= (binpow(2, r) - 1);
                tmp %= MOD;
                ans += tmp;
                ans %= MOD;
            }
        }
        cout << ans << nl;
    }
    return 0;
}
