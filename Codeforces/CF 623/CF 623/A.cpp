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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int a[n], t[n];
    F0R(i, n) cin >> a[i];
    F0R(i, n) cin >> t[i];
    vpi v;
    F0R(i, n) v.pb(mp(a[i], t[i]));
    sort(v.begin(), v.end());
    ll ans = 0;
    ll total = 0;
    priority_queue<ll> pq;
    int cur = 0;
    F0R(i, n) {
        cur = v[i].f;
        pq.push(v[i].s);
        total += v[i].s;
        //cout << v[i].f << endl;
        while (pq.size() && (i == n-1 || cur < v[i+1].f)) {
            //cout << cur << " " << pq.top() << endl;
            total -= pq.top();
            pq.pop();
            cur++;
            ans += total;
        }
        
    }
    cout << ans << endl;
    return 0;
}
