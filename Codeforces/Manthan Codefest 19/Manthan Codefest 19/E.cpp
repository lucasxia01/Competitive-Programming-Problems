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
    int n, w;
    cin >> n >> w;
    int l[n];
    int x;
    ll ans[w], pf[w+1];
    F0R(i, w+1) ans[i] = pf[i] = 0;
    F0R(i, n) {
        cin >> l[i];
        deque<pair<ll, int>> store;
        int window = w-l[i]+1;
        int best = -INF;
        for (int j = 0; j < w; j++) {
            if (j < l[i]) {
                cin >> x;
                while (!store.empty() && x >= store.back().f) store.pop_back();
                store.pb(mp(x, j));
                best = max(best, x);
            } else if (j == l[i] && j < window) {
                j = window;
                //cout << best << endl;
                if (best >= 0) {
                    pf[l[i]] += best;
                    pf[window] -= best;
                } else {
                    if (window-1 < w-window+1) {
                        pf[window-1] += best;
                        pf[w-window+1] -= best;
                    }
                }
            }
            if (j == w) break;
            while (store.front().s <= j-window) store.pop_front();
            if (store.front().f > 0 || (j >= window-1 && j <= w-window)) {
                ans[j] += 1LL*store.front().f;
                //cout << store.front().f << endl;
            }
             
        }
    }
    ll total = 0;
    F0R(i, w) {
        //cout << pf[i] << " ";
        total += pf[i];
        cout << ans[i]+total << " ";
    }
    cout << endl;
    return 0;
}
