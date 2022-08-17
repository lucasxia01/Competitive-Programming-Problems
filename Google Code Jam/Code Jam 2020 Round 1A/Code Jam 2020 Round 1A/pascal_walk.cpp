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

void print(int i) {
    cout << "Case #" << i << ": \n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    FOR(t, 1, T) {
        int n;
        cin >> n;
        int x = n-34; // in case we add too many rows, we solve for a smaller number
        ll pow = 1<<30;
        int exp = 30; // we look at 30 rows, which has at most 465 numbers, so -34 keeps it under 500
        int marked[31] = {};
        int num = 0;
        while (pow >= 1) { // decompose into powers of 2
            if (pow <= x) {
                marked[exp] = 1;
                x -= pow;
                num++;
            }
            exp--;
            pow /= 2;
        }
        vpi path;
        bool left = 1;
        ll total = 0;
        for (int i = 0; i <= 30; i++) {
            if (marked[i]) { // take the whole row
                if (left) {
                    F0R(j, i+1) path.pb(mp(i+1, j+1));
                } else {
                    F0Rd(j, i+1) path.pb(mp(i+1, j+1));
                }
                left = !left;
                total += (1<<i);
            } else { // otherwise add 1
                if (left) path.pb(mp(i+1, 1));
                else path.pb(mp(i+1, i+1));
                total++;
            }
            if (total == n) break;
        }
        int i = 31;
        while (total < n) { // add in more rows if necessary: this is why we did -34 earlier
            if (left) path.pb(mp(i+1, 1));
            else path.pb(mp(i+1, i+1));
            i++;
            total++;
        }
        print(t);
        trav(a, path) {
            cout << a.f << " " << a.s << '\n';
        }
    }
    return 0;
}
