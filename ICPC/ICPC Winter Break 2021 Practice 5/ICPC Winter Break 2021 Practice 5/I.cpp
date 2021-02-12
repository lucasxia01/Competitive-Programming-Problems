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
const ll INF = (1LL<<60) + 123;
const ll MOD1 = 1000000007; // 998244353
const ll MOD2 = 998244353;
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

const int MX = 2001;

struct stringHash {
    int base;
    ll mod;
    int len;
    vi prefixHash, suffixHash, basePowers;
    stringHash(int b, ll m, int* a, int n) : base(b), mod(m) {
        len = n;
        int hash = 0;
        prefixHash.pb(0);
        for (int i = 0; i < len; i++) {
            hash = (1LL * hash * base) % mod;
            hash = (hash + a[i]) % mod;
            prefixHash.pb(hash);
        }
        hash = 0;
        suffixHash.pb(0);
        for (int i = len-1; i >= 0; i--) {
            hash = (1LL * hash * base) % mod;
            hash = (hash + a[i]) % mod;
            suffixHash.pb(hash);
            //cout << hash << endl;
        }
        int pow = 1;
        for (int i = 0; i < len; i++) { // can be changed to len/2 for optimization for palindrome
            basePowers.pb(pow);
            pow = (1LL * pow * base) % mod;
        }
    }
    
    int getPrefixHash(int a, int b) { // b is larger than a, the range is [a, b]
        return (int)((1LL*prefixHash[b+1] - 1LL*basePowers[b-a+1]*prefixHash[a]) % mod + mod) % mod;
    }
    int getSuffixHash(int a, int b) { // b is larger than a the range is [a, b]
        a = len-1-a;
        b = len-1-b;
        return (int)((1LL*suffixHash[a+1] - 1LL*basePowers[a-b+1]*suffixHash[b]) % mod + mod) % mod;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int h, w, H, W; cin >> h >> w >> H >> W;
    string P[h]; F0R(i, h) cin >> P[i];
    string M[H]; F0R(i, H) cin >> M[i];
    int p[h][w]; F0R(i, h) F0R(j, w) p[i][j] = (P[i][j]=='o');
    int m[H][W]; F0R(i, H) F0R(j, W) m[i][j] = (M[i][j]=='o');
    int temp[h];
    F0R(i, h) {
        stringHash t(101, MOD1, p[i], w);
        temp[i] = (int)t.getPrefixHash(0, w-1);
//        dbg_out(temp[i]);
    }
    stringHash sh(103, MOD2, temp, h);
    int hash = (int)sh.getPrefixHash(0, h-1);
//    cout << hash << nl;
    int temp1[W-w+1][H];
    F0R(i, H) {
        stringHash t(101, MOD1, m[i], W);
        F0R(j, W-w+1) {
            temp1[j][i] = (int)t.getPrefixHash(j, j+w-1);
//            cout << temp1[j][i] << " ";
        }
//        dbg();
    }
    int hashes[H-h+1][W-w+1];
    F0R(j, W-w+1) {
        stringHash t(103, MOD2, temp1[j], H);
        F0R(i, H-h+1) hashes[i][j] = (int)t.getPrefixHash(i, i+h-1);
    }
    int ans = 0;
    F0R(i, H-h+1) F0R(j, W-w+1) ans += (hashes[i][j] == hash);
    cout << ans << nl;
    return 0;
}
