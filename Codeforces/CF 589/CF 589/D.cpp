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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> e[n+1];
    int x, y;
    F0R(i, m) {
        cin >> x >> y;
        e[x].pb(y);
        e[y].pb(x);
    }
    int marked[n+1];
    F0R(i, n+1) marked[i] = 0;
    F0R(i, 3) {
        int edges[n+1];
        F0R(j, n+1) edges[j] = 0;
        int j = 1;
        for (; j <= n; j++) {
            if (marked[j] == 0) break;
        }
        if (j == n+1) {
            cout << -1 << endl;
            return 0;
        }
        int count = 0;
        trav(a, e[j]) {
            edges[a] = 1;
            count++;
        }
        marked[j] = i+1;
        j++;
        for(; j <= n; j++) {
            int count1 = 0;
            bool ok = true;
            trav(a, e[j]) {
                if (edges[a] == 0) {ok = false; break;}
                else count1++;
            }
            if (count1 != count) ok = false;
            if (ok) marked[j] = i+1;
        }
    }
    FOR(i, 1, n+1) {
        if (marked[i] == 0) {
            cout << -1 << endl;
            return 0;
        }
    }
    FOR(i, 1, n+1)
        cout << marked[i] << " ";
    cout << endl;
    return 0;
}
