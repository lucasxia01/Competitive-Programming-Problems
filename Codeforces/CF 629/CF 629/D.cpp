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

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        F0R(i, n) cin >> a[i];
        bool ok = true;
        F0R(i, n) {
            if (a[i] != a[0]) ok = false;
        }
        if (ok) {
            cout << 1 << endl;
            F0R(i, n) cout << 1 << " ";
            cout << endl;
        } else {
            bool twoEqual = false, endsNotEqual = (a[0] != a[n-1]);
            F0R(i, n-1) if (a[i] == a[i+1]) twoEqual = true;
            if (n&1 && !twoEqual && endsNotEqual) {
                cout << 3 << endl;
                F0R(i, n-1) {
                    if (i&1) cout << 1 << " ";
                    else cout << 2 << " ";
                }
                cout << 3 << endl;
            } else if (n&1 && endsNotEqual) {
                cout << 2 << endl;
                int c = 0;
                F0R(i, n) {
                    if (i && a[i] == a[i-1] && twoEqual) {
                        c++;
                        twoEqual = false;
                    }
                    if (c&1) cout << 1 << " ";
                    else cout << 2 << " ";
                    c++;
                }
                cout << endl;
            } else {
                cout << 2 << endl;
                F0R(i, n) {
                    if (i&1) cout << 1 << " ";
                    else cout << 2 << " ";
                }
                cout << endl;
            }
        }
    }
    return 0;
}
