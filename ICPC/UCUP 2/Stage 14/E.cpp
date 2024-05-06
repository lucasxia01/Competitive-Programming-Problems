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
    vi gr[n+1];
    int degcnt[n+1];
    F0R(i, n+1) {
        degcnt[i] = 0;
    }
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        gr[u].pb(v);
        gr[v].pb(u);
        degcnt[u]++;
        degcnt[v]++;
    }
    if (n == 1) {
        cout << 2 << nl;
        return 0;
    } else if (n == 2) {
        cout << 1 << nl;
        return 0;
    }
    queue<int> q;
    queue<int> leaves;
    bool dead[n+1]; FOR(i, 1, n) dead[i] = 0;
    FOR(i, 1, n) {
        // find stuff to delete
        if (degcnt[i] == 2) {
            // check all of its nbors!
            trav(u, gr[i]) if (degcnt[u] == 1) {
                q.push(u);
            }
        }
        if (degcnt[i] == 1) {
            leaves.push(i);
        }
    }
    auto check = [&](int nbor) {
        trav(nbor2, gr[nbor]) {
            if (dead[nbor2]) continue;
            assert(degcnt[nbor] == 1);
            degcnt[nbor]--;
            degcnt[nbor2]--;
            if (degcnt[nbor2] == 2 && !dead[nbor2]) {
                trav(nbor3, gr[nbor2]) if (degcnt[nbor3] == 1 && !dead[nbor3]) {
                    q.push(nbor3);
                }
            }
            if (degcnt[nbor2] == 1 && !dead[nbor2]) {
                // check if it connects to a degree 2 thing first
                bool ok = 0;
                trav(nbor3, gr[nbor2]) if (degcnt[nbor3] == 2 && !dead[nbor3]) {
                    q.push(nbor2);
                    ok = 1;
                }
                leaves.push(nbor2);
            }
        }
    };
    int alive = n;
    int ans = 0;
    while (alive) {
        // get rid of all the dead stuff
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dead[u]) continue;
            int nbor = -1;
            trav(v, gr[u]) {
                if (!dead[v]) {
                    nbor = v;
                    break;
                }
            }
            if (nbor == -1) {
                continue;
            }
            dbg("deleting for free", u);
            ans++;
            // delete its nbor too
            degcnt[u]--;
            degcnt[nbor]--;
            assert(degcnt[nbor] <= 1);
            dead[u] = 1;
            dead[nbor] = 1;
            alive--;
            alive--;
            check(nbor);
        }
        // no more free things to kill
        // pick a leaf and hack away at it
        if (leaves.empty()) assert(!alive);
        while (!leaves.empty()) {
            int l = leaves.front(); leaves.pop();
            if (dead[l]) continue;
            dbg("deleting for one", l);
            // hack away at it
            ans += 2;
            dead[l] = 1;
            alive--;
            check(l);
            break;
        }
    }
    cout << ans << nl;
    return 0;
}
