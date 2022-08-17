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

const int MAX_N = 200011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int maxSeg[2*MAX_N];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    int per[n], a[m], prev[n+1], prevPos[n+1];
    F0R(i, n) cin >> per[i];
    F0R(i, n+1) prevPos[i] = -1;
    F0R(i, n) prev[per[i]] = (i+n-1)%n;
    F0R(i, m) cin >> a[i];
    int pow = 1, LOGN = 0;
    while (pow <= n-1) {
        pow*=2;
        LOGN++;
    }
    int nextLift[m][LOGN];
    F0R(i, m) {
        nextLift[i][0] = prevPos[per[prev[a[i]]]];
        prevPos[a[i]] = i;
    }
    for (int exp = 1; exp < LOGN; exp++) {
        F0R(i, m) {
            if (nextLift[i][exp-1] == -1) nextLift[i][exp] = -1;
            else nextLift[i][exp] = nextLift[nextLift[i][exp-1]][exp-1];
        }
    }
    // search for n-1 previous
    int ends[m];
    F0R(i, m) {
        int cur = i, pos = 0;
        F0Rd(exp, LOGN) {
            if (pos+(1<<exp)<=n-1) {
                cur = nextLift[cur][exp];
                pos += (1<<exp);
                if (cur == -1) break;
            }
        }
        ends[i] = cur;
    }

    for (int i = m; i < 2*m; i++) {
        maxSeg[i] = ends[i-m];
    }
    F0Rd(i, m) {
        maxSeg[i] = max(maxSeg[2*i], maxSeg[2*i+1]);
    }
    string ans = "";
    int l, r, l1;
    F0R(i, q) {
        cin >> l >> r;
        l1 = l-1;
        l+=m-1; r+=m;
        int maxEnd = -1;
        for (; l < r; l>>=1, r>>=1) {
            if (l&1) {
                maxEnd = max(maxEnd, maxSeg[l]);
                l++;
            }
            if (r&1) {
                r--;
                maxEnd = max(maxEnd, maxSeg[r]);
            }
        }
        if (maxEnd >= l1) ans += '1';
        else ans += '0';
    }
    cout << ans << endl;
    
    return 0;
}
