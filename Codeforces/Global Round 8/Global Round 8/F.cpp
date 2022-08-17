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

const char nl = '\n';
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

const int MX = 1000;

int a[MX];
int n;
int p;
void op(vl& l) {
    cout << sz(l) << " ";
    assert(sz(l) == p);
    trav(v, l) {
        a[v] = 1;
        cout << v+1 << " ";
    }
    cout << nl;
    fflush(stdout);
    cout.flush();
    l.clear();
    int x; cin >> x;
    FOR(i, x-1, x+p-2) a[i%n] = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    if (n <= 3) {
        cout << 0 << nl;
        return 0;
    }
    p = sqrtl((ld)n);
    while (1) {
        vl l;
        F0R(cur, p) {
            if (cur == p-1) {
                cout << 0 << nl;
                return 0;
            }
            F0R(i, n/p) {
                if (a[i*p+cur] == 0) {
                    l.pb(i*p+cur);
                    if (sz(l) == p) break;
                }
            }
            if (sz(l) == p) break;
            if (cur >= p-n%p && a[n/p*p+cur-(p-n%p)] == 0) l.pb(n/p*p+cur-(p-n%p));
            if (sz(l) == p) break;
        }
        assert(sz(l) == p);
        op(l);
    }
    return 0;
}
