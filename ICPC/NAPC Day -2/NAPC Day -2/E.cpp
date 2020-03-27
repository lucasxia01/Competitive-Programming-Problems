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
const int MX = 1<<20;
const ll INF = (1<<29) + 123;
const ll MOD = 998244353;
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
    int n;
    cin >> n;
    pair<int, pi> m[2*n];
    set<pi> l, d;
    F0R(i, 2*n) {
        cin >> m[i].s.f >> m[i].s.s;
        m[i].f = m[i].s.f-m[i].s.s;
    }
    sort(m, m+2*n);
    ll t = 0;
    F0R(i, 2*n) {
        if (i < n) {
            l.insert(m[i].s);
            t += m[i].s.f;
        } else {
            d.insert(mp(m[i].s.s, m[i].s.f));
            t += m[i].s.s;
        }
    }
    set<pi> el, ed; // el contains lunch price of dinners that were excluded
    ll ans[n];
    F0R(i, n) ans[i] = 0;
    ans[n-1] = t;
    F0Rd(i, n-1) {
        ans[i] = ans[i+1];
        do {
            while (l.size() > i+1) {
                if (l.rbegin()->s != INF) { // in this case, put it in other list
                    d.insert(mp(l.rbegin()->s, INF));
                    ans[i] += l.rbegin()->s;
                }
                ans[i] -= l.rbegin()->f;
                l.erase(--l.end());
            }
            while (d.size() > i+1) {
                if (d.rbegin()->s != INF) { // in this case, put it in other list
                    l.insert(mp(d.rbegin()->s, INF));
                    ans[i] += d.rbegin()->s;
                }
                ans[i] -= d.rbegin()->f;
                d.erase(--d.end());
            }
        } while (l.size() != i+1 || d.size() != i+1);
    }
    F0R(i, n) cout << ans[i] << endl;
    return 0;
}
