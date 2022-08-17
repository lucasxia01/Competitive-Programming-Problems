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

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
ll MOD; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

const int MX = 1e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int f[MX][2]; // f, the function, and frequency of values
    set<int> invf[MX][2]; // inverse function
    F0R(j, 2) F0R(i, n) cin >> f[i][j];
    F0R(i, n) F0R(j, 2) invf[f[i][j]][j].insert(i);
    set<int> single[2], mult[2]; // single is set of domain values whose values only appear once in the remaining range, and mult is appear multiple times
    F0R(i, MX) F0R(j, 2)
        if (sz(invf[i][j]) == 1) trav(a, invf[i][j]) single[j].insert(a);
        else if (sz(invf[i][j]) > 1) trav(a, invf[i][j]) mult[j].insert(a);
    int dom[n]; F0R(i, n) dom[i] = 1;
    int q; cin >> q;
    string s;
    F0R(i, q) {
        cin >> s;
        int j = i%2, k = j^1;
        cerr << i << " " << s << nl;
        if (s[0] == 'Y') {
            // everything more than 1 is killed from domain
            // maybe also update the other dude's stuff
            bool ok[MX] = {};
            trav(a, mult[j]) {
                if (!ok[f[a][j]] && sz(invf[f[a][j]][j]) <= 1) continue;
                ok[f[a][j]] = 1;
                cerr << a << " ";
                if (dom[a] == 1) {
                    invf[f[a][j]][j].erase(invf[f[a][j]][j].find(a));
                    invf[f[a][k]][k].erase(invf[f[a][k]][k].find(a));
                    if (sz(invf[f[a][j]][j]) == 1) single[j].insert(*invf[f[a][j]][j].begin());
                    if (sz(invf[f[a][k]][k]) == 1) single[k].insert(*invf[f[a][k]][k].begin());
                }
                dom[a] = 0;
            }
            mult[j].clear();
            
        } else {
            trav(a, single[j]) {
                if (!sz(invf[f[a][j]][j])) continue;
                cerr << a << " ";
                assert(sz(invf[f[a][j]][j]) == 1);
                if (dom[a] == 1) {
                    invf[f[a][j]][j].erase(invf[f[a][j]][j].find(a));
                    invf[f[a][k]][k].erase(invf[f[a][k]][k].find(a));
                    if (sz(invf[f[a][k]][k]) == 1) single[k].insert(*invf[f[a][k]][k].begin());
                }
                dom[a] = 0;
            }
            single[j].clear();
        }
        cerr << nl;
    }
    bool ok = false;
    F0R(i, n) {
        if (dom[i]) {
            cout << i+1 << " ";
            ok = true;
        }
    }
    if (!ok) cout << -1;
    cout << nl;
    return 0;
}
