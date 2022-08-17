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

const int MX = 1<<20;

int sum = 0;
int par[MX], sz[MX];

int ru(int x) {
    return ((x+9)/10 * 10);
}
int find(int i) {
    return (par[i]==i?i:par[i]=find(par[i]));
}
void merge(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    sum -= ru(sz[a]);
    sum -= ru(sz[b]);
    sz[a]+=sz[b];
    sum += ru(sz[a]);
    par[b] = a;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int p[n]; F0R(i, n) cin >> p[i];
    F0R(i, n) par[i] = i;
    F0R(i, n) sz[i] = p[i];
    int order[n]; F0R(i, n) { cin >> order[i];}
    int mark[n+2]; F0R(i, n+2) mark[i] = 0;
    int cnt = 0;
    ll ans = 0;
    F0Rd(i, n) {
        sum += ru(p[order[i]-1]);
        if (!mark[order[i]-1] && !mark[order[i]+1]) { // forms new segment
            cnt++;
        } else {
            if (mark[order[i]-1]) merge(order[i]-2, order[i]-1);
            if (mark[order[i]+1]) merge(order[i], order[i]-1);
            if (mark[order[i]-1] && mark[order[i]+1]) cnt--;
        }
        mark[order[i]] = 1;
//        sdbg(order[i], cnt, sum);
        ckmax(ans, 1LL*sum*cnt);
    }
    cout << ans << nl;
    return 0;
}

