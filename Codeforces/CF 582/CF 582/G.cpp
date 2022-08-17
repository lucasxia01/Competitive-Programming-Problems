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

int par[2*MAX_N];
int tree_size[2*MAX_N];
ll c = 0;

int find(int idx) {
    return (par[idx] == idx) ? idx : find(par[idx]);
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    //cout << "tree_sizes: " << tree_size[a] << " " << tree_size[b] << endl;
    if (tree_size[a] < tree_size[b]) {
        par[a] = b;
        c -= 1LL*tree_size[b]*(tree_size[b]-1)/2 + 1LL*tree_size[a]*(tree_size[a]-1)/2;
        tree_size[b] += tree_size[a];
        c += 1LL*tree_size[b]*(tree_size[b]-1)/2;
        tree_size[a] = 0;
    } else {
        par[b] = a;
        c -= 1LL*tree_size[b]*(tree_size[b]-1)/2 + 1LL*tree_size[a]*(tree_size[a]-1)/2;
        tree_size[a] += tree_size[b];
        c += 1LL*tree_size[a]*(tree_size[a]-1)/2;
        tree_size[b] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, u, v, w;
    cin >> n >> m;
    vector<pair<int, pi>> e;
    F0R(i, n-1) {
        cin >> u >> v >> w;
        e.pb(mp(w, mp(u, v)));
        par[i+1] = i+1;
        tree_size[i+1] = 1;
    }
    par[n] = n;
    tree_size[n] = 1;
    sort(e.begin(), e.end());
    ll ans[(int)2e5+10] = {};
    int idx = 0;
    FOR(i, 1, (int)2e5) {
        while (idx < n-1 && e[idx].f <= i) {
            //cout << e[idx].s.f << " " << e[idx].s.s << endl;
            merge(e[idx].s.f, e[idx].s.s);
            idx++;
        }
        ans[i] = c;
    }
    while (m--) {
        cin >> w;
        cout << ans[w] << " ";
    } cout << endl;
    return 0;
}
