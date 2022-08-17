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

ll gcd(ll a, ll b) {
    if (a > b) return gcd (b, a);
    if (a == 0) return b;
    return gcd(b%a, a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll q, n, x, a, y, b;
    ll k;
    cin >> q;
    while (q--) {
        cin >> n;
        ll p[n];
        F0R(i, n) cin >> p[i];
        cin >> x >> a;
        cin >> y >> b;
        cin >> k;
        sort(p, p+n);
        ll lo = 1, hi = n+1, mid = (n+2)/2, sum = 0;
        while (lo < hi) {
            mid = (lo + hi)/2;
            sum = 0;
            ll both = mid/((a*b)/gcd(a,b));
            ll justA = mid/a-both, justB = mid/b-both;
            ll i = n-1;
            for (; i >= n-both; i--) {
                sum += p[i]/100 * (x + y);
            }
            if (x > y) {
                F0R(j, justA) {
                    if (i < 0) {
                        sum = -(1LL<<60);
                        break;
                    }
                    sum += p[i]/100 * x;
                    i--;
                }
                F0R(j, justB) {
                    if (i < 0) {
                        sum = -(1LL<<60);
                        break;
                    }
                    sum += p[i]/100 * y;
                    i--;
                }
            } else {
                F0R(j, justB) {
                    if (i < 0) {
                        sum = -(1LL<<60);
                        break;
                    }
                    sum += p[i]/100 * y;
                    i--;
                }
                F0R(j, justA) {
                    if (i < 0) {
                        sum = -(1LL<<60);
                        break;
                    }
                    sum += p[i]/100 * x;
                    i--;
                }
            }
//            cout << both << " " << justA << " " << justB << endl;
//            cout << mid << " " << sum << endl;
            if (sum < k) lo = mid+1;
            else hi = mid;
        }
        mid = (lo+hi)/2;
        sum = 0;
        ll both = mid/((a*b)/gcd(a,b));
        ll justA = mid/a-both, justB = mid/b-both;
        ll i = n-1;
        for (; i >= n-both; i--) {
            sum += p[i]/100 * (x + y);
        }
        if (x > y) {
            F0R(j, justA) {
                if (i < 0) {
                    sum = -(1LL<<60);
                    break;
                }
                sum += p[i]/100 * x;
                i--;
            }
            F0R(j, justB) {
                if (i < 0) {
                    sum = -(1LL<<60);
                    break;
                }
                sum += p[i]/100 * y;
                i--;
            }
        } else {
            F0R(j, justB) {
                if (i < 0) {
                    sum = -(1LL<<60);
                    break;
                }
                sum += p[i]/100 * y;
                i--;
            }
            F0R(j, justA) {
                if (i < 0) {
                    sum = -(1LL<<60);
                    break;
                }
                sum += p[i]/100 * x;
                i--;
            }
        }
//        cout << both << " " << justA << " " << justB << endl;
//        cout << mid << " " << sum << endl;
        if (mid > n || sum < k) cout << -1 << endl;
        else cout << mid << endl;
    }
    return 0;
}
