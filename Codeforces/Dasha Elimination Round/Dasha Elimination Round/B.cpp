#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>

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
#define FOR(i,a,b) for (int i = a; i < b; i++)
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
    cin.tie(0);
    int n, a, b;
    cin >> n;
    string s, s1;
    cin >> s;
    int p[5][5];
    int q[n][2];
    F0R(i, n) {
        cin >> a >> b;
        p[a-1][b-1]++;
        q[i][0] = a; q[i][1] = b;
    }
    int ans = 0;
    F0R(i, 127) {
        //if (s == "111111") cout << s << " " << i << endl;
        int count = 0;
        F0R(j, n) {
            if (s[j] == '1') count++;
        }
        ans = max(ans, count);
        s1 = "";
        F0R(j, n) {
            if (i % q[j][0] == q[j][1] % q[j][0] && i >= q[j][1]) s1 += ('1'-s[j]+'0');
            else s1 += s[j];
        }
        s = s1;
    }
    cout << ans << endl;
    return 0;
}
