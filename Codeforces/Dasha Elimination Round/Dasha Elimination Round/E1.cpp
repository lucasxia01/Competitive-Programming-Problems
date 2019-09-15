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
    int t, n, m;
    cin >> t;
    while (t) {
        cin >> n >> m;
        int a[n][m];
        int used[n][m];
        int b[n*m];
        F0R(i, n) {
            F0R(j, m) {
                cin >> a[i][j];
                used[i][j] = 0;
                b[i*m+j] = a[i][j];
            }
        }
        sort(b, b+(n*m));
        int ans = 0;
        vpi rows;
        int cols[101];
        F0R(i, min(n, 3)) {
            ans += b[n*m-1-i];
            F0R(x, n) {
                F0R(y, m) {
                    if (!used[x][y] && a[x][y] == b[n*m-1-i]) {
                        used[x][y] = 1;
                        cols[y]++;
                        rows.pb(mp(x, y));
                        y = m; x = n; break;
                    }
                }
            }
        }
        if (n <= 3) {
            cout << ans << endl;
        } else {
            int k = 3;
            
            int col = -1, row = -1;
            F0R(x, n) {
                F0R(y, m) {
                    if (!used[x][y] && a[x][y] == b[n*m-1-k]) {
                        used[x][y] = 1;
                        col = y;
                        row = x;
                        y = m; x = n; break;
                    }
                }
            }
            int count = 0;
            cols[col]++;
            F0R(i, m) {
                if (cols[i] >= 2) count++;
            }
            if (count == 2) {
                int ans = 0;
                F0R(i, m) {
                    F0R(j, m) {
                        if (i != j) {
                            FOR(diff, 1, 3) {
                                F0R(s1, 4) {
                                    F0R(s2, 4) {
                                        ans = max(ans, a[i][s1] + a[i][(s1+diff)%4] + a[j][s2] + a[j][(s2+diff)%4]);
                                    }
                                }
                            }
                        }
                    }
                }
                cout << ans << endl;
                
            } else {
                ans += b[n*m-4];
                cout << ans << endl;
            }
        }
        t--;
    }
    return 0;
}
