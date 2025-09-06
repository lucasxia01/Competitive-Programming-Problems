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
const int INF = (int)1e9 + 100;
// const ll MOD = 998244353; // 1000000007;
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

// const int MX = 3e5+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<tuple<int, int, int, int>> segs;
    F0R(i, n) {
        int s, t;
        cin >> s >> t;
        if (s <= t) {
            segs.pb({s, t, 0, i});
        } else {
            segs.pb({t, s, 1, i});
        }
    }
    sort(all(segs));
    segs.pb({INF, INF, 0, n});
    int prevMax = 0;
    bool ok = 1;
    vi ans;
    int curDir = -1;
    vi cur;
    F0R(i, n+1) {
        auto [l, r, dir, idx] = segs[i];
        if (l > prevMax) {
            // start of new segment
            // label the previous
            if (curDir == 0) {
                reverse(all(cur));
            }
            trav(u, cur) ans.pb(u+1);
            cur.clear();
        } else if (r <= prevMax) {
            ok = 0;
            break;
        } else {
            if (curDir != -1 && dir != curDir) {
                ok = 0;
                break;
            }
        }
        prevMax = r;
        curDir = dir;
        cur.pb(idx);
    }
    if (!ok) {
        cout << "No" << nl;
    } else {
        cout << "Yes" << nl;
        F0R(i, n) cout << ans[i] << ' ';
        cout << nl;
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