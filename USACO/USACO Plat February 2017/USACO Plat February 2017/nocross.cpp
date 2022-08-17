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
const int INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;

int n;
int r[MX];
vi pos[MX];
int t[2*MX];

void upd(int p, int v) {
    for (p+=n; p >= 1 && t[p] < v; p >>= 1) t[p] = v;
}

int query(int p) {
    int ans = 0;
    for (int l = n, r = p+n; l < r; l>>=1, r>>=1) {
        if (l&1) ckmax(ans, t[l++]);
        if (r&1) ckmax(ans, t[--r]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    cin >> n;
    F0R(i, n) cin >> r[i], r[i]--;
    int x;
    F0R(i, n) {
        cin >> x; x--;
        for (int j = max(0, x-4); j <= min(n, x+4); j++) pos[j].pb(i);
    }
    F0R(i, n) {
        F0Rd(j, sz(pos[r[i]])) {
            int m = query(pos[r[i]][j]);
            //cout << pos[r[i]][j] << " " << m << nl;
            upd(pos[r[i]][j], m+1);
        } //cout << nl;
    }
    cout << query(n) << nl;
    
    return 0;
}
