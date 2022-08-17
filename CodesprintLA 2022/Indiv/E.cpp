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

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());


const int MX = 2000+5;

struct stringHash {
    int base;
    int mod;
    int len;
    string s;
    vector<int> prefixHash, suffixHash, basePowers;
    stringHash(int b, int m, string s) : base(b), mod(m), s(s) {
        len = (int) s.length();
        int hash = 0;
        prefixHash.push_back(0);
        for (int i = 0; i < len; i++) {
            hash = (1LL * hash * base) % mod;
            hash = (hash + s[i]) % mod;
            prefixHash.push_back(hash);
        }
        hash = 0;
        suffixHash.push_back(0);
        for (int i = len-1; i >= 0; i--) {
            hash = (1LL * hash * base) % mod;
            hash = (hash + s[i]) % mod;
            suffixHash.push_back(hash);
        }
        int pow = 1;
        for (int i = 0; i <= len; i++) { // can be changed to len/2 for optimization
            basePowers.push_back(pow);
            pow = (1LL * pow * base) % mod;
        }
    }
    
    int getPrefixHash(int a, int b) { // b is larger than a, the range is [a, b]
        return ((prefixHash[b+1] - 1LL*basePowers[b-a+1]*prefixHash[a]) % mod + mod) % mod;
    }
    int getSuffixHash(int a, int b) { // b is larger than a the range is [a, b]
        a = len-1-a;
        b = len-1-b;
        return ((suffixHash[a+1] - 1LL*basePowers[a-b+1]*suffixHash[b]) % mod + mod) % mod;
    }
    
};

int gr[505][505];

// find cycle
bool vis[505];
int dfs1(int s, int v) {
    // dbg(s, v);
    if (s == v) return 1;
    vis[v] = 1;
    F0R(i, 505) if (gr[v][i] && !vis[i]) if (dfs1(s, i)) return 1;
    return 0;
}

int dp[505];
int dfs2(int v) {
    // dbg(v);
    if (dp[v] != -1) return dp[v];
    int best = 0;
    F0R(i, 505) if (gr[v][i]) ckmax(best, gr[v][i] + dfs2(i));
    return dp[v] = best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string v[n];
    F0R(i, n) cin >> v[i];
    vector<stringHash> sh;
    F0R(i, n) {
        stringHash temp(101, MOD, v[i]);
        sh.pb(temp);
    }
    F0R(i, n) F0R(j, n) {
        if (i == j) {
            gr[i][j] = 0;
            continue;
        }
        int a = sz(v[i]), b = sz(v[j]);
        F0Rd(k, min(a, b)) {
            if (sh[j].getPrefixHash(0, k-1) == sh[i].getPrefixHash(a-k, a-1)) {
                gr[i][j] = k;
                // dbg(i, j, k);
                break;
            }
        }
    }
    // cycle finding
    F0R(i, n) {
        memset(vis, 0, sizeof vis);
        F0R(j, n) if (gr[i][j]) {
            if (dfs1(i, j)) {
                cout << "Shakespeare, who?" << nl;
                return 0;
            }
        }
    }
    int ans = 0;
    F0R(i, n) dp[i] = -1;
    F0R(i, n) ckmax(ans, dfs2(i));
    cout << ans << nl;
    return 0;
}
