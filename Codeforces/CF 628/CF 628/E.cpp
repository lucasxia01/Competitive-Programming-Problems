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

const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

const int MX = 1e6+5;
bool prime[MX];
bool marked[MX];
vi edges[MX];
int dist[MX];

int bfs(int s) {
    F0R(i, MX) if (dist[i] != INF) dist[i] = -1;
    queue<int> q, par;
    q.push(s);
    par.push(-1);
    dist[s] = 0;
    int ret = INF;
    int minDistMarked = INF;
    while (!q.empty()) {
        int x = q.front(), p = par.front();
        if (marked[x]) {
            //cout << s << " " << x << endl;
            ckmin(ret, dist[x] + minDistMarked+2);
            ckmin(minDistMarked, dist[x]);
        }
        //cout << x << endl;
        q.pop(); par.pop();
        trav(a, edges[x]) {
            if (dist[a] == -1) {
                q.push(a);
                par.push(x);
                dist[a] = dist[x]+1;
            } else if (a != p) {
                ckmin(ret, dist[a] + dist[x] + 1);
            }
        }
    }
    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    F0R(i, MX) dist[i] = INF;
    vi primes;
    primes.pb(2);
    for (int i = 3; i <= sqrt(MX); i+=2) {
        if (!prime[i]) {
            dist[i] = -1;
            primes.pb(i);
            for (int j = 3*i; j <= sqrt(MX); j += 2*i) {
                prime[j] = true;
            }
        }
    }
    int n;
    cin >> n;
    int a[n];
    F0R(i, n) cin >> a[i];
    vi f[n];
    set<int> check;
    F0R(i, n) {
        for (int j = 0; j < primes.size(); j++) {
            int count = 0;
            while (!(a[i]%primes[j])) {
                count++;
                a[i] /= primes[j];
            }
            if (count&1) f[i].pb(primes[j]);
        }
        if (a[i] > 1) {
            f[i].pb(a[i]);
            dist[a[i]] = -1;
        }
        if (f[i].size() == 0) {
            cout << 1 << endl;
            return 0;
        } else if (f[i].size() == 1) marked[f[i][0]] = true;
    }
    F0R(i, n) {
        int prod = 1;
        trav(a, f[i]) prod *= a;
        
        int SZ = (int)check.size();
        check.insert(prod);
        if (SZ == check.size()) {
            cout << 2 << endl;
            return 0;
        }
    }
    F0R(i, n) {
        if (f[i].size() == 2) {
            edges[f[i][0]].pb(f[i][1]);
            edges[f[i][1]].pb(f[i][0]);
            //cout << f[i][0] << " " << f[i][1] << endl;
        }
    }
    int ans = INF;
    trav(p, primes) {
        int ret = bfs(p);
        ckmin(ans, ret);
        //cout << p << " " << ret << endl;
    }
    if (ans == INF) cout << -1 << endl;
    else cout << ans << endl;
    
    
    return 0;
}
