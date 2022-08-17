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
const ll INF = (1<<29) + 123;
const ll MOD = 1e9+7; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

struct stringHash {
    int base;
    ll mod;
    int len;
    string s;
    vector<int> prefixHash, suffixHash, basePowers;
    stringHash(int b, ll m, string s) : base(b), mod(m), s(s) {
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
            //cout << hash << endl;
        }
        int pow = 1;
        for (int i = 0; i < len; i++) { // can be changed to len/2 for optimization
            basePowers.push_back(pow);
            pow = (1LL * pow * base) % mod;
        }
    }
    
    ll getPrefixHash(int a, int b) { // b is larger than a
        return ((prefixHash[b+1] - basePowers[b-a+1]*prefixHash[a]) % mod + mod) % mod;
    }
    ll getSuffixHash(int a, int b) { // b is larger than a
        a = len-1-a;
        b = len-1-b;
        return ((suffixHash[a+1] - 1LL*basePowers[a-b+1]*suffixHash[b]) % mod + mod) % mod;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s;
    cin >> s;
    int len = (int) s.length();
    int pal[len+1];
    int BASE = 59;
    stringHash sH(BASE, MOD, s);
    FOR(i, 1, len) {
        pal[i] = (sH.getPrefixHash(0, i/2-1) == sH.getSuffixHash((i+1)/2, i-1));
        //cout << (i+1)/2 << " " << i-1 << " " << sH.getSuffixHash((i+1)/2, i-1) << endl;
    }
    int ans = 0;
    pal[0] = 0;
    FOR(i, 1, len) {
        if (pal[i]) pal[i] = pal[i/2]+1;
        //cout << pal[i] << " ";
        ans += pal[i];
    }
    cout << ans << endl;
    return 0;
}
