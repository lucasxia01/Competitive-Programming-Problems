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
    ll T;
    cin >> T;
    string c;
    while (T) {
        cin >> c;
        ll hor = 0;
        ll ver = 0;
        ll maxHor = 0;
        ll minHor = 0;
        ll maxVer = 0;
        ll minVer = 0;
        F0R(i, (int)c.length()) {
            switch(c[i]) {
                case 'S':
                    ver--; break;
                case 'D':
                    hor++; break;
                case 'W':
                    ver++; break;
                case 'A':
                    hor--; break;
            }
            maxHor = max(maxHor, hor);
            minHor = min(minHor, hor);
            maxVer = max(maxVer, ver);
            minVer = min(minVer, ver);
        }
        ll area = (maxHor-minHor+1)*(maxVer-minVer+1);
        if (maxHor-minHor > 1) {
            hor = 0;
            ll firstMin = -1, lastMin = -1;
            ll firstMax = -1, lastMax = -1;
            if (hor == maxHor) {
                if (firstMax == -1) firstMax = 0;
                lastMax = 0;
            }
            if (hor == minHor) {
                if (firstMin == -1) firstMin = 0;
                lastMin = 0;
            }
            F0R(i, (int)c.length()) {
                switch(c[i]) {
                    case 'D':
                        hor++; break;
                    case 'A':
                        hor--; break;
                    default:
                        ;
                }
                if (hor == maxHor) {
                    if (firstMax == -1) firstMax = i;
                    lastMax = i;
                }
                if (hor == minHor) {
                    if (firstMin == -1) firstMin = i;
                    lastMin = i;
                }
            }
            if (firstMin > lastMax || firstMax > lastMin) {
                area = min(area, (maxHor-minHor)*(maxVer-minVer+1));
            }
        }
        if (maxVer-minVer > 1) {
            ver = 0;
            ll firstMin = -1, lastMin = -1;
            ll firstMax = -1, lastMax = -1;
            if (ver == maxVer) {
                if (firstMax == -1) firstMax = 0;
                lastMax = 0;
            }
            if (ver == minVer) {
                if (firstMin == -1) firstMin = 0;
                lastMin = 0;
            }
            F0R(i, (int)c.length()) {
                switch(c[i]) {
                    case 'W':
                        ver++; break;
                    case 'S':
                        ver--; break;
                    default:
                        ;
                }
                if (ver == maxVer) {
                    if (firstMax == -1) firstMax = i;
                    lastMax = i;
                }
                if (ver == minVer) {
                    if (firstMin == -1) firstMin = i;
                    lastMin = i;
                }
            }
            if (firstMin > lastMax || firstMax > lastMin) {
                area = min(area, (maxHor-minHor+1)*(maxVer-minVer));
            }
        }
        
        cout << area << endl;
        T--;
    }
    return 0;
}
