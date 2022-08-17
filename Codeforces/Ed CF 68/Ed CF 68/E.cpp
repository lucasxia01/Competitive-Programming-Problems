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
const int N = 10001;
int n;
const int bias = N/2;
vpi h[N], v[N];
int fenw[N+1];
vi curY[N];

void upd(int p, int v) {
    p++;
    while (p <= N) {
        fenw[p] += v;
        p += (p & -p);
    }
}

int query(int p) {
    int sum = 0;
    p++;
    while (p > 0) {
        sum += fenw[p];
        p -= (p & -p);
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int x1, y1, x2, y2;
    F0R(i, n) {
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += bias; y1 += bias; x2 += bias; y2 += bias;
        if (x1 == x2) {
            v[x1].pb(mp(min(y1, y2), max(y1, y2)));
        } else {
            h[y1].pb(mp(min(x1, x2), max(x1, x2)));
        }
    }
    ll ans = 0;
    F0R(y, N) {
        trav(a, h[y]) {
            memset(fenw, 0, (N+1)*sizeof(int));
            F0R(i, N) curY[i].clear();
            FOR(x, a.f, a.s+1) {
                trav(ax, v[x]) {
                    if (ax.f <= y && ax.s > y) {
                        upd(x, 1);
                        //cout << y-bias << " " << x-bias << endl;
                        curY[ax.s].pb(x);
                    }
                }
            }
            FOR(yy, y+1, N) {
                trav(a1, h[yy]) {
                    ll temp = query(a1.s) - query(a1.f-1);
                    //cout << temp << endl;
                    ans += temp*(temp-1)/2;
                }
                trav(a1, curY[yy]) upd(a1, -1);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
