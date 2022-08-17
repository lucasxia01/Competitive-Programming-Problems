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
    cin.tie(0); cout.tie(0);
    int h[3][51];
    int n;
    ll cur = 0;
    bool yes = true;
    F0R(i, 3) {
        cin >> n;
        F0R(j, n) {
            cin >> h[i][j];
            if (j != 0 && h[i][j] > h[i][j-1]) yes = false;
            if (cur < h[i][j]) cur = h[i][j];
        }
        h[i][n] = -1;
    }
    ll m = cur;
    int ptr[3] = {};
    int a = 0;
    ll ans = 0;
    bool good = false;
    if (!yes) {
        cout << "No" << endl;
        return 0;
    }
    bool wrong = false;
    bool right = true;
    while (cur > 0) {
        //cout << cur << " " << a << endl;
        if (h[a][ptr[a]] == cur) {
            //cout << a << " " << h[a][ptr[a]] << endl;
            if (good) ans += 1LL<<(cur-1);
            cur--;
            ptr[a]++;
            wrong = false;
            right = !right;
        } else {
            if (wrong) {
                yes = false;
                break;
            }
            good = !good;
            right = !right;
            wrong = true;
            if (right) a = (a+1)%3;
            else a = (a+2)%3;
        }
        
    }
    if (!yes) cout << "No" << endl;
    else cout << (1LL<<(m)) - 1 - ans << endl;
    return 0;
}
