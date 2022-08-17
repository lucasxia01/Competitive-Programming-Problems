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

const int MX = 2e5+5;
int n;
int a[MX];
bool ok = 1;

unordered_map<int, int> solve(int l, int r) { // [l, r)
    dbg("range", l, r);
    unordered_map<int, int> m, total;
    FOR(i, l, r-1) {
        if (m.find(a[i]) == m.end()) m[a[i]] = i;
        else m[a[i]] = -1;
        if (total.find(a[i]) == total.end()) total[a[i]] = 1;
        else total[a[i]]++;
    }
    if (l >= r-1 || ok == 0) return total;
    unordered_map<int, int> ret = total;
    vi v = {r};
    trav(p, m) if (p.s != -1) v.pb(p.s);
//    trav(u, v) cout << u << " "; cout << nl;
    if (sz(v) == 1) {
        ok = 0;
        return ret;
    }
    sort(all(v));
    int L = l, R = r;
    bool big = 1;
    while (big) {
        dbg("range", L, R);
        trav(u, total) dbg(u.f, u.s);
        big = 0;
        unordered_map<int, int> cur;
        int prev = L-1;
        vector<pair<int, pi > > segs;
        trav(u, v) {
            segs.pb({u-prev-1, {prev+1, u}});
            if (u != R) total[a[u]]--;
            prev = u;
        }
        sort(all(segs));
//        trav(seg, segs) cout << seg.f << " " << seg.s.f << " " << seg.s.s << nl;
        trav(seg, segs) {
            if (2*seg.f <= R-L) { // small piece
                unordered_map<int, int> temp = solve(seg.s.f, seg.s.s);
                trav(t, temp) {
                    if (cur.find(t.f) == cur.end()) cur[t.f] = t.s;
                    else cur[t.f] += t.s;
                }
            } else { // big piece (should be last)
                L = seg.s.f; R = seg.s.s;
                v = {R};
                trav(u, cur) {
                    total[u.f] -= u.s;
                    if (total[u.f] == 1) {
                        v.pb(u.f);
                    }
                }
                if (sz(v) == 1) { // nothing unique
                    ok = 0;
                    return ret;
                }
                sort(all(v));
                big = 1;
            }
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        ok = 1;
        cin >> n;
        F0R(i, n) cin >> a[i];
        vpi v; F0R(i, n) v.pb({a[i], i});
        sort(all(v));
        int cur = 0;
        F0R(i, n) {
            a[v[i].s] = cur;
            if (i == n-1 || v[i].f != v[i+1].f) cur++;
        }
        
        solve(0, n);
        cout << (ok?"non-boring":"boring") << nl;
    }
}
