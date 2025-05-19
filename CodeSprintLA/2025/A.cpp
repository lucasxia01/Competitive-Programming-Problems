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

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string s, int lim=256) { // or vector<int>
		s.push_back(0); int n = sz(s), k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

int parent[MX];
void make_set(int v) {
    parent[v] = v;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
}

void union_sets(int a, int b) {
    // merge b into a
    a = find_set(a);
    b = find_set(b);
    assert(a != b);
    parent[b] = a;
    
}

void solve() {
    int R, C, x, y; cin >> R >> C >> x >> y;
    int N = R*(C+1);
    int M = C*(R+1);
    int total = N+M;

    string s = "";
    char m[R][C];
    F0R(i, R) F0R(j, C) cin >> m[i][j];
    F0R(i, R) {
        F0R(j, C) s += m[i][j];
        s += '#';
    }
    F0R(j, C) {
        F0R(i, R) s += m[i][j];
        s += '#';
    }
    assert(s.size() == N+M);
    SuffixArray sa(s);
    dbg(sa.sa);
    dbg(sa.lcp);
    assert(total+1 == sa.lcp.size());
    // queue things up by lcp
    vi q[total];
    F0R(i, sa.lcp.size()) {
        if (i == 0) continue;
        // we need to constrain the lcp array
        if (sa.sa[i] < N) { // its a row
            int col = sa.sa[i]%(C+1);
            // we need to bound it to at most C-col length
            if (i+1 < total+1) ckmin(sa.lcp[i+1], C-col);
            ckmin(sa.lcp[i], C-col);
        } else {
            int row = (sa.sa[i]-N)%(R+1);
            // bound to at most R-row
            if (i+1 < total+1) ckmin(sa.lcp[i+1], R-row);
            ckmin(sa.lcp[i], R-row);
        }
    }
    
    // go from high to low
    pair<set<int>, set<int>> g[total+1]; // we have this many nodes
    // init this array
    F0R(i, total+1) {
        if (i == 0) continue;
        make_set(i);
        // set the merge queue
        q[sa.lcp[i]].pb(i); // i and i-1

        if (sa.sa[i] < N) { // its a row
            int row_idx = sa.sa[i]/(C+1);
            g[i].f.insert(row_idx);
            dbg(i, sa.sa[i], sa.lcp[i], "row", row_idx);
        } else { // its a column
            int col_idx = (sa.sa[i]-N)/(R+1);
            g[i].s.insert(col_idx);
            dbg(i, sa.sa[i], sa.lcp[i], "col", col_idx);
        }
    }
    vi ans;
    F0Rd(matchLen, total) {
        if (matchLen == 0) break;
        // merge everything here
        vi merged;
        trav(j, q[matchLen]) {
            dbg(matchLen, j);
            int i = find_set(j);
            int ii = find_set(j-1);
            // merge i with ii
            if ((g[ii].f.size() + g[ii].s.size()) >= (g[i].f.size() + g[i].s.size())) {
                dbg("merging", find_set(i), "into", find_set(ii));
                trav(k, g[i].f) {
                    g[ii].f.insert(k);
                }
                trav(k, g[i].s) {
                    g[ii].s.insert(k);
                }
                merged.pb(ii);
                union_sets(ii, i);
            } else {
                dbg("merging", find_set(ii), "into", find_set(i));
                trav(k, g[ii].f) {
                    g[i].f.insert(k);
                }
                trav(k, g[ii].s) {
                    g[i].s.insert(k);
                }
                merged.pb(i);
                union_sets(i, ii);
            }
        }
        if (matchLen == C && x == 1 && y == 0) {
            // just add everything that starts a row
            F0R(i, total+1) {
                if (i == 0) continue;
                if (sa.sa[i] < N && sa.sa[i]%(C+1) == 0)
                    merged.pb(i);
            }
        }
        if (matchLen == R && x == 0 && y == 1) {
            // just add everything
            F0R(i, total+1) {
                if (i == 0) continue;
                if (sa.sa[i] >= N && (sa.sa[i]-N)%(R+1) == 0)
                    merged.pb(i);
            }
        }
        trav(val, merged) {
            if (val != find_set(val)) continue;
            // check it for x and y things
            dbg(matchLen, val, g[val].f.size(), g[val].s.size());
            trav(z, g[val].f) dbg("row", z);
            trav(z, g[val].s) dbg("col", z);
            if (g[val].f.size() == x && g[val].s.size() == y) {
                ans.pb(val);
            }
        }
        if (sz(ans)) {
            // the length is exactly matchLen
            // the index is exactly ans[0]
            F0R(j, matchLen) {
                cout << s[sa.sa[ans[0]]+j];
            }
            cout << nl;
            return;
        }
    }
    cout << -1 << nl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    while (T--) {
        solve();
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