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

const int MAX_N = 100011;
const int MX = 1<<20;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

/*
 String Hashing class
 Finds prefix and suffix hashes and uses this to compute a prefix/suffix hash for any substring
 Tested on Codeforces Global Round 7 D1/D2 (3/19/2020)
 */
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n; string s; cin >> s;
        stringHash SH(101, MOD, s); // initializing the string hash
        int ans = 0, cnt = 0;
        bool ok = 1;
        int i = 0;
        int j = 0;
        while (i < n) {
            if (i-j > 0 && SH.getPrefixHash(j, i) == SH.getSuffixHash(j, i)) {
                ans++;
                ok = 1;
                cnt = 0;
                j = i+1;
                i++;
                continue;
            }
            if (s[i] == '(') cnt++;
            else cnt--;
            if (cnt < 0) ok = 0;
            if (cnt == 0 && ok) {
                ans++;
                ok = 1;
                cnt = 0;
                j = i+1;
            }
            i++;
        }
        cout << ans << " " << n-j << endl;
    }
    
    // cout << (SH.getPrefixHash(0, len/2-1) == SH.getSuffixHash(len-len/2, len-1)) << endl;
    return 0;
}


