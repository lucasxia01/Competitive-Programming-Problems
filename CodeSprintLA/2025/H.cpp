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
// const ll INF = (1LL<<55) + 123;
const ll MOD = 1000000007;
// const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

#ifdef DBG
#include "/Users/lucasxia/Competitive-Programming-Problems/Library/debug.hpp"
#else
#define dbg(...)
#define dbg_array(a, n)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e6+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n], b[n];
    F0R(i, n) cin >> a[i];
    F0R(i, n) cin >> b[i];
    ll ans = 1;
    if (a[0] != 0 || b[1] != 0 || a[1] != b[0]) {
        ans = 0;
    }
    map<pair<int, pi>, int> cnt;
    int d = abs(a[0]-b[0]);
    F0R(i, n) {
        // place it into each of the places it could be
        if ((a[i]+b[i])%2 != d%2) {
            ans = 0;
        }
        if (a[i] <= b[i]) {
            if (b[i]-a[i] == d) {
                // its on a's side
                cnt[{0, {0, a[i]}}]++;
            } else if (b[i]-a[i] > d) {
                ans = 0;
            } else {
                int gap = b[i]-a[i];
                int dista = (d-gap)/2;
                // its in between the two
                cnt[{2, {dista, a[i]-dista}}]++;
            }
        } else {
            if (a[i]-b[i] == d) {
                // its on b's side
                cnt[{1, {0, b[i]}}]++;
            } else if (a[i]-b[i] > d) {
                ans = 0;
            } else {
                int gap = a[i]-b[i];
                int dista = (d+gap)/2;
                // its in between the two
                cnt[{2, {dista, a[i]-dista}}]++;
            }
        }
    }
    // now check to see if everything exists
    // we need to check that everything in between exists
    FOR(i, 1, d-1) {
        if (cnt.find({2, {i, 0}}) == cnt.end()) {
            ans = 0;
        }
    }
    trav(p, cnt) {
        // we must check that the previous exists
        if (p.f.f == 0 || p.f.f == 1) {
            if (p.f.s.s != 0) {
                if (cnt.find({p.f.f, {0, p.f.s.s-1}}) == cnt.end()) {
                    ans = 0;
                } else {
                    for (int i = 0; i < p.s; i++) {
                        ans = (ans * cnt[{p.f.f, {0, p.f.s.s-1}}])%MOD;
                    }
                }
            } else {
                if (p.s != 1) {
                    ans = 0;
                }
            }
        } else { // its in between
            if (p.f.s.s != 0) {
                if (cnt.find({p.f.f, {p.f.s.f, p.f.s.s-1}}) == cnt.end()) {
                    ans = 0;
                } else {
                    for (int i = 0; i < p.s; i++) {
                        ans = (ans * cnt[{p.f.f, {p.f.s.f, p.f.s.s-1}}])%MOD;
                    }
                }
            } else {
                if (p.s != 1) {
                    ans = 0;
                }
            }
        }
    }
    cout << ans << nl;
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