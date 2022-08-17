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
ll round10000(ll a) {
    if (a % 10000 >= 5000) a += 10000;
    return a-(a%10000);
}
bool checkHigher(ll pre, ll post, ll t) {
    return (round10000(pre * (t + 10000)) >= post*10000);
}

bool checkLower(ll pre, ll post, ll t) {
    return (round10000(pre * (t + 10000)) <= post*10000);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    while (n--) {
        string A, B, T;
        cin >> A >> B >> T;
        ll a = 0, b = 0, t = 0;
        ll pow = 1;
        F0Rd(i, (int)A.length()) {
            if (A[i] == '.') continue;
            a += pow * (A[i]-'0');
            pow *= 10;
        }
        pow = 1;
        F0Rd(i, (int)B.length()) {
            if (B[i] == '.') continue;
            b += pow * (B[i]-'0');
            pow *= 10;
        }
        pow = 1;
        F0Rd(i, (int)T.length()) {
            if (T[i] == '.') continue;
            t += pow * (T[i]-'0');
            pow *= 10;
        }
        // cout << a << " " << b << " " << t << endl;
        assert(a <= b);
        ll aa = ((10000*a)-((10000*a)%(t+10000)))/(t+10000);
        ll bb = ((10000*b)-((10000*b)%(t+10000)))/(t+10000)+1; // floored both aa and bb
        // cout << aa << " " << bb << endl;
        assert(aa <= bb);
        ll i = aa-1;
        ll j = bb+1;
        while (!checkHigher(i, a, t)) i++;
        assert(checkHigher(i, a, t) && !checkHigher(i-1, a, t));
        while (!checkLower(j, b, t)) j--;
        assert(checkLower(j, b, t) && !checkLower(j+1, b, t));
        // cout << i << " " << j << endl;
        assert(j-i >= -1);
        ll ans = (ll) (b-a+1);
        if (i <= j) ans -= (j-i+1);
        cout << ans << '\n';
        assert(ans >= 0);
    }
}
