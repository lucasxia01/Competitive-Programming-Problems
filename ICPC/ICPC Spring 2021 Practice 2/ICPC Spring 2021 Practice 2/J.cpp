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
#include <climits>

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
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;
int k, n;
map<string, vector<string> > m;
map<string, vi > lcs;
void dfs(string s) {
    if (lcs.find(s) != lcs.end()) return;
    dfs(m[s][0]);
    dfs(m[s][1]);
    vi v1 = lcs[m[s][0]];
    vi v2 = lcs[m[s][1]];
    vi v(n, 0);
    F0R(i, n) {
        int cur = v1[i];
        if (i+cur < n) cur += v2[i+cur];
        v[i] = cur;
    }
//    dbg(s);
//    F0R(i, n) cout << v1[i] << " "; cout << nl;
//    F0R(i, n) cout << v2[i] << " "; cout << nl;
//    F0R(i, n) cout << v[i] << " "; cout << nl;
    lcs[s] = v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        m.clear();
        lcs.clear();
        cin >> k;
        string s;
        getline(cin, s);
        vector<pair<string, string> > terms;
        F0R(i, k) {
            getline(cin, s);
            s += ' ';
            vector<string> v;
            string cur = "";
            F0R(i, (int)s.length()) {
                if (s[i] == ' ') {
                    v.pb(cur);
                    cur = "";
                } else cur += s[i];
            }
            if (sz(v) == 5) {
                m[v[0]] = {v[2], v[4]};
            } else {
                terms.pb({v[0], v[2]});
            }
        }
        string root; cin >> root;
        string t; cin >> t;
        n = (int)t.length();
        trav(term, terms) {
            vi v(n, 0);
            F0R(i, n) {
                int k = 0;
                F0R(j, (int)term.s.length()) {
                    if (i+k >= n) break;
                    if (t[i+k] == term.s[j]) {
                        k++;
                    }
                }
                v[i] = k;
            }
//            dbg(term.f);
//            F0R(i, n) cout << v[i] << " "; cout << nl;
            lcs[term.f] = v;
        }
        dfs(root);
        if (lcs[root][0] == n) cout << "YES" << nl;
        else cout << "NO" << nl;
    }
    return 0;
}
