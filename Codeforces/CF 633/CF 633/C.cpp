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
    int t;
    cin >> t;
//    int marked[100000] = {};
//    int a = 1;
//    int c0 = 1;
//    ll precalc[t+7];
//    while (1) {
//        if (!marked[a]) {
//            int b = a+1;
//            while (marked[b] || marked[a^b]) {
//                b++;
//            }
////            cout << a << " " << b << " " << (a^b) << endl;
//            marked[a] = marked[b] = marked[a^b] = 1;
//            precalc[c0] = a;
//            precalc[c0+1] = b;
//            precalc[c0+2] = (a^b);
//            c0 += 3;
//        }
//        a++;
//        if (c0 > t) break;
//    }
//    int count = 0;
    while (t--) {
        ll n;
        cin >> n;
        ll x = (n-1)/3, y = (n-1)%3;
        ll pow = 1;
        ll c = 0;
        ll total = 0;
        while (total+pow <= x) {
            total += pow;
            c++;
            pow*=4;
        }
        x-= total;
        ll ans = pow*(y+1);
        int a[3][4] =   {
                        {0, 1, 2, 3},
                        {0, 2, 3, 1},
                        {0, 3, 1, 2}
                        };
        while (pow > 1) {
            pow /= 4;
            ans += pow*a[y][(x/pow)%4];
        }
//        cout << count << " " << precalc[count] << " " << ans << endl;
//        assert(precalc[count] == ans);
        cout << ans << endl;
    }
    return 0;
}
