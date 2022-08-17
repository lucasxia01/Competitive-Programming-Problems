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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, x, y; cin >> n >> x >> y;
        int a[n]; F0R(i, n) cin >> a[i];
        vi cnt[n+2]; F0R(i, n) cnt[a[i]].pb(i);
        int unused = -1; FOR(i, 1, n+1) if (!sz(cnt[i])) { unused = i; break; }
        priority_queue<pi> pq; FOR(i, 1, n+1) if (sz(cnt[i])) pq.push({sz(cnt[i]), i});
        vi v;
        F0R(i, x) {
            assert(!pq.empty());
            pi p = pq.top(); pq.pop();
            assert(sz(cnt[p.s]));
            v.pb(cnt[p.s].back());
            cnt[p.s].pop_back();
            if (p.f > 1) pq.push({p.f-1, p.s});
        }
        int mapping[n]; F0R(i, n) mapping[i] = -1;
        trav(i, v) mapping[i] = 0;
        int m = n-x;
        vi ct[n+2]; F0R(i, n) if (mapping[i] == -1) ct[a[i]].pb(i);
        vector<pi> w;
        FOR(i, 1, n+1) if (sz(ct[i])) w.pb({-sz(ct[i]), i});
        sort(all(w));
        vi b; trav(i, w) trav(j, ct[i.s]) b.pb(j);
        assert(sz(b) == m);
//        trav(i, b) cout << i << " "; cout << nl;
        // shifting everything over by highest count
        if (sz(w)) {
            int hi = -w[0].f;
            F0R(i, m-hi) mapping[b[i+hi]] = a[b[i]];
            FOR(i, m-hi, m-1) mapping[b[i-(m-hi)]] = a[b[i]];
        }
        int count = 0;
        F0R(i, n) if (mapping[i] == a[i]) {
            mapping[i] = unused;
            count++;
        }
        if (count > n-y) {
            cout << "NO" << nl;
            continue;
        }
        F0R(i, n) if (mapping[i] && mapping[i] != unused) {
            if (count >= n-y) break;
            mapping[i] = unused;
            count++;
        }
        trav(i, v) mapping[i] = a[i];
        cout << "YES" << nl;
        F0R(i, n) cout << mapping[i] << " "; cout << nl;
    }
    return 0;
}
