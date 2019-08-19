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
const ll MOD = 998244353; //
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    int colors[m];
    int changes = 1;
    F0R(i, m) {
        cin >> colors[i];
        if (i != 0 && colors[i] != colors[i-1]) changes++;
    }
    int cColors[changes];
    if (changes >= 2*n) {
        cout << 0 << endl;
        return 0;
    }
    cColors[0] = colors[0];
    changes = 1;
    FOR(i, 1, m) {
        if (colors[i] != colors[i-1]) {
            cColors[changes] = colors[i];
            changes++;
        }
    }
    m = changes;
//    F0R(i, m) {
//        cout << cColors[i] << " ";
//    } cout << endl;
    int minMaxCol[n+1][2];
    FOR(i, 1, n+1) {
        int minI = m+1, maxI = -1;
        F0R(j, m) {
            if (cColors[j] == i) {
                minI = min(minI, j);
                maxI = max(maxI, j);
            }
        }
        minMaxCol[i][0] = minI;
        minMaxCol[i][1] = maxI;
    }

    int minmaxIdx[m][m][2];
    F0R(i, m) F0R(j, m) {
        int min = m+1;
        minmaxIdx[i][j][0] = -1;
        minmaxIdx[i][j][1] = -1;
        for (int k = i; k <= j; k++) {
            if (cColors[k] < min) {
                min = cColors[k];
                minmaxIdx[i][j][0] = k;

            }
            if (cColors[k] <= min) {
                minmaxIdx[i][j][1] = k;
            }
        }
        //cout << i << " " << j << ": " << min << " " << minmaxIdx[i][j][0] << " " << minmaxIdx[i][j][1] << endl;
    }
    
    long long dp[m+1][m+1], sum = 0, sum1 = 0, a, b; // left, right not inclusive
    for (int length = 0; length <= m; length++) {
        for (int i = 0; i + length <= m; i++) {
            dp[i][i+length] = 1;
            if (length == 0) continue;

            sum = 0;
            int j = minmaxIdx[i][i+length-1][0];
            int j2 = minmaxIdx[i][i+length-1][1];
            int minColor = cColors[minmaxIdx[i][i+length-1][0]];
            if (minMaxCol[minColor][0] < i || minMaxCol[minColor][1] >= i+length) {
                dp[i][i+length] = 0;
                continue;
            }
            //cout << j << endl;
            for (int k = i; k <= j; k++) {
                a = dp[i][k];
                b = dp[k][j];
                sum = (sum+(a*b)%MOD)%MOD;
            }
            //if (length == m) cout << minColor << " " << j << " " << j2 << endl;
            //cout << i << " " << i+length << ": " << sum << endl;
            int fir = j;
            for (int k = j+1; k <= j2; k++) {
                if (cColors[k] == minColor) {
                    dp[i][i+length] = (dp[i][i+length]*dp[fir+1][k]) % MOD;
                    fir = k;
                    //if (length == m) cout << k << endl;
                }
            }
            sum1 = 0;
            for (int k = j2+1; k <= i+length; k++) {
                a = dp[k][i+length];
                b = dp[j2+1][k];
                sum1 = (sum1+(a*b)%MOD)%MOD;
            }
            //cout << i << " " << i+length << ": " << sum1 << endl;
            dp[i][i+length] = (dp[i][i+length]*((sum*sum1)%MOD))%MOD;
        }
    }
    //cout << minmaxIdx[0][m-1][0] << endl;
    //cout << dp[1][8] << endl;
    cout << dp[0][m] << endl;
    
    return 0;
}
