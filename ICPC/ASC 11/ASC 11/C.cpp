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
//    freopen("bw.in", "r", stdin);
//    freopen("bw.out", "w", stdout);
    int n; cin >> n;
    pi p[n]; F0R(i, n) cin >> p[i].f >> p[i].s;
    sort(p, p+n);
    int curX = p[0].f;
    map<int, int> totalY;
    vi curY;
    ll totalB = 0, totalW = 0, curB = 0, curW = 0;
    F0R(i, n) { // sweepline based on x
        if (p[i].f != curX) {
            F0R(i, sz(curY)/2) { // go over all the y
                int a = curY[2*i], b = curY[2*i+1];
                int pos = 0;
                // we want to see if this segment is adding or deleting
                if (sz(totalY)&&totalY.upper_bound(a)!=totalY.end()) pos = (totalY.upper_bound(a)->s);
                ll sgn = (pos&1?-1:1);
                if (totalY.find(a) != totalY.end()) totalY.erase(totalY.find(a));
                else totalY.insert({a, pos});
                if (totalY.find(b) != totalY.end()) totalY.erase(totalY.find(b));
                else totalY.insert({b, !pos});
                if ((b-a)%2) {
                    if ((curX+a)%2) curW += sgn;
                    else curB += sgn;
                }
                curB += sgn * (b-a)/2;
                curW += sgn * (b-a)/2;
            }
            curY.clear();
            if ((p[i].f-curX)%2) {
                totalB += curB;
                totalW += curW;
                swap(curB, curW);
            }
            totalB += (p[i].f-curX)/2 * (curB+curW);
            totalW += (p[i].f-curX)/2 * (curB+curW);
        }
        curX = p[i].f;
        curY.pb(p[i].s);
    }
    cout << totalB << " " << totalW << nl;
    return 0;
}
