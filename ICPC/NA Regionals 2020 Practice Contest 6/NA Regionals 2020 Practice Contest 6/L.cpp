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

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 4e5+5;

int st[2*MX];
int n;
void upd(int i, int v) {
    i += n;
    while (i > 0) {
        ckmax(st[i], v);
        i >>= 1;
    }
}

int query(int l, int r) {
    int ret = -1;
    for(l += n, r += n; l < r; l>>=1, r>>=1) {
        if (l&1) ckmax(ret, st[l++]);
        if (r&1) ckmax(ret, st[--r]);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    int a[n];
    vi pos[n+1];
    F0R(i, n) {
        cin >> a[i];
        pos[a[i]].pb(i);
    }
    FOR(i, 1, n) sort(all(pos[i]));
    int cur[n+1]; F0R(i, n+1) cur[i] = 0;
    int minA = INF;
    F0R(i, n) {
        int ptr = cur[a[i]];
        if (ptr > 0) { // there was a previous
            int prev = pos[a[i]][ptr-1]+1;
            int ret = query(prev, i);
//            dbg(i, a[i], prev, i, ret);
            if (ret > i) ckmin(minA, a[i]);
        }
        if (ptr+1 < sz(pos[a[i]])) {
            ptr = ++cur[a[i]];
            int nxt = pos[a[i]][ptr];
            upd(i, nxt);
        }
    }
    if (minA == INF) {
        cout << -1 << nl;
        return 0;
    }
    int ptr = 0;
    int minB = INF;
    FOR(i, pos[minA].front()+1, pos[minA].back()-1) {
        if (a[i] == minA) ptr++;
        else if (pos[a[i]].back() > pos[minA][ptr+1]) ckmin(minB, a[i]);
    }
    cout << minA << " " << minB << nl;
    return 0;
}
