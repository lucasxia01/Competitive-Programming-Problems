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

const char nl = '\n';
const ll INF = (1LL<<50) + 123;
const ll LLINF = (1LL<<50) + 777;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

const int MX = 1e6+5;
int n;
int fenw[MX];
int a[MX];
void upd(int p, int v) {
    while (p <= n) {
        // cout << p << " " << v << nl;
        fenw[p] ^= v;
        p += p&-p;
    }
}

int query(int p) {
    // cout << p << nl;
    int ans = 0;
    while (p > 0) {
        ans ^= fenw[p];
        p -= p&-p;
    }
    return ans;
}

struct Query {
    int r, l, i;
    bool operator<(const Query& o) const {
        return (r < o.r);
    }
};

int main() {
    cin >> n;
    F0R(i, n) scanf("%d", &a[i]);
    int q, l, r; cin >> q;
    vector<Query> qs;
    F0R(i, q) {
        scanf("%d %d", &l, &r);
        l--; r--;
        qs.pb({r, l, i});
    }
    int prefXOR[n+1]; prefXOR[0] = 0;
    F0R(i, n) prefXOR[i+1] = prefXOR[i]^a[i];
    sort(qs.begin(), qs.end());
    unordered_map<int, int> last;
    int ans[q];
    int j = 0;
    // the idea here is that the xor of all the even frequency is the xor of all the distinct values xor-ed with all the values (including duplicates) of the segment
    // we can count the distinct values xor with a fenwick tree offline by sorting by right query endpoint and updating the most recently seen position of each value
    // then we can just get each segment, assuming they have that right endpoint
    // for the whole segment's xor, we can do that easily with prefix xors
    F0R(i, n) {
        if (last.find(a[i]) != last.end()) upd(last[a[i]]+1, a[i]);
        last[a[i]] = i;
        upd(i+1, a[i]);
        while (j < q && qs[j].r == i) {
            ans[qs[j].i] = query(i+1)^query(qs[j].l)^prefXOR[i+1]^prefXOR[qs[j].l];
            j++;
        }
        if (j == q) break;
    }
    F0R(i, q) printf("%d\n", ans[i]);
    return 0;
}
