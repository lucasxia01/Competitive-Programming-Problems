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
const int MX = 1e5+5;
const int INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    int a[n];
    F0R(i, n) cin >> a[i];
    pair<char, int> qrs[q];
    F0R(i, q) cin >> qrs[i].f >> qrs[i].s; // store the queries
    int marked = MX-1; // current lower bound marker of fixed range
    int ans[2*MX]; // stores pos or neg of all values from 0 to 2e5, padded
    F0R(i, 2*MX) { // initializing neg to 1 and pos to 0
        if (i < MX) ans[i] = 1;
        else ans[i] = 0;
    }
    bool c = 0; // counter var to store if the remaining is negated
    F0Rd(i, q) {
        int cur = abs(qrs[i].s);
        bool gt = (qrs[i].f == '>'); // if its greater than
        bool pos = (qrs[i].s >= 0); // if its positive
        if ((gt^pos) == 0) cur++; // if its > 5 for example, doesn't affect 5, affects (5, MX) => [6, MX)
        FOR(j, cur, marked-1) { // from current value to marker, make everything fixed
            if (gt) ans[MX+j] = ans[MX-j] = !c; // invert if greater
            else ans[MX+j] = ans[MX-j] = c;
        }
        if (gt^pos) c = !c; // if it affects the smaller stuff, invert
        ckmin(marked, cur); // update min fixed range
    }
    F0R(i, marked) {
        ans[MX+i] ^= c;
        ans[MX-i] ^= c;
    }
    F0R(i, n) cout << (1-2*ans[a[i]+MX])*abs(a[i]) << " ";
    cout << endl;
    return 0;
}
