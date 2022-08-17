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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
 
const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);
 
template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }
 
void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }
 
#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif
 
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int MX = 2e5+5;
const int SQRT = 450;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vi sprimes; bool notPrime[SQRT] = {};
    FOR(i, 2, SQRT-1) {
        if (!notPrime[i]) {
            sprimes.pb(i);
            for (int j = 2*i; j < SQRT; j+= i) notPrime[j] = 1;
        }
    }
    int n; cin >> n;
    int a[n]; F0R(i, n) cin >> a[i];
    int N = sz(sprimes);
    ll st[N+1][2*n];
    F0R(i, n) {
        F0R(j, N) {
            ll temp = 1;
            while (a[i]%sprimes[j] == 0) {
                temp *= sprimes[j];
                a[i] /= sprimes[j];
            }
            st[j][i+n] = temp;
        }
        st[N][i+n] = a[i];
    }
    F0R(j, N) FORd(i, 1, n-1) st[j][i] = max(st[j][i<<1], st[j][i<<1|1]);
    FORd(i, 1, n-1) st[N][i] = (st[N][i<<1]*st[N][i<<1|1])%MOD;
    int q; cin >> q;
    ll last = 0;
    while (q--) {
        int L, R; cin >> L >> R;
        L = (L+last)%n+1; R = (R+last)%n+1;
        if (L > R) swap(L, R);
        L--;
        ll ans = 1;
        F0R(j, N) {
            ll temp = 1;
            int l = L, r = R;
            for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
                if (l&1) ckmax(temp, st[j][l++]);
                if (r&1) ckmax(temp, st[j][--r]);
            }
            ans = (ans*temp)%MOD;
        }
        int l = L, r = R;
        for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
            if (l&1) ans = (ans * st[N][l++])%MOD;
            if (r&1) ans = (ans * st[N][--r])%MOD;
        }
        cout << ans << nl;
        last = ans;
    }
    
    return 0;
}
