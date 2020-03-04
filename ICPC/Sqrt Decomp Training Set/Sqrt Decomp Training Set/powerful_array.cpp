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

struct bucketPair {
    int l, r, bSize, index;
    bool operator< (bucketPair const& other) const {
        if (l/bSize == other.l/bSize) return r < other.r;
        return l/bSize < other.l/bSize;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q, Q;
    cin >> n >> q;
    Q = q;
    int A[n];
    ll ans[q];
    F0R(i, n) cin >> A[i];
    int SQRTN = sqrt(n) + 1000;
    vector<bucketPair> v;
    while (q--) {
        bucketPair range;
        cin >> range.l >> range.r;
        range.l--; range.r--;
        range.bSize = SQRTN;
        range.index = Q-q-1;
        v.pb(range);
    }
    sort(v.begin(), v.end());
    int l = 0, r = 0;
    ll total = 0;
    ll freq[(int) 1e6+5] = {};
    int idx;
    ll f;
    trav(a, v) {
        while (l < a.l) {
            idx = A[l];
            freq[idx]--;
            f = freq[idx];
            total += (f*f - (f+1)*(f+1))*idx;
            l++;
        }
        while (l > a.l) {
            l--;
            idx = A[l];
            freq[idx]++;
            f = freq[idx];
            total += (f*f - (f-1)*(f-1))*idx;
        }
        while (r-1 < a.r) {
            idx = A[r];
            freq[idx]++;
            f = freq[idx];
            total += (f*f - (f-1)*(f-1))*idx;
            r++;
        }
        while (r-1 > a.r) {
            r--;
            idx = A[r];
            freq[idx]--;
            f = freq[A[r]];
            total += (f*f - (f+1)*(f+1))*idx;
        }
        ans[a.index] = total;
    }
    F0R(i, Q) cout << ans[i] << endl;
    return 0;
}
