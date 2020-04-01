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

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}
const int MX = 1e5+5;
vi edges[MX];
int n;
int t;

int check(int k, int v = 1, int p = 0) {
    multiset<int> roads;
    int ti = t++;
    trav(u, edges[v]) {
        if (u != p) {
            int ret = check(k, u, v);
            if (ret) roads.insert(ret);
            else return 0;
        }
    }
    int noMatch = 0;
    int largestMatchWithK = 0;
    for (auto i = roads.begin(); i != roads.end();) {
        if (*i >= k) {
            noMatch = *roads.rbegin(); // set to largest one, but it doesn't really matter
            break;
        }
        auto it = lower_bound(++roads.begin(), roads.end(), k-*i);
        if (it == roads.end() && noMatch == 0) noMatch = *i;
        else if (it == roads.end()) return 0;
        else {
            if (*it >= k) largestMatchWithK = *i;
            roads.erase(it);
        }
        i = roads.erase(i);
    }
    if (v == 1) if (noMatch && noMatch < k) return 0; // if its the root, and something is unmatched that is small, then failed mission
    if (noMatch == 0) noMatch = largestMatchWithK;
    return noMatch+1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
    int u, v;
    cin >> n;
    F0R(i, n-1) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    int l = 1, h = n;
    while (l < h) {
        int mid = (l+h)/2;
        if (check(mid)) l = mid+1;
        else h = mid;
    }
    cout << (l+h)/2-1 << endl;
    return 0;
}
