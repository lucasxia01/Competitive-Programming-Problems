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

const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t, n, d;
    cin >> t;
    int tri[5011];
    tri[0] = 0;
    F0R(i, 5010) {
        tri[i+1] = tri[i] + i;
    }
    while (t--) {
        cin >> n >> d;
        int total = 0;
        int pow = 1;
        int count = 0;
        int minD = 0;
        int a[n];
        F0R(i, n) a[i] = 0;
        while (total+pow <= n) {
            a[count] = pow;
            total += pow;
            minD += count * pow;
            count++;
            pow *= 2;
        }
        minD += (n-total)*count;
        a[count] += n-total;
        //cout << minD << " " << tri[n] << endl;
        if (d >= minD && d <= tri[n]) {
            cout << "YES" << endl;
            F0R(i, d-minD) {
                F0Rd(j, n-1) {
                    if (a[j] > 1) {
                        a[j]--;
                        a[j+1]++;
                        break;
                    }
                }
            }
            int par = 1;
            int cur = 2, nextPar = 0;
            FOR(i, 1, n-1) {
                int count = 0;
                nextPar = cur;
                while (a[i]--) {
                    cout << par << " ";
                    cur++;
                    count++;
                    if (count % 2 == 0) par++;
                }
                par =  nextPar;
            }
            cout << endl;
        } else cout << "NO" << endl;
    }
    return 0;
}
