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
int n;
ll fenw[MAX_N+1];

void upd(int i, ll val) {
    while (i <= n) {
        fenw[i] += val;
        i += (i&-i);
    }
}

ll get(int i) {
    ll sum = 0;
    while (i > 0) {
        sum += fenw[i];
        i -= (i&-i);
    }
    return sum;
}

int query(ll sum) {
    int LOGN = 0;
    ll pow = 1;
    while (pow <= n) {
        LOGN++;
        pow *= 2;
    }
    int pos = 0;
    ll cur = 0;
    F0Rd(i, LOGN) {
        ll add = (1LL<<i);
        if (pos+add <= n && cur + fenw[pos+add] <= sum) {
            pos += add;
            cur += fenw[pos];
        }
    }
    return pos+1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    ll s[n];
    F0R(i, n) {
        cin >> s[i];
        upd(i+1, i+1);
    }
    
    int ans[n];
    F0Rd(i, n) {
        int val = query(s[i]);
//        F0R(i, n+1) {
//            cout << fenw[i] << " ";
//        } cout << endl;
        upd(val, -val);
        ans[i] = val;
    }
    F0R(i, n) {
        cout << ans[i] << " ";
    } cout << endl;
    return 0;
}
