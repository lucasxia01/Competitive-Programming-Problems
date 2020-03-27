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

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

const int MX = 2e5+5;
int p[MX], c[MX], marked[MX], m[MX];;
vi cur;
int n, ans = MX;

bool dfs2(int spos, int pos, int jump, int color) {
    if (c[cur[pos]] != color) return false;
    if ((pos+jump)%(cur.size()) == spos) return true;
    m[pos] = 1;
    return dfs2(spos, (pos+jump)%(cur.size()), jump, color);
}

void solve() {
    int sz = (int)cur.size();
    for (int i = 1; i <= sqrt(sz); i++) { // if something doesn't divide the length, then it must go through all parts and it can't be better than 1
        if (sz % i == 0) { // if it divides, check both divisors
            F0R(j, sz) m[j] = 0;
            F0R(j, sz) {
                if (m[j]) continue;
                if (dfs2(j, j, i, c[cur[j]])) { // check if the cycle is same color
                    ckmin(ans, i);
                    break;
                }
            }
            F0R(j, sz) m[j] = 0;
            F0R(j, sz) {
                if (m[j]) continue;
                if (dfs2(j, j, sz/i, c[cur[j]])) ckmin(ans, sz/i);
            }
        }
    }
}

void dfs(int i) {
    if (marked[i]) return;
    marked[i] = 1;
    cur.pb(i);
    dfs(p[i]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        ans = MX;
        cin >> n;
        F0R(i, n) {
            cin >> p[i];
            p[i]--;
        }
        F0R(i, n) marked[i] = 0;
        F0R(i, n) cin >> c[i];
        F0R(i, n) {
            if (marked[i]) continue;
            dfs(i); // find the "connected component" for each node
//            F0R(j, cur.size()) cout << cur[j] << " ";
//            cout << endl;
            solve(); // this will solve for that connected cycle thing
            cur.clear();
        }
        cout << ans << endl;
    }
    return 0;
}
