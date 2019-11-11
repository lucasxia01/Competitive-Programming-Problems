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
#define FORd(i,a,b) for (int i = (b); i >= (a); i--)
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
    int n, q;
    cin >> n >> q;
    int R[n], C[n];
    int u[n], d[n], l[n], r[n];
    F0R(i, n) { cin >> R[i]; R[i] %= 2; }
    F0R(i, n) { cin >> C[i]; C[i] %= 2; }
    int cur = 0;
    F0R(i, n) {
        if (i == 0 || R[i] != R[i-1]) cur = i;
        u[i] = cur;
    }
    F0Rd(i, n) {
        if (i == n-1 || R[i] != R[i+1]) cur = i;
        d[i] = cur;
    }
    F0R(i, n) {
        if (i == 0 || C[i] != C[i-1]) cur = i;
        l[i] = cur;
    }
    F0Rd(i, n) {
        if (i == n-1 || C[i] != C[i+1]) cur = i;
        r[i] = cur;
    }
    int a, b, x, y;
    while (q--) {
        cin >> a >> b >> x >> y;
        a--; b--; x--; y--;
        if (u[a] == u[x] && d[a] == d[x] && l[b] == l[y] && r[b] == r[y]) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
