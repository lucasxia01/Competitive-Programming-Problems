#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>

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


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    ll a[n];
    F0R(i, n) cin >> a[i];
    sort(a, a + n);
    int mid = n/2;
    ll counts[mid+2];
    counts[0] = 0;
    counts[mid+1] = 1LL<<60;
    for (int i = mid + 1; i < n; i++) {
        counts[i - mid] = counts[i-mid-1]+(a[i]-a[i-1])*(i-mid);
        //cout << counts[i-mid] << endl;
    }
    int i = mid;
    while (counts[i+1-mid] <= k) i++;
    
    ll r = k - counts[i-mid];
    ll q = r/(i-mid+1);
    //cout << r << " " << q << " " << i-mid+1 << endl;
    cout << a[i]+q << endl;
    return 0;
}

