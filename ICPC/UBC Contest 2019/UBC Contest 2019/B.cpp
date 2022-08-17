#include <iostream>
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

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()
int a[101][3];

int check(int A, int B) { // if a can beat b
    int x, y;
    if (a[A][1] <= a[B][2]) x = INF;
    else x = (a[B][0]+(a[A][1]-a[B][2])-1)/(a[A][1]-a[B][2]); // ceiling
    if (a[B][1] <= a[A][2]) y = INF;
    else y = (a[A][0]+(a[B][1]-a[A][2])-1)/(a[B][1]-a[A][2]); // ceiling
    if (x<y) return 1;
    else if (x>y) return -1;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    
    string name[n];
    F0R(i, n) {
        cin >> name[i];
        F0R(j, 3) cin >> a[i][j];
    }
    vector<pair<pair<int, int>, int>> ans;
    //cout << check(1, 2) << endl;
    F0R(i, n) {
        FOR(j, i+1, n-1) {
            FOR(k, j+1, n-1) {
                int temp = check(i, j) + check(j, k) + check(k, i);
                if (temp == 3 || temp == -3) ans.pb(mp(mp(i, j), k));
            }
        }
    }
    cout << ans.size() << endl;
    trav(a, ans) {
        cout << name[a.f.f] << " " << name[a.f.s] << " " << name[a.s] << endl;
    }
    return 0;
}
