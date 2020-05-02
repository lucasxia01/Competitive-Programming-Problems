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

const int MX = 3e5+5;

/* Segment Tree
 * Range Max Query and Increment Update
 * Written 4/30/20 generally from scratch
 */
template <typename T>
struct SegTree {
    int t[2*MX];
    int d[MX];
    int N, h;
    SegTree(int n) {
        h = 8*sizeof(int) - __builtin_clz(n);
        N = n;
        F0R(i, 2*N) t[i] = 0;
        F0R(i, N) d[i] = 0;
    }
    
    void push(int p) {
        for (int i = h; i > 0; i--) {
            int q = p>>i;
            if (d[q]) {
                apply(q<<1, d[q]);
                apply(q<<1|1, d[q]);
                d[q] = 0;
            }
        }
    }
    int query(int l, int r) { // querying [l, r)
        // cout << "query " << l << " " << r << nl;
        push(l+N);
        push(r+N-1);
        T ans = -INF;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) ckmax(ans, t[l++]);
            if (r&1) ckmax(ans, t[--r]);
        }
        return ans;
    }
    void apply(int p, int v) {
        t[p] += v;
        if (p < N) d[p] += v;
    }
    void pull(int p) {
        for (p >>= 1; p > 0; p >>= 1)
            t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
    }
    void upd(int l, int r, int v) { // incrementing by v on [l, r)
        // cout << "upd " << l << " " << r<< " " << v << nl;
        int l0 = l+N, r0 = r+N;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) apply(l++, v);
            if (r&1) apply(--r, v);
        }
        pull(l0);
        pull(r0-1);
    }
    void printTree() {
        FOR(i, 1, 2*N-1) cout << t[i] << " ";
        cout << nl;
    }
    void printDelay() {
        FOR(i, 1, N-1) cout << d[i] << " ";
        cout << nl;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int p[n], pos[n+1], q;
    F0R(i, n) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    int a[n+1];
    F0R(i, n+1) a[i] = 1;
    int curAns = n;
    SegTree<int> st(n);
    st.upd(0, pos[curAns]+1, 1);
    F0R(i, n) {
        cout << curAns << " ";
        cin >> q;
        st.upd(0, q, -1);
        while (curAns > 1 && st.query(0, n) < 1) {
            curAns--;
            st.upd(0, pos[curAns]+1, 1);
        }
    }
    cout << nl;
    return 0;
}
