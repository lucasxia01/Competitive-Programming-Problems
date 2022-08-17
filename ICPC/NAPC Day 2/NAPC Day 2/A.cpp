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
const ll INF = (1LL<<40) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;
ll x = 1, y = 1;
pl a[MX];
ll calcCost(int i) {
    if (i == -1) return INF;
    return 2LL*((a[i].f-x > 0) ? (a[i].f-x) : 0) + 2LL*((a[i].s-y > 0) ? (a[i].s-y) : 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    set<pair<ll, int> > top, right, top_right;
    vector<pair<ll, int> > sortedX, sortedY;
    F0R(i, n) {
        cin >> a[i].f >> a[i].s;
        if (a[i].f > x && a[i].s > y) top_right.insert(mp(a[i].f+a[i].s, i));
        else if (a[i].f > x) right.insert(mp(a[i].f, i));
        else if (a[i].s > y) top.insert(mp(a[i].s, i));
        else top.insert(mp(a[i].s, i));
    }
    top.insert(mp(INF, -1));
    right.insert(mp(INF, -1));
    top_right.insert(mp(INF, -1));
    int t;
    while (1) {
        // if stuff in top_right should be moved, move them to right and top
        while ((t = top_right.begin()->s) != -1 && (a[t].f <= x || a[t].s <= y)) {
            if (a[t].f <= x) top.insert(mp(a[t].s, t));
            else if (a[t].s <= y) right.insert(mp(a[t].f, t));
            top_right.erase(top_right.begin());
        }
        ll bestTop = calcCost(top.begin()->s);
        ll bestRight = calcCost(right.begin()->s);
        ll bestTopRight = calcCost(t);
        if (bestTop <= bestRight && bestTop <= bestTopRight) {
            if (bestTop == INF) break; // when all are INF, it will come here
            cout << top.begin()->s+1 << " ";
            ckmax(y, a[top.begin()->s].s); // update y
            top.erase(top.begin());
        } else if (bestRight <= bestTop && bestRight <= bestTopRight) {
            cout << right.begin()->s+1 << " ";
            ckmax(x, a[right.begin()->s].f); // update y
            right.erase(right.begin());
        } else {
            cout << t+1 << " ";
            ckmax(x, a[t].f);
            ckmax(y, a[t].s); // update y
            top_right.erase(top_right.begin());
        }
    }
    
    return 0;
}
