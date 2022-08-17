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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T, b;
    cin >> T >> b;
    F0R(t, T) {
        string ans(b, '2');
        // find same and different
        int same = -1, diff = -1; // same figures out complements, diff for reverse
        int i = 1;
        int q = 0;
        bool ok = true;
        while (1) {
            char x, y;
            if (q > 150) break;
            if (q%10 == 0 && !(same == -1 && diff == -1)) { // figure it out
                if (same != -1) { // query same
                    cout << same << endl; fflush(stdout); q++;
                    cin >> x;
                    if (ans[same-1] != x) {// everything complemented
                        F0R(j, b) {
                            if (ans[j] == '0') ans[j] = '1';
                            else if (ans[j] == '1') ans[j] = '0';
                        }
                    } // else we don't do anything
                }
                if (diff != -1) { // query same
                    cout << diff << endl; fflush(stdout); q++;
                    cin >> x;
                    if (ans[diff-1] != x) {// everything reversed
                        F0R(j, (b+1)/2) {
                            if (ans[j] != '2') swap(ans[j], ans[b-j-1]);
                        }
                    } // else we don't do anything
                }
                if (q%2) { // waste a query to make it even :))
                    cout << 1 << endl; fflush(stdout); q++;
                    cin >> x;
                }
                continue;
            }
            cout << i << endl; fflush(stdout); q++;
            cin >> x;
            ans[i-1] = x;
            cout << b-i+1 << endl; fflush(stdout); q++;
            cin >> y;
            ans[b-i] = y;
            if (same == -1 && x == y) same = i;
            else if (diff == -1 && x != y) diff = i;
            i++;
            if (i >= (b+1)/2+1) {
                cout << ans << endl; fflush(stdout);
                cin >> x;
                if (x == 'N') ok = false;
                break;
            }
        }
        if (!ok) break;
    }
    return 0;
}
