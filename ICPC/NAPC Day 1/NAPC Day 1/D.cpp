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

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

struct Sphere {
    int r, x, y, z;
};

const int MX = 1e4 + 5;
Sphere holes[MX];
int n;

ld cb(ld x) {
    return x*x*x;
}
ld vol(ld z) {
    // compute volume given this z;
    ld totalVolume = z*1e5*1e5;
    
    F0R(i, n) {
        ld r = holes[i].r, h = holes[i].z+holes[i].r-z;
        if (holes[i].z - holes[i].r >= z) continue; // sphere over z
        else {
            totalVolume -= cb(r)*4/3*PI;
            if (h > 0) totalVolume += PI*h*h*(r-h/3);
        }
    }
    return totalVolume;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int s;
    cin >> n >> s;
    cout.precision(8);
    
    ld totalVolume = cb(1e5);
    F0R(i, n) {
        cin >> holes[i].r >> holes[i].x >> holes[i].y >> holes[i].z;
        totalVolume -= (ld)4/3*PI*cb(holes[i].r);
    }
    ld sliceVolume = totalVolume/s;
    //cout << fixed << sliceVolume << endl;
    ld prev = 0;
    FOR(i, 1, s) {
        // binary search for sliceVolume*i;
        ld l = 0, h = 1e5;
        F0R(j, 100) {
            ld mid = (l+h)/2;
            //cout << mid << " " << vol(mid) << " " << sliceVolume*i << endl;
            if (vol(mid) > sliceVolume*i) h = mid;
            else l = mid;
        }
        cout << fixed << ((l+h)/2-prev)/1000 << endl;
        prev = (l+h)/2;
    }
    
}
