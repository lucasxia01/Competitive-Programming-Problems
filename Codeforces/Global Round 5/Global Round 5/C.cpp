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
    int n;
    cin >> n;
    pair<pi, pi> a[n];
    F0R(i, n) {
        cin >> a[i].f.f >> a[i].f.s >> a[i].s.f;
        a[i].s.s = i+1;
    }
    sort(a, a+n);
    int m[n];
    F0R(i, n) m[i] = 0;
    F0R(k, 3) {
        int i = 0;
        int j = 0;
        while (j < n) {
            if (m[j]) {
                j++;
                while (j < n && m[j]) j++;
                i = j;
                j++;
                while (j < n && m[j]) j++;
            } else {
                i = j;
                j++;
                while (j < n && m[j]) j++;
            }
            if (j >= n) break;
            //cout << i << " " << j << endl;
            if ((k == 0 && a[i].f.f == a[j].f.f && a[i].f.s == a[j].f.s) ||
                (k == 1 && a[i].f.f == a[j].f.f) ||
                (k == 2)) {
                m[i] = 1;
                m[j] = 1;
                //cout << "marked" << endl;
                cout << a[i].s.s << " " << a[j].s.s << endl;
            }
        }
    }
    
    return 0;
}
