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
const ll INF = 2e9+1;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s; cin >> s;
    int n = (int)s.length()/2;
    int freq[26] = {};
    F0R(i, 2*n) freq[s[i]-'a']++;
    int hi = 0, maxIdx = -1, diff = 0;
    F0R(i, 26) {
        if (ckmax(hi, freq[i])) maxIdx = i;
        if (freq[i]) diff++;
    }
    if (hi > n) {
        if (hi >= 2*n-2 && diff <= 2) cout << "NO" << nl;
        else {
            cout << "YES" << nl;
            F0R(i, freq[maxIdx]/2) cout << (char)('a'+maxIdx);
            F0R(i, 26) if (i != maxIdx && freq[i]) {
                cout << (char)('a'+i);
                break;
            }
            FOR(i, freq[maxIdx]/2, freq[maxIdx]-1) cout << (char)('a'+maxIdx);
            bool first = true;
            F0R(i, 26) if (i != maxIdx) F0R(j, freq[i])  {
                if (first) first = !first;
                else cout << (char)('a'+i);
            }
            cout << nl;
        }
    } else {
        cout << "YES" << nl;
        F0R(i, 26) F0R(j, freq[i]) cout << (char)('a'+i);
        cout << nl;
    }
    return 0;
}
