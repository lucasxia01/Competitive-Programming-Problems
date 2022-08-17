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

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()
int n, m, q;
int fenw[MAX_N];
void upd(int x, int val) {
    while (x <= m) {
        fenw[x]+=val;
        x += x&(-x);
    }
}

int query(int x) {
    int ans = 0;
    while (x > 0) {
        ans += fenw[x];
        x -= x&(-x);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> q;
    ll a[n];
    int buf[m+1];
    int count = 0;
    int countL[m+1];
    F0R(i, n) {
        cin >> a[i];
        if (a[i] > a[0]) count++;
    }
    countL[0] = count;
    upd(1, count);
    buf[0] = n-1-count;
    vector<ll> r[m];
    int x, y;
    F0R(i, m) {
        cin >> x;
        buf[i] = n-1-count-x;
        F0R(j, x) {
            cin >> y;
            r[i].pb(y);
            if (y > a[0]) countL[i+1]++;
        }
        count += countL[i+1];
        upd(i+2, countL[i+1]);
    }
    int minBuf[m+1];
    minBuf[m-1] = buf[m-1];
    F0Rd(i, m-1) minBuf[i] = min(minBuf[i+1], buf[i]);
    int p;
    ll c;
    int off = 0;
    int fail = m+1;
    while (q--) {
        cin >> y >> p >> c;
        if (r[y-1][p-1] > a[0] && c < a[0]) {
            off--;
            upd(y+1, -1);
        }
        else if (r[y-1][p-1] < a[0] && c > a[0]) {
            off++;
            upd(y+1, 1);
        }
        r[y-1][p-1] = c;
        if ((y == m || minBuf[y] - off >= 0) && y <= fail) {
            cout << 1 << endl;
            fail = m+1;
        }
        else {
            int l = 0, r = m, mid = m;
            while (l < r) {
                cout << l << " " << r << endl;
                mid = (l+r)/2;
                if (query(mid+2) < off) l = mid+1;
                else r = mid;
            }
            if (r < fail) fail = r;
            cout << "left fail: " << fail << endl;
            cout << 0 << endl;
        }
    }
        
    return 0;
}
