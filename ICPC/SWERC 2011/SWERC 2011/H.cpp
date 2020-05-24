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
const int MX = 1005;

bool bad[MX];
int f[MX];
map<string, int> m;
set<int> p[MX], q[MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for (int n, k; cin >> k >> n && n;) {
        m.clear();
        F0R(i, n) p[i].clear(), q[i].clear();
        memset(bad, 0, sizeof bad);
        memset(f, 0, sizeof f);
        string str;
        int count = 0;
        F0R(i, n) {
            cin >> str;
            if (m.find(str) == m.end()) m[str] = count++;
            int idx = m[str];
            assert(idx <= n);
            q[idx].insert(i+1);
            int freq[1001] = {};
            int x;
            F0R(j, k) {
                cin >> x;
                f[x]++;
                freq[x]++;
                if (freq[x] > 1) bad[x] = 1;
                p[idx].insert(x);
            }
        }
        FOR(i, 1, n) if (f[i] != k) bad[i] = 1;
        F0R(i, count) {
            assert(sz(q[i]));
            trav(a, q[i]) {
                if (p[i].find(a) != p[i].end()) bad[a] = 1;
            }
        }
        int ans = 0;
        FOR(i, 1, n) if (bad[i]) ans++;
        if (ans == 0) cout << "NO PROBLEMS FOUND" << nl;
        else if (ans == 1) cout << "1 PROBLEM FOUND" << nl;
        else cout << ans << " PROBLEMS FOUND" << nl;
        
    }
    return 0;
}
