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
    int t; cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        F0R(i, n) cin >> a[i];
        vi ops;
        int mex = 0;
        int freq[n+1]; F0R(i, n+1) freq[i] = 0;
        F0R(i, n) freq[a[i]]++;
        while (freq[mex]) mex++;
        while (1) {
            if (mex == n) {
                F0R(i, n) {
                    if (a[i] != i) {
                        freq[a[i]]--;
                        assert(!freq[a[i]]);
                        int prev = a[i];
                        a[i] = n;
                        freq[n]++;
                        ops.pb(i);
                        mex = prev;
                        int nxt = 0;
                        while (freq[nxt]) nxt++;
                        assert(nxt == mex);
                        break;
                    }
                }
                bool ok = 1;
                F0R(i, n-1) if (a[i] > a[i+1]) ok = 0;
                if (ok) break;
            }
            assert(mex < n);
            ops.pb(mex);
            freq[a[mex]]--;
            freq[mex]++;
            int nxt = 0;
            while (freq[nxt]) nxt++;
            assert(nxt <= n);
            a[mex] = mex;
            mex = nxt;
            bool ok = 1;
            F0R(i, n-1) if (a[i] > a[i+1]) ok = 0;
            if (ok) break;
//            cout << mex << nl;
//            F0R(i, n) cout << a[i] << ' '; cout<<nl;
        }
        cout << sz(ops) << nl;
        trav(a, ops) cout << a+1 << " "; cout << nl;
        
    }
    return 0;
}
