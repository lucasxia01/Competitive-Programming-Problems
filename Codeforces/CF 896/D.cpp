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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n; cin >> n;
        ll sum = 0;
        int a[n]; F0R(i, n) cin >> a[i];
        F0R(i, n) sum += a[i];
        if (sum != 2*n) {
            cout << "NO" << nl;
            continue;
        }
        // now see how many non-1
        int m = 0;
        F0R(i, n) m += (a[i]!=1);
        // put the max dudes in the middle?
        vpi v; F0R(i, n) v.pb({a[i], i});
        sort(all(v));
        reverse(all(v));
        // F0R(i, m) {
        //     dbg(i, v[i].f, v[i].s);
        // }
        // all must be 2s or all not 2s
        bool alltwos = 1, anytwo = 0;
        F0R(i, m) {
            alltwos &= (v[i].f == 2);
            anytwo |= (v[i].f == 2);
        }
        vpi ans;
        bool ok = 1;
        if (alltwos) {
            assert(n == m);
            // put them all in the center
            F0R(i, n) ans.pb({i, (i+1)%n});
        } else if (m%2 == 0) {
            if (v[1].f == 2) ok = 0;
            // connect to first two
            if (ok) {
                ans.pb({v[0].s, v[1].s});
                ans.pb({v[0].s, v[1].s});
                v[0].f -= 2;
                v[1].f -= 2;
                FOR(i, 2, m-1) {
                    ans.pb({v[i].s, v[i-2].s});
                    assert(v[i-2].f > 0);
                    assert(v[i].f > 0);
                    v[i].f--;
                    v[i-2].f--;
                }
                int ptr = 0;
                FOR(i, m, n-1) {
                    while (v[ptr].f == 0) ptr++;
                    ans.pb({v[ptr].s, v[i].s});
                    v[ptr].f--;
                }
            }
        } else if (m == 3) {
            // if something is a 2, we're dead
            F0R(i, m) if (v[i].f == 2) ok = 0;
            if (ok) {
                // put them all in the center
                ans.pb({v[0].s, v[1].s});
                ans.pb({v[1].s, v[2].s});
                ans.pb({v[2].s, v[0].s});
                v[0].f -= 2;
                v[1].f -= 2;
                v[2].f -= 2;
                int ptr = 0;
                FOR(i, m, n-1) {
                    while (v[ptr].f == 0) ptr++;
                    ans.pb({v[ptr].s, v[i].s});
                    v[ptr].f--;
                }
            }
        } else {
            if (v[1].f == 2) ok = 0;
            ans.pb({v[0].s, v[1].s});
            ans.pb({v[0].s, v[1].s});
            v[0].f -= 2;
            v[1].f -= 2;
            FOR(i, 2, m-2) {
                ans.pb({v[i].s, v[i-2].s});
                v[i].f--;
                v[i-2].f--;
            }
            if (v[0].f > 0) {
                ans.pb({v[0].s, v[m-1].s});
                v[0].f--; v[m-1].f--;
            } else if (v[2].f > 0 && m > 5) {
                ans.pb({v[2].s, v[m-1].s});
                v[2].f--; v[m-1].f--;
            } else {
                // try out different number of things in center
                if (m == 5 && !anytwo) {
                    // we can put them all in center
                    ans.clear();
                    v[0].f += 2;
                    v[1].f += 2;
                    FOR(i, 2, m-2) {
                        v[i].f++;
                        v[i-2].f++;
                    }
                    
                    F0R(i, m) {
                        ans.pb({v[i].s, v[(i+1)%m].s});
                        v[i].f--;
                        v[(i+1)%m].f--;
                    }
                } else ok = 0;
            }

            if (ok) {
                int ptr = 0;
                FOR(i, m, n-1) {
                    while (v[ptr].f == 0) ptr++;
                    ans.pb({v[ptr].s, v[i].s});
                    v[ptr].f--;
                }
            }
        }
        if (!ok) cout << "NO" << nl;
        else {
            cout << "YES" << nl;
            trav(x, ans) cout << x.f+1 << " " << x.s+1 << nl;
        }

    }
    return 0;
}
