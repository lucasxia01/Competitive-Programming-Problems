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
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s;
    cin >> s;
    int len = (int) s.length();
    bool pal[len][len];
    F0R(i, len) F0R(j, len) {
        if (i != j) pal[i][j] = 0; else pal[i][j] = 1;
    }
    FOR(l, 1, len) {
        F0R(i, len-l) {
            if (s[i] == s[i+l] && (pal[i+1][i+l-1] || l == 1))
                pal[i][i+l] = pal[i+1][i+l-1] + 1;
        }
    }
    int ans[len][len];
    F0R(i, len) F0R(j, len) {
        if (i != j) ans[i][j] = 0; else ans[i][j] = 1;
    }
    FOR(l, 1, len) {
        F0R(i, len-l) {
            if (pal[i][i+l]) {
                ans[i][i+l] = ans[i][i+(l-1)/2]+1;
                //cout << i << " " << i+l << " " << ans[i][i+l] << endl;
            }
        }
    }
    int freq[len];
    F0R(i, len) freq[i] = 0;
    F0R(i, len) F0R(j, len) if (ans[i][j]) freq[ans[i][j]-1]++;
    int a[len]; a[len-1] = freq[len-1];
//    F0R(i, len) cout << freq[i] << " ";
//    cout << endl;
    F0Rd(i, len-1) a[i] = a[i+1] + freq[i];
    F0R(i, len) cout << a[i] << " ";
    cout << endl;
    return 0;
}
