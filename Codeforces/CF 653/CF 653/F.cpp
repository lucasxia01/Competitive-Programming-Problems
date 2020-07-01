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
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 505;
vi ans;
bool fail = 0;
int n;
void shift(vi& v, int i) {
    if (i+2 >= n) {
        fail = 1;
        return;
    }
    ans.pb(i);
    int temp = v[i];
    v[i] = v[i+2];
    v[i+2] = v[i+1];
    v[i+1] = temp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        fail = 0;
        ans.clear();
        vi freq[MX];
        vi a(n);
        F0R(i, n) {
            cin >> a[i];
            freq[a[i]].pb(i);
        }
        bool dup = 0;
        int dupval = -1;
        int count = 0;
        int dupidx = -1;
        F0R(i, MX) {
            if (sz(freq[i]) > 1) {
                dup = 1;
                dupval = i;
                a[freq[i][0]] = INF; a[freq[i][1]] = INF;
                dupidx = count;
                break;
            }
            count += sz(freq[i]);
        }
        F0R(i, (dup?n-2:n)) {
            int lo = INF, idx = -1;
            FOR(j, i, n-1) if (ckmin(lo, a[j])) idx = j;
            // end is i, start is idx
//            cout << lo << " " << i << " " << idx << nl;
            while (idx > i) {
                if (idx-i == 1) {
                    shift(a, i);
                    shift(a, i);
                    idx--;
                } else {
                    shift(a, idx-2);
                    idx-=2;
                }
                if (fail) break;
            }
            if (!fail) assert(a[i] == lo);
            else break;
        }
        if (dup) {
            // gotta move it to dupidx, dupidx+1 from n-2 and n-1
            int idx = n-2, i = dupidx;
            if (idx-i == 1) {
                shift(a, i); shift(a, i);
            } else { // now we won't touch n-1 when we move n-2
                while (idx > i) {
                    if (idx-i == 1) {
                        shift(a, i);
                        shift(a, i);
                        idx--;
                    } else {
                        shift(a, idx-2);
                        idx-=2;
                    }
                }
                assert(!fail);
                idx = n-1; i = dupidx+1; // this run shouldn't affect dupidx
                while (idx > i) {
                    if (idx-i == 1) {
                        shift(a, i);
                        shift(a, i);
                        idx--;
                    } else {
                        shift(a, idx-2);
                        idx-=2;
                    }
                }
                assert(!fail);
            }
        }
        if (fail) cout << -1 << nl;
        else { // hopefully under n^2 ??
            if (dup) {
                a[dupidx] = dupval;
                a[dupidx+1] = dupval;
            }
            F0R(i, n-1) assert(a[i] <= a[i+1]);
            cout << sz(ans) << nl;
            trav(u, ans) cout << u+1 << " "; cout << nl;
        }
    }
    return 0;
}
