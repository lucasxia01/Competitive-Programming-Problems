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
const ll MOD1 = 1000000007;
const ll MOD2 = 998244353;
const int base1 = 101;
const int base2 = 107;
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

struct stringHash {
    ll base;
    ll mod;
    int len;
    string s;
    vector<ll> prefixHash, suffixHash, basePowers;
    stringHash(ll b, ll m, string s) : base(b), mod(m), s(s) {
        len = (int) s.length();
        ll hash = 0;
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
        ll pow = 1;
        for (int i = 0; i <= len; i++) {
            basePowers.push_back(pow);
            pow = (1LL * pow * base) % mod;
        }
    }
    
    ll getPrefixHash(int a, int b) { // b is larger than a
        return ((prefixHash[b+1] - (1LL*basePowers[b-a+1]*prefixHash[a])%mod) % mod + mod) % mod;
    }
    ll getSuffixHash(int a, int b) { // b is larger than a
        a = len-1-a;
        b = len-1-b;
        return ((suffixHash[a+1] - (1LL*basePowers[a-b+1]*suffixHash[b]) % mod) % mod + mod) % mod;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int len = (int)s.length();
        int c = 0;
        F0R(i, len) {
            if (s[i] == s[len-i-1]) c++;
            else break;
        }
        if (c == len) {
            cout << s << endl;
            continue;
        }
        // [c, len-1-c]
        // hashing really
        int len2 = len-2*c;
        string s2 = s.substr(c, len2);
        stringHash sH1(101, MOD1, s2);
        stringHash sH2(107, MOD2, s2);
        int lngP = 0, lngS = 0;
        //cout << "0 " + s2 << endl;
        FOR(i, c, len-c-1) {
            if (sH1.getPrefixHash(0, i-c) == sH1.getSuffixHash(0, i-c) &&
                sH2.getPrefixHash(0, i-c) == sH2.getSuffixHash(0, i-c)) {
                ckmax(lngP, i-c+1);
            }
            if (sH1.getPrefixHash(i-c, len2-1) == sH1.getSuffixHash(i-c, len2-1) &&
                sH2.getPrefixHash(i-c, len2-1) == sH2.getSuffixHash(i-c, len2-1)) {
                ckmax(lngS, len2-i+c);
            }
        }
        if (lngP > lngS) {
            cout << s.substr(0, c+lngP) + s.substr(len-c) << endl;
        } else cout << s.substr(0, c) + s.substr(len-lngS-c) << endl;
        
        
    }
    return 0;
}
