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

const int MX = 1000;

int cnt = 0;
int n, m;
int par[MX*MX], sz[MX*MX];

int find(int i) {
    return (par[i]==i?i:par[i]=find(par[i]));
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    cnt--;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
}

void reset() {
    F0R(i, n) F0R(j, m) {
        int idx = i*m+j;
        par[idx] = idx;
        sz[idx] = 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    char a[n][m]; F0R(i, n) F0R(j, m) cin >> a[i][j];
    // white
    int pref[m+1], suf[m+1];
    pref[0] = 0;
    suf[m] = 0;
    reset();
    cnt = 0;
    F0R(j, m) {
        F0R(i, n) cnt += (a[i][j] == '0');
        F0R(i, n) {
            if (a[i][j] != '0') continue;
            if (i > 0 && a[i-1][j] == '0') merge((i-1)*m+j, i*m+j);
            if (j > 0 && a[i][j-1] == '0') merge(i*m+j, i*m+(j-1));
        }
        pref[j+1] = cnt;
    }
    cnt = 0;
    reset();
    F0Rd(j, m) {
        F0R(i, n) cnt += (a[i][j] == '0');
        F0R(i, n) {
            if (a[i][j] != '0') continue;
            if (i > 0 && a[i-1][j] == '0') merge((i-1)*m+j, i*m+j);
            if (j < m-1 && a[i][j+1] == '0') merge(i*m+j, i*m+(j+1));
        }
        suf[j] = cnt;
    }
//    F0R(i, m+1) dbg(pref[i]);
//    F0R(i, m+1) dbg(suf[i]);
    reset();
    F0R(j, m) {
        F0R(i, n) {
            if (a[i][j] != '1') continue;
            if (i > 0 && a[i-1][j] == '1') merge((i-1)*m+j, i*m+j);
            if (j > 0 && a[i][j-1] == '1') merge(i*m+j, i*m+(j-1));
        }
    }
    int total = 0;
    F0R(i, n) F0R(j, m) if (a[i][j] == '1' && find(i*m+j) == i*m+j) total++;
//    dbg(total);
    int ans = 0;
    int bestW = 0;
    F0R(j, m) {
        unordered_set<int> s;
        F0R(K, 3) {
            int k = K-1;
            if (j+k < 0 || j+k >= m) continue;
            F0R(i, n) if (a[i][j+k] == '1') s.insert(find(i*m+j+k));
        }
//        trav(ss, s) dbg(ss);
        int cur = total+1-sz(s);
        int w = pref[j] + suf[j+1];
//        dbg(j, cur, w);
        cur += w;
        if (cur > ans || (cur == ans && w > bestW)) {
            ans = cur;
            bestW = w;
        }
    }
    cout << bestW << " " << ans-bestW << nl;
    return 0;
}
