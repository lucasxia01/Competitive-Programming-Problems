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
// const ll INF = (1LL<<55) + 123;
// const ll MOD = 998244353; // 1000000007;
// const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

#ifdef DBG
#include "../../Library/debug.hpp"
#else
#define dbg(...)
#define dbg_array(a, n)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e6+5;

vpi gr[MX];
vi ans;
bool used[MX];
bool dfs(int v, int start, bool first) {
    dbg(v);
    if (v == start && !first) return true;
    while (!gr[v].empty()) {
        int u = gr[v].back().f;
        int idx = gr[v].back().s;
        gr[v].pop_back();
        if (used[abs(idx)]) continue;
        used[abs(idx)] = true;
        dbg(u, idx);
        if (dfs(u, start, false)) {
            if (idx < 0) ans.pb(-idx);
            return true;
        } else return false;
    }
    return (v==start);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        ans.clear();
        int n; cin >> n;
        int a[n]; F0R(i, n) cin >> a[i];
        int b[n]; F0R(i, n) cin >> b[i];
        // find cycles repeatedly, can we do this fast?
        // dfs, if we reach a dead end, then its false
        // otherwise, we're just processing each node and its edge once
        F0R(i, n+1) gr[i].clear();
        F0R(i, n+1) used[i] = 0;
        F0R(i, n) {
            gr[a[i]].pb({b[i], i+1});
            gr[b[i]].pb({a[i], -(i+1)});
        }
        bool ok = 1;
        FOR(i, 1, n) {
            while (!gr[i].empty()) {
                if (!dfs(i, i, true)) {
                    ok = 0;
                    break;
                }
            }
            if (!ok) break;
        }
        if (ok) {
            cout << sz(ans) << nl;
            trav(i, ans) cout << i << " ";
            cout << nl;
        } else cout << -1 << nl;
    }
    return 0;
}

/*
Basic Debugging:
n = 0, 1, 2, MAX?
Generate max cases, especially if simple to generate.
memory usage?
OVERFLOW?

Wrong answer:
Print your solution! Print debug output, as well.
Are you clearing all data structures between test cases?
Can your algorithm handle the whole range of input?
Read the full problem statement again.
Do you handle all corner cases correctly?
Have you understood the problem correctly?
Any uninitialized variables?
Any overflows?
Confusing N and M, i and j, etc.?
Are you sure your algorithm works?
What special cases have you not thought of?
Are you sure the STL functions you use work as you think?
Add some assertions, maybe resubmit.
Create some testcases to run your algorithm on.
Go through the algorithm for a simple case.
Go through this list again.
Explain your algorithm to a teammate.
Ask the teammate to look at your code.
Go for a small walk, e.g. to the toilet.
Is your output format correct? (including whitespace)
Rewrite your solution from the start or let a teammate do it.

Runtime error:
Have you tested all corner cases locally?
Any uninitialized variables?
Are you reading or writing outside the range of any vector?
Any assertions that might fail?
Any possible division by 0? (mod 0 for example)
Any possible infinite recursion?
Invalidated pointers or iterators?
Are you using too much memory?
Debug with resubmits (e.g. remapped signals, see Various).

Time limit exceeded:
Do you have any possible infinite loops?
What is the complexity of your algorithm?
Are you copying a lot of unnecessary data? (References)
How big is the input and output? (consider scanf)
Avoid vector, map. (use arrays/unordered_map)
What do your teammates think about your algorithm?

Memory limit exceeded:
What is the max amount of memory your algorithm should need?
Are you clearing all data structures between test cases?
*/