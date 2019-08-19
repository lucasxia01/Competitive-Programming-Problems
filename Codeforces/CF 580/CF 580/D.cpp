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
#include <unordered_map>

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
    int n;
    cin >> n;
    ll a[n];
    static int bits[100011][64];
    vi nodes;
    F0R(i, n) {
        cin >> a[i];
        int count = 0;
        ll x = a[i];
        F0R(j, 64) {
            if (x%2) bits[i][j] = 1;
            else bits[i][j] = 0;
            x /= 2;
            if (bits[i][j]) count++;
        }
        if (count >= 2) {
            cout << i << endl;
            nodes.pb(i);
        }
    }
    F0R(i, 64) {
        int count = 0;
        int x[2];
        F0R(j, n) {
            if (bits[j][i]) {
                if (count < 2) x[count] = j;
                count++;
            }
        }
        if (count >= 3) {
            cout << 3 << endl;
            return 0;
        }
    }
    int ans = MAX_N;
    int n_nodes = (int) nodes.size();
    int mat[2*n_nodes][2*n_nodes];
    F0R(i, 2*n_nodes)
        F0R(j, 2*n_nodes)
            mat[i][j] = INF;
    F0R(i, n_nodes) {
        F0R(j, n_nodes) {
            cout << a[nodes[i]] << " " << a[nodes[j]] << endl;
            if (i != j && (a[nodes[i]]&a[nodes[j]])) mat[2*i][2*j+1] = 1;
            //if (mat[i][j] != INF) cout << i << " " << j << endl;
        }
    }
    F0R(i, n_nodes) {
        mat[2*i+1][2*i] = 1;
    }
    F0R(k, n_nodes) {
        F0R(i, n_nodes) {
            F0R(j, n_nodes) {
                if (i == j && mat[i][k] + mat[k][j] == 2) continue;
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }
    F0R(k, n_nodes) {
        ans = min(ans, mat[k][k]);
    }
    if (ans == MAX_N) cout << -1 << endl;
    else cout << ans/2 << endl;
    
    
    return 0;
}
