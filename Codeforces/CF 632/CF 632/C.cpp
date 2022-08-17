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

const int MAX_N = 100011;
const ll INF = (1LL<<50) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    ll a[n+1], p[n+1];
    F0R(i, n) cin >> a[i+1];
    p[0] = 0;
    F0R(i, n) p[i+1] = p[i]+a[i+1];
    map<ll, int> pos;
    ll nextPos[n+1];
    F0Rd(i, n+1) {
        if (pos.find(p[i])==pos.end()) {
            nextPos[i] = INF;
        } else nextPos[i] = pos[p[i]];
        // cout << i << " " << nextPos[i] << endl;
        pos[p[i]] = i;
    }
    multimap<ll, int> ms;
    ll ans = 0;
    int r = 0;
    F0R(i, n) { // i is index of left border
        while (!ms.empty() && ms.begin()->s < i) ms.erase(ms.begin());
        while (r < n+1 && r < ms.begin()->f) {
            ms.insert(mp(nextPos[r], r));
            r++;
        }
        //cout << i << " " << r << endl;
        ans += r-i-1;
    }
    cout << ans << endl;
    return 0;
}
