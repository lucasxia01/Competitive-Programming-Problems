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

#define F0R(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

ll LOG(ll n) {
    ll pow = 1;
    ll ans = 0;
    while (pow <= n) {
        ans++;
        pow *= 2;
    }
    return ans-1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    ll a[n];
    F0R(i, n) cin >> a[i];
    sort(a+1, a+n);
    ll j = a[0];
    a[0] = -1;
    vector<pair<ll, int> > p;
    int start = n-1;
    FORd(i, 1, n) {
        if (a[i-1] != a[i]) {
            p.pb(mp(a[i], start-(i-1)));
            //cout << a[i] << " " << start-(i-1) << endl;
            start = i-1;
        }
    }
    ll numMax = p[0].s;
    ll curMax = p[0].f, prevMax = curMax;
    ll curMove = 0, prevMove = 0;
    int idx = 1;
    ll LOGN = LOG(numMax), prevLOG = LOGN;
    while (true) {
        //cout << curMove << " " << numMax << " " << curMax << endl;
        if (idx >= p.size()) break;
        ll diff = p[idx-1].f - p[idx].f;
        curMax += (LOGN)*diff;
        curMove += (LOGN+1)*diff;
        numMax += p[idx].s;
        LOGN = LOG(numMax);
        if (curMax > j) {
            curMove = prevMove;
            curMax = prevMax;
            LOGN = prevLOG;
            break;
        }
        prevLOG = LOGN;
        prevMax = curMax;
        prevMove = curMove;
        idx++;
    }
    curMove += ((j-curMax)/LOGN)*(LOGN+1);
    curMax += ((j-curMax)/LOGN)*LOGN;
    //cout << curMove << " " << numMax << " " << curMax << endl;
    cout << curMove+j-curMax << endl;
    
    return 0;
}
