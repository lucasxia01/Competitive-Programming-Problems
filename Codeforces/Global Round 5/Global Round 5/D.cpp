#include <iostream>
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

#define F0R(i,n) for (ll i = 0; i < n; i++)
#define FOR(i,a,b) for (ll i = a; i < b; i++)
#define F0Rd(i,a) for (ll i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 1000011;
const ll INF = (1<<30) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n;
    cin >> n;
    ll a[n];
    F0R(i, n) cin >> a[i];
    ll b[2*n];
    F0R(i, n) b[i] = 1LL<<60;
    priority_queue<pi> pq;
    F0R(i, n) {
        pq.push(mp(a[i], i));
        while (2*a[i] < pq.top().f) {
            b[pq.top().s] = i;
            pq.pop();
        }
    }
    F0R(i, n) {
        while (2*a[i] < pq.top().f) {
            b[pq.top().s] = i+n;
            pq.pop();
        }
    }
    int count = 0;
    F0R(i, n) {
        b[i+n] = b[i]+n;
        if (b[i] < 1LL<<32) count++;
    }
    if (count == 0) {
        F0R(i, n) cout << -1 << " ";
        cout << endl;
        return 0;
    }
    ll seg[4*n];
    F0R(i, 2*n) {
        seg[i+2*n] = b[i];
    }
    F0Rd(i, 2*n) {
        seg[i] = min(seg[2*i], seg[2*i+1]);
    }
    F0R(i, n) {
        ll ans = 1LL<<60;
        ll l = i, r = i+n;
        for (l+=2*n, r+=2*n; l < r; l>>=1, r>>=1) {
            if (l&1) if (ans > seg[l++]) ans = seg[l-1];
            if (r&1) if (ans > seg[--r]) ans = seg[r];
        }
        //cout << i << " " << ans << endl;
        cout << ans-i << " ";
    }
    cout << endl;
    
    return 0;
}
