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

const int MX = 1e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vi sprimes, lprimes;
    bool isNotPrime[MX] = {};
    int SQRTN = sqrt(n);
    FOR(i, 2, n) {
        if (!isNotPrime[i]) {
            if (i > SQRTN) lprimes.pb(i); else sprimes.pb(i);
            for (int j = 2*i; j <= n; j+=i) isNotPrime[j] = 1;
        }
    }
    int x, y, z;
    ll ans = 1;
    trav(p, sprimes) {
        cout << "B " << p << nl; cout.flush();
        cin >> y;
        ll pow = p;
        while (pow <= n) {
            cout << "A " << pow << nl; cout.flush();
            cin >> x;
            if (!x) break;
            pow *= p;
        }
        ans *= pow/p;
    }
    cout << "A 1" << nl; cout.flush();
    cin >> x;
    int i = 0;
    int SZ = sz(lprimes);
    int SQRTSZ = sqrt(SZ);
    while (i < sz(lprimes)) { // lprimes have multiplicity of at most 1
        int j = 0;
        while (j < SQRTSZ && i+j < sz(lprimes)) {
            cout << "B " << lprimes[i+j] << nl; cout.flush();
            cin >> y;
            x -= y;
            j++;
        }
        cout << "A 1" << nl; cout.flush();
        cin >> z;
        if (z != x) { //  then its in this block of primes
            j = 0;
            while (j < SQRTSZ && i+j < sz(lprimes)) {
                cout << "A " << lprimes[i+j] << nl; cout.flush();
                cin >> y;
                if (y) {
                    ans *= lprimes[i+j];
                    cout << "C " << ans << nl;
                    return 0;
                }
                j++;
            }
        }
        i+=j;
    }
    cout << "C " << ans << nl;
    return 0;
}
