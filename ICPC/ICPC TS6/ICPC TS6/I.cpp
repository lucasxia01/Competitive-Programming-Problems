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

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()


struct yeet {
    bool operator<(const yeet &o) const {
        F0R(i, 26) {
            if (ar[i] != o.ar[i]) return ar[i] < o.ar[i];
        }
        return false;
    }
    int ar[26] = {};
} freqA, freqB;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    while (n--) {
        string a, b;
        cin >> a >> b;
        
        bool printed = false;
        F0Rd(i, (int)a.length()) {
            set<struct yeet> m;
            F0R(k, 26) {
                freqA.ar[k] = 0;
                freqB.ar[k] = 0;
            }
            F0R(k, i) {
                freqB.ar[b[k]-'a']++;
            }
            FOR(k, i, b.length()-1) {
                freqB.ar[b[k]-'a']++;
                //F0R(j, 26) cout << freqB.ar[j] << " ";
                //cout << endl;
                if (m.find(freqB) == m.end()) {
                    m.insert(freqB);
                }
                freqB.ar[b[k-i]-'a']--;
            }
            //cout << endl;
            F0R(k, i) {
                freqA.ar[a[k]-'a']++;
            }
            FOR(k, i, a.length()-1) {
                freqA.ar[a[k]-'a']++;
//                F0R(j, 26) cout << freqA.ar[j] << " ";
//                cout << endl;
                if (m.find(freqA) != m.end()) {
                    cout << a.substr(k-i, i+1) << endl;
                    printed = true;
                    break;
                }
                freqA.ar[a[k-i]-'a']--;
            }
            //cout << endl;
            if (printed) {
                break;
            }
        }
        if (!printed) cout << "NONE" << endl;
    }
    return 0;
}
