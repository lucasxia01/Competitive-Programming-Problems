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
bool vis[26];
int m[26][26];

string find_cycle(int cur, int x) {
//    dbg(x, vis[x]);
    if (vis[x]) return " ";
    vis[x] = 1;
    F0R(i, 26) if (m[x][i]) {
        string ret = "";
        if (i == cur) return ret+(char)('a'+x);
        ret = find_cycle(cur, i);
        if (ret == " ") continue;
        else return ret+(char)(x+'a');
    }
    return " ";
}

string dfs(int x) {
    string ans = "";
    F0R(i, 26) if (m[x][i]) {
        string ret = dfs(i);
        if (ret.length() > ans.length()) ans = ret;
    }
    ans += (char)(x+'a');
    return ans;
}

void print(string s) {
    int n = (int)(s.length()+1)/2;
    F0R(i, n) {
        cout << s.substr(0, n) << nl;
        s = s.substr(1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        F0R(i, 26) F0R(j, 26) m[i][j] = 1;
        string s; F0R(i, n) { cin >> s; m[s[0]-'a'][s[1]-'a'] = 0; }
        string ans = "a";
        bool ok = 0;
        F0R(i, 26) {
            memset(vis, 0, sizeof(vis));
            string ret = find_cycle(i, i);
            reverse(all(ret));
            if (ret != " ") {
                ok = 1;
                while (ret.length() < 39) ret += ret;
                ans = ret.substr(0, 39);
                break;
            }
        }
        if (!ok) {
            F0R(i, 26) {
                string ret = dfs(i);
                reverse(all(ret));
                if (ret.length() > ans.length()) ans = ret;
            }
        }
        print(ans);
    }
    return 0;
}
