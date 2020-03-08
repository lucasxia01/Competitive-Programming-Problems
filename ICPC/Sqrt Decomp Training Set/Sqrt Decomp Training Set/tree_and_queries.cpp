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

int SQRTN;

struct Query {
    int l, r, k, index;
    
    bool operator< (Query const& other) const {
        if (l/SQRTN == other.l/SQRTN) return (r < other.r);
        return (l/SQRTN < other.l/SQRTN);
    }
};

const int MX = 100005;
vi edges[MX];
int startT[MX], endT[MX], c[MX], color[MX];
int clk = 0;

void dfs(int r, int p) {
    c[clk] = color[r-1];
    startT[r] = clk++;
    trav(v, edges[r])
        if (v != p) dfs(v, r);
    endT[r] = clk;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, a, b, u, k;
    cin >> n >> m;
    SQRTN = sqrt(n);
    ll ans[m];
    F0R(i, n) cin >> color[i];
    F0R(i, n-1) {
        cin >> a >> b;
        edges[a].pb(b);
        edges[b].pb(a);
    }
    dfs(1, 0);
    vector<Query> v;
    F0R(q, m) {
        Query qry;
        cin >> u >> k;
        qry.l = startT[u];
        qry.r = endT[u];
        qry.index = q;
        qry.k = k;
        v.pb(qry);
    }
    sort(v.begin(), v.end());
    int l = 0, r = 0;
    ll freq[MX] = {}; // counts frequencies of each color
    ll freqfreq[2*MX] = {}; // counts number of frequencies above i, padded by MX
    trav(a, v) {
        //cout << a.l << " " << a.r << " " << a.k << endl;
        while (l < a.l) {
            freqfreq[freq[c[l]]+MX]--;
            freq[c[l]]--;
            l++;
        }
        while (l > a.l) {
            l--;
            freq[c[l]]++;
            freqfreq[freq[c[l]]+MX]++;
        }
        while (r < a.r) {
            freq[c[r]]++;
            freqfreq[freq[c[r]]+MX]++;
            r++;
        }
        while (r > a.r) {
            r--;
            freqfreq[freq[c[r]]+MX]--;
            freq[c[r]]--;
        }
        ans[a.index] = freqfreq[a.k+MX];
    }
    F0R(i, m) cout << ans[i] << endl;
    return 0;
}
