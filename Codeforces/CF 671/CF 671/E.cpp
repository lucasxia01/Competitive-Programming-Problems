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

const int MX = 1e5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vi primes;
    bool isNotP[MX] = {};
    FOR(i, 2, MX-1) {
        if (!isNotP[i]) {
            primes.pb(i);
            for (int j = 2*i; j < MX; j+=i) isNotP[j] = 1;
        }
    }
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int m = n, N = n;
        vpi decomp;
        trav(p, primes) {
            int cnt = 0;
            while (n%p == 0) {
                cnt++;
                n /= p;
            }
            if (cnt) decomp.pb({p, cnt});
        }
        if (n != 1) decomp.pb({n, 1});
        vi order;
        set<int> used;
        int SZ = sz(decomp);
        int numDiv = 1;
        F0R(j, SZ) {
            pi p = decomp[j], q = decomp[(j+1)%SZ];
//            cout << p.f << " " << p.s << nl;
            numDiv *= p.s+1;
            int M = m;
            int temp = 1;
            if (j < SZ-1) F0R(i, q.s) M /= q.f;
            M /= p.f; temp *= p.f;
            // everything divisible by p.f but not q.f
            for (int i = 1; i*i <= M; i++) {
                if (M%i == 0) {
                    if (i*i != M) order.pb(i*temp);
                    if (M/i*temp != N) order.pb(M/i*temp);
                }
            }
            if (j < SZ-1) {
                int temp = (p.f * q.f);
                int M = m/temp;
                // everything divisible by p.f and q.f
                for (int i = 1; i*i <= M; i++) {
                    if (M%i == 0) {
                        if (i*i != M) order.pb(i*temp);
                        if (M/i*temp != N) order.pb(M/i*temp);
                    }
                }
            }
            // no longer need p.f
            F0R(i, p.s) m /= p.f;
        }
        order.pb(N);
        assert(sz(order) == numDiv-1);
        trav(o, order) cout << o << " "; cout << nl;
        if (sz(decomp) == 2 && decomp[0].s == 1 && decomp[1].s == 1) cout << 1 << nl;
        else cout << 0 << nl;
    }
    return 0;
}
