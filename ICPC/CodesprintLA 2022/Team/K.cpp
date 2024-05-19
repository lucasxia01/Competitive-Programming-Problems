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

const int MX = 1e5+5;
int arr[MX], RANK[MX];

// Finding the root of node i
int root(int i)
{
    while (arr[i] != i)
    {
       arr[i] = arr[arr[i]];
       i = arr[i];
    }
    return i;
}
 
// union of two nodes a and b
void weighted_union(int a, int b)
{
    int root_a = root ( a);
    int root_b = root (b);
 
    // union based on RANK
    if (RANK[root_a] < RANK[root_b])
    {
       arr[root_a] = arr[root_b];
       RANK[root_b] += RANK[root_a];
    }
    else
    {
        arr[root_b] = arr[root_a];
        RANK[root_a] += RANK[root_b];
    }
}
 
// Returns true if two nodes have same root
bool areSame(int a, int b)
{
    return (root(a) == root(b));
}
 
// Performing an operation according to query type
void query(int type, int x, int y)
{
    // type 1 query means checking if node x and y
    // are connected or not
    if (type == 1)
    {
        // If roots of x and y is same then yes
        // is the answer
        if (areSame(x, y) == true)
            cout << "Yes" << endl;
        else
           cout << "No" << endl;
    }
 
    // type 2 query refers union of x and y
    else if (type == 2)
    {
        // If x and y have different roots then
        // union them
        if (areSame(x, y) == false)
            weighted_union(x, y);
    }
}

int dp[MX];

vpi gr[MX];

void dfs(int v) {
    trav(u, gr[v]) {
        if (dp[u.f] == -1) {
            dp[u.f] = (dp[v]^u.s);
            dfs(u.f);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, k, t; cin >> n >> m >> k >> t;
    FOR(i, 1, n) {
        arr[i] = i;
        RANK[i] = 1;
    }
    vpi v; vi x;
    F0R(i, m) {
        int a, b; cin >> a >> b; string s; cin >> s;
        v.pb({a, b});
        x.pb((s=="imposter"));
    }
    F0R(i, m) {
        if (lc.connected(1, k)) {
            cout << i+1 << nl;
            F0R(j, m-t) {
                int a = v[(i+j)%m].f, b = v[(i+j)%m].s;
                gr[a].pb({b, x[i]});
                gr[b].pb({a, x[i]});
            }
            F0R(j, MX) dp[j] = -1;
            dp[i] = 0;
            dfs(i);
            cout << (dp[k]?"imposter":"crewmate") << nl;
            return 0;
        }
        dbg(v[i].f, v[i].s);
        dbg(v[(i+t)%m].f, v[(i+t)%m].s);
        lc.link(v[i].f, v[i].s);
        lc.cut(v[(i+t)%m].f, v[(i+t)%m].s);
    }
    cout << -1 << nl;

    return 0;
}
