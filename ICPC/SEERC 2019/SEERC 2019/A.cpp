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
#include <random>
#include <chrono>
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
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int n;
struct Node {
    int res[2][2] = {{INF, INF}, {INF, INF}};
    Node operator+(const Node& o) const {
        Node ret;
        F0R(i, 2) F0R(j, 2) F0R(ii, 2) F0R(jj, 2)
            ckmin(ret.res[i][j], res[i][ii] + (ii != jj) + o.res[jj][j]);
        return ret;
    }
};

template <class T>
struct SegTree {
    int SZ;
    vector<Node> t;
    SegTree(int n) {
        SZ = n;
        Node temp;
        F0R(i, 2*SZ) t.pb(temp);
    }
    void pull(int p) {
        while (p > 1) p>>=1, t[p] = t[p<<1]+t[p<<1|1];
    }
    void set(int p, T v) {
        p+=SZ;
        Node newP; newP.res[v][v] = 0, newP.res[!v][!v] = 1;
        t[p] = newP;
        pull(p);
    }
    Node query(int l, int r) {
        Node ans;
        F0R(i, 2)  ans.res[i][i] = 0;
        vi rSegs;
        for (l+=SZ, r+=SZ; l<r; l>>=1, r>>=1) {
            if (l&1) ans = ans + t[l++];
            if (r&1) rSegs.pb(--r);
        }
        F0Rd(i, sz(rSegs)) ans = ans + t[rSegs[i]]; // this is for correct order of merge
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int m; cin >> n >> m;
    vi v[m+1]; // positions of values of type i
    int a[n];
    F0R(i, n) {
        cin >> a[i];
        v[a[i]].pb(i);
    }
    SegTree<int> st(n);
    F0R(i, n) st.set(i, 1);
    FOR(i, 1, m) {
        trav(p, v[i-1]) st.set(p, 0);
        int SZ = sz(v[i]);
        int ans = n-SZ;
        F0R(j, SZ) {
            Node ret;
            int l = v[i][j], r = v[i][(j+1)%SZ];
            if (l < r) ret = st.query(l+1, r);
            else ret = st.query(l+1, n)+st.query(0, r);
            int add = INF;
            F0R(ii, 2) F0R(jj, 2) ckmin(add, ret.res[ii][jj]);
            ans += add;
        }
        cout << (!SZ ? -1 : ans) << " ";
    }
    cout << nl;
    return 0;
}
