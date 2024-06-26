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

const int MX = 1<<20;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

set<pi> s;
map<pi, pi> vis;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vpi v;
    F0R(i, n) {
        int a, b; cin >> a >> b;
        v.pb({a, b});
        s.insert({a, b});
    }
    queue<pi> q;
    F0R(i, n) {
        F0R(d, 4) {
            pi temp = {v[i].f+dx[d], v[i].s+dy[d]};
            if (s.find(temp) == s.end()) {
                vis[temp] = temp;
                q.push(temp);
            }
        }
    }
    while (!q.empty()) {
        pi cur = q.front(); q.pop();
        F0R(d, 4) {
            pi temp = {cur.f+dx[d], cur.s+dy[d]};
            if (s.find(temp) != s.end() && vis.find(temp) == vis.end()) {
                vis[temp] = vis[cur];
                q.push(temp);
            }
        }
    }
    F0R(i, n) cout << vis[v[i]].f << " " << vis[v[i]].s << nl;
    return 0;
}
