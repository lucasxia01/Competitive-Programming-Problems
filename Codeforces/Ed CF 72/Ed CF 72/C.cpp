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

int pow(int x) {
    int ans = 1;
    F0R(i, x) {
        ans *= 2;
    }
    return ans;
}
string intToStr(int i) {
    string s = "";
    int x = i;
    F0R(j, x) {
        if (i % 2 == 0) s = '0' + s;
        else s = '1' + s;
        i /= 2;
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t) {
        string s;
        cin >> s;
        int slen = (int) s.length();
        int l = 1;
        int p = 1;
        while (p < s.length()) {
            p*=2;
            l++;
        }
        ll ans = 0;
        int ones[slen+1];
        ones[slen] = 0;
        F0Rd(i, slen) {
            ones[i] = ones[i+1];
            if (s[i] == '1') ones[i]++;
        }
        F0Rd(i, slen) {
            ll len = 1;
            while (len <= s.length()) {
                string curS = "";
                if (i-len < -1) break;
                FORd(j, i-len+1, i+1) {
                    curS += s[j];
                }
                //cout << curS << endl;
                ll x = 0;
                p = 1;
                F0R(j, curS.length()) {
                    x += p*(curS[j]-'0');
                    if (x > slen) {
                        x = -1;
                        break;
                    }
                    if (p <= slen) p*=2;
                    else {
                        if (ones[i-len+1]-ones[i-j]) x = -1;
                        break;
                    }
                    
                }
                
                if (len == x) {
//                    cout << curS << endl;
//                    cout << x << " " << i << endl;
                    ans++;
                }
                //if (i == 7) cout << x << ": " << len << endl;
                if (x > len) {
                    len = x;
                    continue;
                }
                if (len > l) break;
                len = x + pow(len);
            }
        }
        cout << ans << endl;
        t--;
    }
    return 0;
}
