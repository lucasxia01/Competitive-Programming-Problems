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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int q, n;
    cin >> q;
    while (q--) {
        cin >> n;
        int a[n], b[n];;
        F0R(i, n) {
            cin >> a[i];
            b[i] = a[i];
        }
        int next[n+1], first[n+1], last[n+1], noOverlapNext[n+1];
        int groups = 1;
        F0R(i, n+1) {
            first[i] = -1;
            last[i] = -1;
            next[i] = -1;
            noOverlapNext[i] = -1;
        }
        sort(b, b+n);
        int cur = b[0];
        F0R(i, n) {
            if (cur != b[i]) {
                next[cur] = b[i];
                groups++;
            }
            cur = b[i];
        }
        next[cur] = -1;
        
        
        F0R(i, n)
            if (first[a[i]] == -1) first[a[i]] = i;
        F0Rd(i, n)
            if (last[a[i]] == -1) last[a[i]] = i;
        F0R(i, n) {
            if (first[a[i]] != -1) {
                if (next[a[i]] != -1 && last[a[i]] < first[next[a[i]]]) {
                    noOverlapNext[a[i]] = 1;
                } else noOverlapNext[a[i]] = 0;
            }
        }
        cur = b[0];
        int best = 1, count = 1;
        while (cur != -1) {
//            cout << cur << " " << next[cur] << " " << last[cur] << " " << first[next[cur]] << endl;
            if (noOverlapNext[cur] == 1) count++;
            else count = 1;
            if (count > best) best = count;
            cur = next[cur];
        }
        // cout << groups << " " << best << endl;
        cout << groups-best << endl;
    }
    return 0;
}
