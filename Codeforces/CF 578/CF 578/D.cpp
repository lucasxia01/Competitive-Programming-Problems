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
    int n, k;
    cin >> n >> k;
    string a[n];
    F0R(i, n) cin >> a[i];
    
    pi row[n];
    pi col[n];
    int wL = 0;
    F0R(i, n) {
        int minI = n, maxI = n;
        F0R(j, n) {
            if (a[i][j] == 'B') {
                minI = min(minI, j);
                maxI = j;
            }
        }
        if (minI == n) wL++;
        row[i] = make_pair(minI, maxI);
        //cout << row[i].f << " " << row[i].s << endl;
    }
    F0R(i, n) {
        int minI = n, maxI = n;
        F0R(j, n) {
            if (a[j][i] == 'B') {
                minI = min(minI, j);
                maxI = j;
            }
        }
        if (minI == n) wL++;
        col[i] = make_pair(minI, maxI);
        //cout << col[i].f << " " << col[i].s << endl;
    }
    //cout << wL << endl;
    int ans = wL;
    int base[n];
    F0R(i, n-k+1) {
        base[i] = wL;
        F0R(j, k) {
            if (0 <= row[i+j].f && k > row[i+j].s) base[i]++;
            if (i <= col[j].f && i+k > col[j].s) base[i]++;
        }
        ans = max(ans, base[i]);
    }
    int numMins[n-k+1][n];
    int numMaxs[n-k+1][n];
    F0R(i, n-k+1) {
        F0R(j, n) {
            numMins[i][j] = 0;
            numMaxs[i][j] = 0;
        }
    }
    //cerr << "NUMMINS" << endl;
    F0R(i, n) {
        F0R(j, k) {
            if (row[j].f == i && row[j].s < i+k) {
                numMins[0][i]++;
            }
            if (row[j].s == i && row[j].f > i-k) {
                numMaxs[0][i]++;
            }
            //cerr << numMaxs[0][i] << endl;
        }
    }
    F0R(i, n) {
        //cout << "COL " << i << endl;
        FOR(j, 1, n-k+1) {
            numMins[j][i] = numMins[j-1][i];
            if (row[j-1].f == i && row[j-1].s < i+k) numMins[j][i]--;
            if (row[j+k-1].f == i && row[j+k-1].s < i+k) numMins[j][i]++;
            
            numMaxs[j][i] = numMaxs[j-1][i];
            if (row[j-1].s == i && row[j-1].f > i-k) numMaxs[j][i]--;
            if (row[j+k-1].s == i && row[j+k-1].f > i-k) numMaxs[j][i]++;
            //cout << numMaxs[j][i] << endl;
        }
        
    }
    F0R(i, n-k+1) {
        int count = base[i];
        //cout << "base value row " << i << ": " << base[i] << endl;
        FOR(j, 1, n-k+1) {
            count -= numMins[i][j-1];
            count += numMaxs[i][j+k-1];
            //cout << numMins[i][j-1] << " " << numMaxs[i][j+k-1] << endl;
            if (i <= col[j-1].f && i+k > col[j-1].s) count--;
            if (i <= col[j+k-1].f && i+k > col[j+k-1].s) count++;
            ans = max(ans, count);
            //cout << "col " << j << ": " << count << endl;
        }
    }
    cout << ans << endl;
    return 0;
}
