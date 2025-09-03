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

// const int MX = 3e5+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        string s; cin >> s;
        // if everything is just 1 letter, its impossible
        string t = "LIT";
        int c[3] = {0, 0, 0};
        F0R(i, n) {
            if (s[i] == 'L') c[0]++;
            if (s[i] == 'I') c[1]++;
            if (s[i] == 'T') c[2]++;
        }
        if (c[0] == n || c[1] == n || c[2] == n) {
            cout << -1 << nl;
            continue;
        }
        // find the most popular letter, generate the other two letters from it
        int hi = max_element(c, c+3)-c;
        int lo = min_element(c, c+3)-c;
        int mid = 0; 
        if (mid == hi || mid == lo) mid = 1;
        if (mid == hi || mid == lo) mid = 2;
        // find an instance of the hi letter
        vi ans;
        F0R(i, n-1) {
            // if one of i or i+1 is the hi letter and the other is not
            if ((s[i] == t[hi] && s[i+1] != t[hi]) || (s[i] != t[hi] && s[i+1] == t[hi])) {
                // spam c[hi]-c[lo] times
                if (s[i] == t[hi]) {
                    // otherletter is not s[i] or s[i+1]
                    char otherLetter = (s[i+1] == t[lo]) ? t[mid] : t[lo];
                    char curLetter = s[i+1];
                    dbg(otherLetter);
                    F0R(j, c[hi]-c[lo]) {
                        s.insert(i+1, 1, otherLetter);
                        ans.pb(i+1);
                        s.insert(i+1, 1, curLetter);
                        ans.pb(i+1);
                    }
                } else if (s[i+1] == t[hi]) {
                    char otherLetter = (s[i] == t[lo]) ? t[mid] : t[lo];
                    char curLetter = s[i];
                    dbg(otherLetter);
                    F0R(j, c[hi]-c[lo]) {
                        s.insert(i+1+2*j, 1, otherLetter);
                        ans.pb(i+1+2*j);
                        s.insert(i+1+2*j+1, 1, curLetter);
                        ans.pb(i+1+2*j+1);
                    }
                } else {
                    assert(0);
                }
                break;
            }
        }
        dbg(s);
        // now do the same with the mid letter
        F0R(i, n-1) {
            // if one of i or i+1 is the mid letter and the other is not
            if ((s[i] == t[mid] && s[i+1] != t[mid]) || (s[i] != t[mid] && s[i+1] == t[mid])) {
                // spam c[mid]-c[lo] times
                if (s[i] == t[mid]) {
                    // otherletter is not s[i] or s[i+1]
                    char otherLetter = (s[i+1] == t[lo]) ? t[hi] : t[lo];
                    char curLetter = s[i+1];
                    dbg(otherLetter);
                    F0R(j, c[mid]-c[lo]) {
                        s.insert(i+1, 1, otherLetter);
                        ans.pb(i+1);
                        s.insert(i+1, 1, curLetter);
                        ans.pb(i+1);
                    }
                } else if (s[i+1] == t[mid]) {
                    char otherLetter = (s[i] == t[lo]) ? t[hi] : t[lo];
                    char curLetter = s[i];
                    dbg(otherLetter);
                    F0R(j, c[mid]-c[lo]) {
                        s.insert(i+1+2*j, 1, otherLetter);
                        ans.pb(i+1+2*j);
                        s.insert(i+1+2*j+1, 1, curLetter);
                        ans.pb(i+1+2*j+1);
                    }
                } else {
                    assert(0);
                }
                break;
            }
        }
        dbg(s);
        cout << sz(ans) << nl;
        trav(a, ans) cout << a << nl;
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