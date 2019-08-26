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
int n;
ll t[2 * MAX_N];

void build() {  // build the tree
    for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int l, int r, ll value) {
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) t[l++] += value;
        if (r&1) t[--r] += value;
        cout << l << " " << r << endl;;
    }
}
int query(int p) {
    int res = 0;
    for (p += n; p > 0; p >>= 1) res += t[p];
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    ll s[n], ans[n];
    t[n] = 0;
    F0R(i, n) {
        cin >> s[i];
        t[i+n+1] = t[n+i] + i+1;
    }
    build();
    F0R(i, 2*n) {
        cout << t[i] << " ";
    } cout << endl;
    modify(0, 5, 1);
    cout << query(4) << endl;
    F0R(i, 2*n) {
        cout << t[i] << " ";
    } cout << endl;
    F0Rd(i, n) {
        ll* pos = lower_bound(t+n, t+2*n, s[i]);
        int p = pos - (t+n);
        cout << s[i] << " " << p << " " << t[p+n] << " ";
        modify(p+1, n, (t+n)-pos-1);
        F0R(i, 2*n) {
            cout << t[i] << " ";
        } cout << endl;
        ans[i] = (pos-(t+n)+1);
    }

    F0R(i, n) {
        cout << ans[i] << " ";
    } cout << endl;
    return 0;
}
