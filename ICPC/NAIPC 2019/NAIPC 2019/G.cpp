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
int fenw[4 * MAX_N];
void mod(int i, int v) {
    while (i < 4 * MAX_N) {
        fenw[i] += v;
        i += i&-i;
    }
}
int query(int i) {
    int sum = 0;
    while (i > 0) {
        sum += fenw[i];
        i -= i&-i;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int a[n][4];
    set<int> s;
    F0R(i, n) F0R(j, 4) {
        cin >> a[i][j];
        s.insert(a[i][j]);
    }
    // coord compression
    unordered_map<int, int> m;
    int count = 1;
    trav(a, s) m[a] = count++;
    F0R(i, n) F0R(j, 4) a[i][j] = m[a[i][j]];
    // x coord, start or end of rect, lower y coord, upper y coord
    vector<pair<pair<int, int>, pair<int, int>>> vlines;
    F0R(i, n) F0R(j, 2) {
        vlines.pb(mp(mp(a[i][2*j], 1-2*j), mp(a[i][1], a[i][3])));
    }
    sort(vlines.begin(), vlines.end());
    // sweepline
    trav(a, vlines) {
        //cout << a.f.f << " " << a.f.s << " " << a.s.f << " " << a.s.s << endl;
        if (query(a.s.f) != query(a.s.s)) {
            cout << 1 << endl;
            return 0;
        }
        mod(a.s.f, a.f.s);
        mod(a.s.s+1, a.f.s);
    }
    cout << 0 << endl;
    return 0;
}
