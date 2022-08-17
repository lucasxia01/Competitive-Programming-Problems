#include <iostream>
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
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s;
    cin >> s;
    int slen = (int) s.length();
    int n;
    cin >> n;
    string a[n];
    F0R(i, n) cin >> a[i];
    bool hits[slen][n];
    F0R(i, n) {
        //cout << a[i] << endl;
        int len = (int)a[i].length();
        int freq[26] = {}, f[26] = {};
        F0R(j, len) {
            f[a[i][j]-'a']++;
        }
        F0R(j, slen) {
            freq[s[j]-'a']++;
            if (j-len >= 0) freq[s[j-len]-'a']--;
            bool ok = true;
            F0R(k, 26) {
                if (f[k] != freq[k]) {
                    ok = false;
                    break;
                }
            }
            if (j-len+1 < 0 || a[i][len-1] != s[j] || a[i][0] != s[j-len+1]) ok = false;
            if (ok) hits[j][i] = true;
            else hits[j][i] = false;
        }
    }
    int dp[slen+1];
    F0R(i, slen+1) dp[i] = 0;
    dp[0] = 1;
    FOR(i, 1, slen) {
        F0R(j, n) {
            //cout << i << " " << j <<" " <<hits[i-1][j] << endl;
            if (hits[i-1][j] && dp[i-a[j].length()]) {
                if (dp[i] < 2) dp[i]+=dp[i-a[j].length()];
                if (dp[i] > 2) dp[i] = 2;
            }
        }
    }
    if (dp[slen] == 0) {
        cout << "impossible" << endl;
    } else if (dp[slen] > 1) {
        cout << "ambiguous" << endl;
    } else {
        vector<int> out;
        int i = slen;
        while (i > 0) {
            F0R(j, n) {
                if (hits[i-1][j] && dp[i-a[j].length()]) {
                    i -= a[j].length();
                    out.pb(j);
                    break;
                }
            }
        }
        F0Rd(j, (int)out.size()) {
            cout << a[out[j]] << " ";
        } cout << endl;
    }
    return 0;
}
