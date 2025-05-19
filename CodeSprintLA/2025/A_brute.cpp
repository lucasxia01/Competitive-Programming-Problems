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
#include "/Users/lucasxia/Competitive-Programming-Problems/Library/debug.hpp"
#else
#define dbg(...)
#define dbg_array(a, n)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 6e5+50;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
    int R, C, x, y; cin >> R >> C >> x >> y;
    int N = R*(C+1);
    int M = C*(R+1);
    int total = N+M;

    string s = "";
    char m[R][C];
    F0R(i, R) F0R(j, C) cin >> m[i][j];
    // just try every substring you can
    string best = "";
    {
        F0R(j, C) F0R(i, R) {
            string t = "";
            FOR(ii, i, R-1) {
                t += m[ii][j];
                dbg(t);
                int len = t.size();
                // try matching it everywhere
                int a = 0, b = 0;
                F0R(jj, C) {
                    F0R(k, R-len+1) {
                        // [k through k+len-1]
                        string tt = "";
                        F0R(l, len) tt += m[k+l][jj];
                        if (t == tt) {
                            b++;
                            break;
                        }
                    }
                }
                F0R(jj, R) {
                    F0R(k, C-len+1) {
                        // [k through k+len-1]
                        string tt = "";
                        F0R(l, len) tt += m[jj][k+l];
                        if (t == tt) {
                            a++;
                            break;
                        }
                    }
                }
                dbg(a, b);
                if (a == x && b == y) {
                    if (t.size() > best.size()) {
                        best = t;
                    } else if (t.size() == best.size()) {
                        if (t < best) best = t;
                    }
                }
            }
        }
    }
    swap(R, C);
    char m2[R][C];
    F0R(i, R) F0R(j, C) m2[i][j] = m[j][i];
    {
        F0R(j, C) F0R(i, R) {
            string t = "";
            FOR(ii, i, R-1) {
                t += m2[ii][j];
                int len = t.size();
                // try matching it everywhere
                int a = 0, b = 0;
                F0R(jj, C) {
                    F0R(k, R-len+1) {
                        // [k through k+len-1]
                        string tt = "";
                        F0R(l, len) tt += m2[k+l][jj];
                        if (t == tt) {
                            a++;
                            break;
                        }
                    }
                }
                F0R(jj, R) {
                    F0R(k, C-len+1) {
                        // [k through k+len-1]
                        string tt = "";
                        F0R(l, len) tt += m2[jj][k+l];
                        if (t == tt) {
                            b++;
                            break;
                        }
                    }
                }
                if (a == x && b == y) {
                    if (t.size() > best.size()) {
                        best = t;
                    } else if (t.size() == best.size()) {
                        if (t < best) best = t;
                    }
                }
            }
        }
    }
    if (best == "") cout << -1 << nl;
    else cout << best << nl;
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