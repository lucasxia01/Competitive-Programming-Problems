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

const int MX = 1e6;

struct P {
    ll x, y;
    ll dist(P o) { return (x-o.x)*(x-o.x)+(y-o.y)*(y-o.y);}
};

ll gcd(ll a, ll b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    P p[n];
    int count = 0, count1 = 0, count2 = 0;
    ll g = 0;
    F0R(i, n) {
        cin >> p[i].x >> p[i].y;
        if (i) {
            p[i].x -= p[0].x; p[i].y -= p[0].y;
            g = gcd(gcd(g, abs(p[i].x)), abs(p[i].y));
        }
    }
    p[0].x = 0; p[0].y = 0;

    F0R(i, n) {
        p[i].x /= g; p[i].y /= g;
        if ((p[i].x+p[i].y)%2==0) count++;
        if (p[i].x%2==0&&p[i].y%2==0) count1++;
        if (p[i].x%2==0&&p[i].y&1) count2++;
    }
    if (count > 0 && count < n) {
        cout << count << nl;
        F0R(i, n) if ((p[i].x+p[i].y)%2==0) cout << i+1 << " "; cout << nl;
        return 0;
    } else if (count == n) {
        cout << count1 << nl;
        F0R(i, n) if (p[i].x%2==0&&p[i].y%2==0) cout << i+1 << " "; cout << nl;
        return 0;
    } else {
        cout << count2 << nl;
        F0R(i, n) if (p[i].x%2==0&&p[i].y&1) cout << i+1 << " "; cout << nl;
        return 0;
    }
    return 0;
}
