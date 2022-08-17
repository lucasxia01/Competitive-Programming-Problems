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
 
const int MX = (1<<20) + 5;
 
vi subtree[MX];
int heap[MX], ans[MX];
bool used[MX];
int n, m;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int h, g;
        cin >> h >> g;
        n = (1<<h)-1;
        m = (1<<g)-1;
        memset(heap, 0, 4*n+4);
        memset(ans, 0, 4*n+4);
        F0R(i, n) cin >> heap[i+1];
        FOR(i, 1, n) subtree[i].clear();
        FORd(i, 1, n) { // just store the whole subheap at every position (nlogn space)
            subtree[i].pb(heap[i]);
            if (2*i <= n) {
                trav(a, subtree[2*i]) subtree[i].pb(a);
                trav(a, subtree[2*i+1]) subtree[i].pb(a);
            }
            sort(subtree[i].begin(), subtree[i].end());
        }
        // build heap layer by layer
        ll total = 0;
        FORd(i, 1, m) {
            trav(a, subtree[i]) {
                if (!used[a] && a > ans[2*i] && a > ans[2*i+1]) { // find the smallest thing bigger than its children
                    total += 1LL*a;
                    used[a] = 1;
                    ans[i] = a;
                    break;
                }
            }
        }
        cout << total << endl;
        FORd(i, 1, n) {
            if (!used[heap[i]]) cout << i << " ";
            else used[heap[i]] = 0;
        }
        cout << endl;
    }
    return 0;
}
