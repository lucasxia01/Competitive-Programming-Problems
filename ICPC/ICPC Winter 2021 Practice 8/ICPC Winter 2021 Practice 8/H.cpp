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
#include <climits>

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
const ll MOD = 123456789; // 998244353
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

const int MX = 1<<20;

vi facs, fs, others;
int b;

bool overflow(ll a, ll b) {
    __int128 aa = a;
    __int128 bb = b;
    __int128 c = (1LL<<62)-1 + (1LL<<62);
    return (aa*bb > c);
}

unordered_map<ll, ll> m;

ll solve(ll n) {
    if (m.find(n) != m.end()) return m[n];
    ll ret = -1;
    if (n < b) {
        m[n] = n;
        return n;
    }
    trav(f, facs) {
        if (f*f < b) break;
        if (n%f==0) {
            ll temp = solve(n/f);
            if (temp == -1) continue;
            if (overflow(temp, b) || overflow(temp*b+f, 1)) continue;
            if (ret == -1) ret = temp*b+f;
            ckmin(ret, temp*b+f);
        }
    }
    if (ret == -1) {
        trav(f, others) {
            if (f*f < b) break;
            if (n%f==0) {
                ll temp = solve(n/f);
                if (temp == -1) continue;
                if (overflow(temp, b) || overflow(temp*b+f, 1)) continue;
                if (ret == -1) ret = temp*b+f;
                ckmin(ret, temp*b+f);
            }
        }
    }
//    dbg(n, ret);
    m[n] = ret;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n; cin >> b >> n;
    ll N = n;
    FOR(i, 2, b-1) {
        if (N%i==0) {
            fs.pb(i);
            while (n%i==0) n/=i;
        }
    }
    trav(f, fs) {
        bool ok = 1;
        trav(g, fs) {
            if (g > f && g%f==0) {
                ok = 0;
                break;
            }
        }
        if (ok) facs.pb(f);
        else others.pb(f);
    }
    reverse(all(facs));
    reverse(all(others));
//    trav(f, facs) dbg(f);
    if (n != 1) {
        cout << "impossible" << nl;
        return 0;
    }
    if (N == 1) {
        cout << 1 << nl;
        return 0;
    }
    m[1] = 0;
    cout << solve(N) << nl;
    return 0;
}
