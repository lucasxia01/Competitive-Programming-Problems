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

const int MX = 1e6+5;

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
    
    ll calc(int i) {
//        dbg(s.substr(i+1), getPrefixHash(i+1, len-1));
        return (1LL*getPrefixHash(0, i-1)*basePowers[len-1-i]+getPrefixHash(i+1, len-1))%mod;
    }
    
};
set<ll> s[MX];
vector<pair<string, int> > v[MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    stringHash sh1(101, MOD, "ose");
//    stringHash sh2(101, MOD, "oseose");
//    dbg(sh1.getPrefixHash(0, 2), sh2.getPrefixHash(0, 2), sh2.getPrefixHash(3, 5))
    int n; cin >> n;
    F0R(i, n) {
        string t; cin >> t;
        stringHash sh(101, MOD, t);
        int hash = sh.getPrefixHash(0, (int)t.length()-1);
        s[t.length()].insert(hash);
        v[t.length()].pb({t, i});
    }
    vector<pair<int, string> > ans;
    FOR(i, 1, MX-1) {
        trav(t, v[i]) {
            stringHash sh(101, MOD, t.f);
            F0R(j, t.f.length()) {
                int hash = sh.calc(j);
                if (s[i-1].find(hash) != s[i-1].end()) {
                    ans.pb({t.s, t.f});
                    break;
                }
            }
        }
    }
    if (sz(ans) == 0) {
        cout << "NO TYPOS" << nl;
        return 0;
    }
    sort(all(ans));
    trav(a, ans) cout << a.s << nl;
    return 0;
}
