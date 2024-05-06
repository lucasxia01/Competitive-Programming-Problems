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
    int n; cin >> n;
    int a[n+1]; F0R(i, n+1) cin >> a[i+1];
    // top sort and handle cycle
    // possible as long as you don't have an odd cycle by itself
    int circled[n+1]; F0R(i, n+1) circled[i] = -1;
    vi gr[n+1];
    int degcnt[n+1]; F0R(i, n+1) degcnt[i] = 0;
    FOR(i, 1, n) {
        gr[a[i]].pb(i);
        degcnt[a[i]]++;
    }
    queue<int> q;
    FOR(i, 1, n) if (degcnt[i] == 0) q.push(i);
    while (!q.empty()) {
        // deal with all children
        int cur = q.front(); q.pop();
        // check if its circled or not
        bool uncircledChild = false;
        trav(u, gr[cur]) {
            if (circled[u]==0) uncircledChild = 1;
        }
        if (uncircledChild) circled[cur] = 1;
        else circled[cur] = 0;
        degcnt[a[cur]]--;
        if (degcnt[a[cur]] == 0) q.push(a[cur]);
    }
    // now its only cycles left
    bool possible = 1;
    FOR(i, 1, n) {
        if (degcnt[i] > 0) {
            // loop through its cycle
            vi v;
            int cur = a[i];
            while (cur != i) {
                v.pb(cur);
                cur = a[cur];
            }
            v.pb(cur);
            bool hasCircled = 0;
            int start = -1;
            trav(u, v) {
                bool uncircledChild = false;
                trav(c, gr[u]) {
                    if (circled[c]==0) uncircledChild = 1;
                }
                if (uncircledChild) {
                    circled[u] = 1;
                    hasCircled = 1;
                    start = u;
                }
            }
            dbg(i, hasCircled, sz(v));
            if (!hasCircled && sz(v)%2) {
                possible = 0;
                break;
            } else if (!hasCircled) {
                start = i;
            }
            // otherwise traverse from a circled
            cur = a[start];
            bool circle = 0;
            while (cur != start) {
                if (circled[cur] == 1) {
                    circle = 1;
                } else circled[cur] = circle;
                circle = !circle;
                cur = a[cur];
            }
            trav(u, v) {
                degcnt[u] = 0;
            }
        }
    }
    if (!possible) cout << -1 << nl;
    else {
        vi ans;
        FOR(i, 1, n) {
            if (!circled[i]) ans.pb(a[i]);
        }
        cout << sz(ans) << nl;
        trav(u, ans) cout << u << " ";
        cout << nl;
    }
    return 0;
}
