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

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    int m[n], c[k];
    F0R(i, n) cin >> m[i];
    sort(m, m+n);
    F0R(i, k) cin >> c[i];
    int freq[k+1];
    memset(freq, 0, 4*k+4);
    F0R(i, n) freq[m[i]]++;
    vi ans[n];
    int count = 0;
    set<pi> q; // size of vector, index of vector
    q.insert({0, 0});
    F0Rd(i, k) {
        if (!freq[i+1]) continue;
        while (freq[i+1]) {
            pi t = *q.begin();
            assert(!q.empty());
            freq[i+1]--;
            if (t.f >= c[i]) {
                count++;
                ans[count].pb(i+1);
                q.insert({1, count});
                continue;
            }
            q.erase(q.begin());
            ans[t.s].pb(i+1);
            q.insert({t.f+1, t.s});
        }
    }
    cout << count+1 << nl;
    trav(a, ans) {
        if (!sz(a)) break;
        cout << sz(a) << " ";
        trav(b, a) {
            cout << b << " ";
        }
        cout << nl;
    }
    return 0;
}
