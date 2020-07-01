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

int n, m, t, l;
struct P {
    int i, a, l, o;
};
struct T {
    int t, z, v, c;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("unfair.in", "r", stdin);
//    freopen("unfair.out", "w", stdout);
    cin >> m >> n >> t >> l;
    P p[m];
    F0R(i, m) cin >> p[i].i >> p[i].a >> p[i].l >> p[i].o;
    T teams[t];
    F0R(i, t) cin >> teams[i].t >> teams[i].z >> teams[i].v >> teams[i].c;
    int hRank = INF, bestMask = -1;
    F0R(i, 1<<m) {
        if (__builtin_popcount(i) != n) continue;
        vector<pair<pi, int> > scores;
        F0R(tt, t) {
            vpi times;
            F0R(j, m) {
                if (i&(1<<j)) {
                    if (teams[tt].t+teams[tt].c < p[j].i-p[j].o) continue;
                    int e = (int)ceil((ld)p[j].i/p[j].o)+
                        max((int)ceil((ld)p[j].a/teams[tt].c), 5);
                    
                    int ttt = max(p[j].i-teams[tt].t, 0)+
                        (int)ceil((ld)p[j].a/(teams[tt].z+teams[tt].c))+
                        (int)ceil((ld)p[j].l/teams[tt].v);
                    times.pb({e, ttt});
                }
            }
            sort(times.begin(), times.end());
            int curTime = 0;
            int totalPen = 0;
            int k = 0;
            while (k < sz(times)) {
                curTime += times[k].s;
                if (curTime > l) break;
                totalPen += curTime;
                k++;
            }
            scores.pb({{-k, totalPen}, tt});
        }
        sort(scores.begin(), scores.end());
        F0R(ii, sz(scores)) {
            if (scores[ii].s == 0) {
                if (ckmin(hRank, ii+1)) bestMask = i;
                break;
            }
        }
    }
    F0R(i, m) {
        if (bestMask&(1<<i)) cout << i+1 << " ";
    }
    cout << nl;
    return 0;
}
