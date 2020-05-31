#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cassert>

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

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 100000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MX = 1005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int x, y;
    for (int n; cin >> n && n;) {
        int v[n]; F0R(i, n) cin >> v[i];
        int m; cin >> m;
        string s; cin >> s;
        int len = (int) s.length();
        set<char> unk;
        stack<char> ops;
        vector<char> postfix;
        F0R(i, len) {
            if (s[i] == ')') {
                assert(!ops.empty());
                postfix.pb(ops.top()); ops.pop();
            } else if (s[i] >= 'a' && s[i] <= 'z') {
                unk.insert(s[i]);
                postfix.pb(s[i]);
            } else if (s[i] == '+' || s[i] == '*' || s[i] == '-') ops.push(s[i]);
        }
        assert(ops.empty());
        // map variables and process for all 5! permutations
        assert(n == sz(unk));
        map<char, int> var;
        int c = 0;
        trav(a, unk) var[a] = c++;
        bool ok = false;
        sort(v, v+n);
        do {
            // process postfix
            stack<int> st;
            trav(a, postfix) {
                if (a >= 'a' && a <= 'z') st.push(v[var[a]]);
                else if (a == '+') {
                    x = st.top(); st.pop();
                    y = st.top(); st.pop();
                    st.push(x+y);
                } else if (a == '-') {
                    x = st.top(); st.pop();
                    y = st.top(); st.pop();
                    st.push(y-x);
                } else if (a == '*') {
                    x = st.top(); st.pop();
                    y = st.top(); st.pop();
                    st.push(x*y);
                }
            }
            assert(sz(st) == 1);
            if (st.top() == m) {
                ok = 1; break;
            }
        } while (next_permutation(v, v+n));
        cout << (ok ? "YES" : "NO") << nl;
    }
    cin >> x;
    return 0;
}
