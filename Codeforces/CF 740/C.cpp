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
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 2021+5;
int a[MX];
vi v;
void rev(int x) {
    assert(x%2 && x > 0);
    v.pb(x);
    x--;
    F0R(i, x/2) swap(a[i], a[x-i]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        v.clear();
        int n; cin >> n;
        F0R(i, n) cin >> a[i];
        bool ok = 1;
        F0R(i, n) ok = ok&&((a[i]-i)&1);
        if (!ok) {
            cout << -1 << nl;
            continue;
        }
        int cur = n;
        while (cur > 1) {
            // find cur
            int p, q;
            F0R(i, n) {
                if (a[i] == cur) p = i;
                if (a[i] == cur-1) q = i;
            }
            p++;
            q++;
            if (p < q) {
                rev(p);
                rev(q-1);
                rev(q+1);
                rev(3);
                rev(cur);
            } else {
                rev(p);
                int qq = p+1-q;
                rev(qq-1);
                rev(qq+1);
                rev(3);
                rev(cur);
            }
            cur -= 2;
        }
        F0R(i, n-1) assert(a[i] < a[i+1]);
        cout << sz(v) << nl;
        trav(vv, v) cout << vv << ' '; cout << nl;
    }
    return 0;
}
