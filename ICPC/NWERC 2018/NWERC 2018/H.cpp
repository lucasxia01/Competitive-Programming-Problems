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
    int n, c, b;
    cin >> n >> c >> b;
    int a[b+1];
    F0R(i, b) cin >> a[i+1];
    F0R(i, b+1) a[i]--;
    int diff = a[0];
    int ch = 0;
    string s = "";
    F0R(i, n) s += '0';
    if (c % 2) {
        s[0] = '1';
        a[0] = 1;
    } else a[0] = 0;
    
    int idx;
    F0R(i, b) {
        diff = a[i+1]-a[i];
        ch = min(2*(diff/2), 2*(c/2));
        //cout << a[i+1] << " " << a[i] << " " << ch << endl;
        idx = a[i]+1;
        F0R(i, ch/2) {
            s[idx] = '1';
            idx+=2;
        }
        c -= ch;
    }
    cout << s << endl;
    return 0;
}
