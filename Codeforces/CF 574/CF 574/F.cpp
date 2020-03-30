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

const int MX = 1e5+5;
int n;
int f[MX];
void upd(int p, int v) {
    while (p < MX) {
        f[p] += v;
        p += p&-p;
    }
}
int query(int p) {
    int ret = 0;
    while (p) {
        ret += f[p];
        p -= p&-p;
    }
    return ret;
}

struct Query {
    int l, r, idx;
    Query(int L, int R, int I) {
        l = L; r = R; idx = I;
    }
    bool operator< (Query const& other) const {
        return (r < other.r);
    }
};

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    return gcd(b%a, a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int k, q;
    cin >> n;
    set<pi> slopes[n]; // idea is that only distinct slopes affect the answer, you can see this if you imagine moving one polygon around based on the other polygon, if they have same slope, they just form 1 line together
    F0R(i, n) {
        cin >> k;
        pi a[k];
        F0R(j, k) cin >> a[j].f >> a[j].s;
        F0R(j, k) {
            int dx = a[j].f-a[(j+k-1)%k].f, dy = a[j].s-a[(j+k-1)%k].s;
            int g = gcd(abs(dx), abs(dy));
            slopes[i].insert(mp(dx/g, dy/g)); // size of vector doesn't matter
        }
    }
    cin >> q;
    vector<Query> queries; // offline approach with fenwick tree to count number of distinct in each query range
    int l, r;
    F0R(i, q) {
        cin >> l >> r;
        l--; r--; // 0-indexed
        queries.pb(Query(l, r, i));
    }
    sort(queries.begin(), queries.end()); // sort by right end
    int ql, qr;
    map<pi, int> curSlopes;
    int ans[q];
    map<pi, int> last;
    r = -1;
    F0R(i, q) {
        ql = queries[i].l; qr = queries[i].r;
        //cout << ql << " " << qr << endl;
        while (r < qr) { // for each r, we greedily update the most recent occurrence of each slope, such that it is maximal given the current r
            // we do this because we query based on l, we want [l, r) to contain an occurrence of each element
            // if the most recent occurence is not in the interval, then it must not be in the interval
            // we only want each element to appear once in the fenwick tree, so we use the most recent
            r++;
            trav(a, slopes[r]) {
                if (last[a]) upd(last[a], -1); // subtract last occurence by 1 because it is no longer the most recent occurrence
                last[a] = r+1;
                upd(last[a], 1);
            }
        }
        ans[queries[i].idx] = query(qr+1)-query(ql); // answer the query by counting the number of distinct elements from 1 to qr, minus the number from 1 to ql-1
    }
    F0R(i, q) cout << ans[i] << endl;
    return 0;
}
