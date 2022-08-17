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

const int MX = 1<<20;

string subtract(string a, string b) { // a > b
    int n = (int)a.length();
    int m = (int)b.length();
    string c = "";
    F0R(i, n-m) c += '0';
    b = c + b;
    int ans[n];
    F0R(i, n) {
        ans[i] = (int)(a[i]-b[i]);
    }
    F0Rd(i, n) {
        if (ans[i] < 0) {
            ans[i]+=10;
            ans[i-1]--;
        }
    }
    string ret = "";
    bool leading = true;
    F0R(i, n) {
        if (ans[i]) leading = false;
        if (!leading) ret += (char)(ans[i]+'0');
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        string s, b;
        cin >> s;
        vector<string> ans;
        int n;
        while((n = (int)s.length())) {
            b = s.substr(0, n/2);
            reverse(b.begin(), b.end());
            b = s.substr(0, (n+1)/2) + b;
            if (b > s) {
                int c = (n-1)/2;
                while (c >= 0 && s[c] == '0') {
                    c--;
                }
                if (c < 0 || (c == 0 && s[0] == '1')) {
                    b = "";
                    F0R(i, n-1) b += '9';
                } else {
                    b[c]--;
                    if (c != n-1-c) b[n-1-c]--;
                }
            }
            ans.pb(b);
            s = subtract(s, b);
        }
        cout << sz(ans) << endl;
        trav(a, ans) cout << a << endl;
    }
    return 0;
}
