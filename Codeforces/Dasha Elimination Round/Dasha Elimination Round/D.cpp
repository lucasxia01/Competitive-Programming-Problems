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

int a[100011][2];
vi e[100011];
int marked[100011];
int count = 0;

void dfs(int v) {
    marked[v] = 1;
    //cout << v << endl;
    trav(au, e[v]) {
        if (a[au][0] == v) {
            if (!marked[a[au][1]]) dfs(a[au][1]);
        } else {
            if (!marked[a[au][0]]) dfs(a[au][0]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    
    F0R(i, k) {
        cin >> a[i][0] >> a[i][1];
        e[a[i][0]].pb(i);
        e[a[i][1]].pb(i);
    }
    int count = 0;
    FOR(i, 1, n+1) {
        if (!marked[i]) {
            count++;
            dfs(i);
            //cout << endl;
        }
    }
    int num = 0;
    FOR(i, 1, n+1) if (marked[i]) num++;
    cout << k - (num-count) << endl;
    return 0;
}
