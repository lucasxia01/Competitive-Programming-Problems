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

#define int ll

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

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3000+5;

#define tri(n) (n)*((n)+1)/2

vi gr[MX];
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    F0R(i, 2*n) {
        int a, b; cin >> a >> b;
        gr[a].pb(b); gr[b].pb(a);
    }
    ll ans = 0;
    FOR(i, 1, 2*n) {
        //initialize the dudes
        int a = 0, b = 2*n+1, c = 0, d = 2*n+1;
        bool vis[2*n+1]; F0R(i, 2*n+1) vis[i] = 0;
        if (i <= n) a = b = i;
        else c = d = i;
        queue<int> q;
        dbg("i", i, sz(gr[i]));
        q.push(gr[i][0]); 
        q.push(gr[i][1]); 
        vis[i] = 1;
        vis[gr[i][0]] = vis[gr[i][1]] = 1;
        int sum = 0;
        while (1) {
            int u = q.front(); q.pop();
            int v = q.front(); q.pop();
            dbg(u, v, a, b, c, d);
            // first add for previous
            if (u <= n) {
                if (a == 0) {
                    int hi = max(u, v), lo = min(u, v);
                    sum += (2*n-i+1)*(i-n)*(tri(n-hi)+tri(hi-lo-1)+tri(lo-1));
                } else {
                    if ((u >= b && u <= a) || (v >= b && v <= a)) ans += 0;
                    else {
                        int hi = n+1, lo = 0;
                        if (u > a) hi = u;
                        else lo = u;
                        if (v > a) ckmin(hi, v);
                        else ckmax(lo, v);
                        sum += (2*n-c+1)*(d-n)*(hi-a)*(b-lo);
                    }
                }
            } else {
                if (c == 0) { // first iteration
                    int hi = max(u, v), lo = min(u, v);
                    dbg("hilo", lo, hi, n-i+1, i, tri(2*n-hi), tri(hi-lo-1), tri(lo-n-1));
                    sum += (n-i+1)*i*(tri(2*n-hi)+tri(hi-lo-1)+tri(lo-n-1));
                } else {
                    if ((u >= d && u <= c) || (v >= d && v <= c)) ans += 0;
                    else {
                        int hi = 2*n+1, lo = n;
                        if (u > c) hi = u;
                        else lo = u;
                        if (v > c) ckmin(hi, v);
                        else ckmax(lo, v);
                        sum += (n-a+1)*b*(hi-c)*(d-lo);
                    }
                }
            }
            if (u == v) break; //cycle formed
            if (u <= n) {
                ckmax(a, u);
                ckmax(a, v);
                ckmin(b, u);
                ckmin(b, v);
            } else {
                ckmax(c, u);
                ckmax(c, v);
                ckmin(d, u);
                ckmin(d, v);
            }
            // now add next ones
            if (!vis[gr[u][0]]) q.push(gr[u][0]); 
            if (!vis[gr[u][1]]) q.push(gr[u][1]); 
            if (!vis[gr[v][0]]) q.push(gr[v][0]); 
            if (!vis[gr[v][1]]) q.push(gr[v][1]); 
            vis[gr[u][0]] = vis[gr[u][1]] = 1;
            vis[gr[v][0]] = vis[gr[v][1]] = 1;
            assert(sz(q) == 2);
        }
        dbg(sum);
        ans += sum;
    }
    int total = 0;
    F0R(i, n) F0R(j, i+1) {
        total += 2*tri(n) * (i-j+1);
    }
    dbg(total, ans);
    cout << (total-ans)/2 << nl;
    return 0;
}
