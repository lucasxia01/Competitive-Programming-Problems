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

const int MX = 1e5+5;

ll pow2[MX];
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    pow2[0] = 1;
    FOR(i, 1, MX-1) {
        pow2[i] = (pow2[i-1]*2)%MOD;
    }
    int t = 1; 
    while (t--) {
        int n; cin >> n;
        vpi a(n); F0R(i, n) cin >> a[i].f;
        F0R(i, n) a[i].s = i+1;
        sort(all(a));
        reverse(all(a));
        // total num of divisors is nlogn
        int b[n+1]; F0R(i, n+1) b[i] = 0;
        vi divisors[n+1];
        FOR(i, 1, n) {
            for (int j = i; j <= n; j += i) {
                divisors[j].pb(i);
            }
        }
        int unpicked = n;
        int ans = 0;
        trav(p, a) {
            dbg(p.f, p.s);
            // go through its divisors and see what needs to not be picked
            int cnt = 0;
            trav(d, divisors[p.s]) {
                if (b[d] == 0) {
                    b[d] = 1;
                    cnt++;
                    unpicked--;
                }
            }
            dbg(p.f, cnt, unpicked);
            ll tmp = ((pow2[cnt]-1)*pow2[unpicked])%MOD;
            dbg(tmp*p.f);
            ans += (tmp*p.f)%MOD;
            ans %= MOD;
        }
        cout << ans << nl;
    }
    return 0;
}
