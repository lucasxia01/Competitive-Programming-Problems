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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a%b);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n, v[3]; cin >> n;
    F0R(i, 3) cin >> v[i];
    ll a[n]; F0R(i, n) cin >> a[i];
    // for each one, compute the costs for all 7 options
    // get the 3 best for every subset
    vpi best[8];
    F0R(i, n) {
        F0R(j, 8) {
            if (j == 0) continue;
            ll pow = 1;
            F0R(k, 3) {
                if (j & (1 << k)) {
                    int g = gcd(pow, v[k]);
                    pow *= v[k]/g;
                }
            }
            best[j].pb({(pow - (a[i]%pow))%pow, i});
        }
    }
    FOR(i, 1, 7) sort(all(best[i]));
    // try combining all subsets of these 7
    int ans = 1e18 + 5;
    F0R(i, 1<<14) {
        int ii = i;
        set<int> s;
        ll cost = 0;
        int mask = 0;
        int cnt = 0;
        bool ok = 1;
        F0R(j, 7) {
            int idx = ii%4;
            if (idx < 3) {
                if (idx < n) {
                    pi p = best[j+1][idx];
                    cnt++;
                    s.insert(p.s);
                    cost += p.f;
                } else {
                    ok = 0;
                }
                mask |= (j+1);
            }
            ii/=4;
        }
        if (!ok || mask != 7 || sz(s) != cnt) continue;
        dbg(i, cost);
        ckmin(ans, cost);
    }
    cout << ans << nl;
    return 0;
}
