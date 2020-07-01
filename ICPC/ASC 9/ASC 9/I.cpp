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
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 4005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("traces.in", "r", stdin);
//    freopen("traces.out", "w", stdout);
    int n, m; cin >> n >> m;
    int ind[n][n]; F0R(i, n) F0R(j, n) ind[i][j] = 0;
    char a, b;
    F0R(i, m) {
        cin >> a >> b;
        ind[a-'a'][b-'a'] = ind[b-'a'][a-'a'] = 1;
    }
    string s, t; cin >> s >> t;
    if (s.length() != t.length()) {
        cout << "NO" << nl;
        return 0;
    }
    int len = (int)s.length();
    int freq[10] = {};
    F0R(i, len) {
        freq[s[i]-'a']++;
        freq[t[i]-'a']--;
    }
    F0R(i, 10) {
        if (freq[i]) {
            cout << "NO" << nl;
            return 0;
        }
    }
    F0R(i, n) F0R(j, i) {
        if (ind[i][j]) continue;
        string x = "", y = "";
        F0R(k, len) {
            if (s[k] == i+'a' || s[k] == j+'a') x += s[k];
            if (t[k] == i+'a' || t[k] == j+'a') y += t[k];
        }
        if (x != y) {
            cout << "NO" << nl;
            return 0;
        }
    }
    cout << "YES" << nl;
    return 0;
}
