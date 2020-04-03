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
#include <random>
#include <chrono>

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
#define sz(x) (int)x.size()

const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string d[77] = {"xxxxx",
                        "x...x",
                        "x...x",
                        "x...x",
                        "x...x",
                        "x...x",
                        "xxxxx",
                        "....x",
                        "....x",
                        "....x",
                        "....x",
                        "....x",
                        "....x",
                        "....x",
                        "xxxxx",
                        "....x",
                        "....x",
                        "xxxxx",
                        "x....",
                        "x....",
                        "xxxxx",
                        "xxxxx",
                        "....x",
                        "....x",
                        "xxxxx",
                        "....x",
                        "....x",
                        "xxxxx",
                        "x...x",
                        "x...x",
                        "x...x",
                        "xxxxx",
                        "....x",
                        "....x",
                        "....x",
                        "xxxxx",
                        "x....",
                        "x....",
                        "xxxxx",
                        "....x",
                        "....x",
                        "xxxxx",
                        "xxxxx",
                        "x....",
                        "x....",
                        "xxxxx",
                        "x...x",
                        "x...x",
                        "xxxxx",
                        "xxxxx",
                        "....x",
                        "....x",
                        "....x",
                        "....x",
                        "....x",
                        "....x",
                        "xxxxx",
                        "x...x",
                        "x...x",
                        "xxxxx",
                        "x...x",
                        "x...x",
                        "xxxxx",
                        "xxxxx",
                        "x...x",
                        "x...x",
                        "xxxxx",
                        "....x",
                        "....x",
                        "xxxxx",
                        ".....",
                        "..x..",
                        "..x..",
                        "xxxxx",
                        "..x..",
                        "..x..",
                        "....."
    };
    string s[7];
    F0R(i, 7) getline(cin, s[i]);
    // first num
    int i = 0;
    int f = 0;
    while (1) {
        bool plus = false;
        F0R(j, 11) {
            bool good = true;
            F0R(x, 7) F0R(y, 5) {
                if (d[j*7+x][y] != s[x][i*6+y]) {
                    good = false;
                    break;
                }
            }
            if (good) {
                if (j == 10) {
                    plus = true;
                    break;
                }
                f = 10*f + j;
                break;
            }
        }
        i++;
        if (plus) break;
    }
    int n = (int)s[0].length()/5;
    int sN = 0;
    for (; i < n; i++) {
        F0R(j, 11) {
            bool good = true;
            F0R(x, 7) F0R(y, 5) {
                if (d[j*7+x][y] != s[x][i*6+y]) {
                    good = false;
                    break;
                }
            }
            if (good) {
                sN = 10*sN + j;
                break;
            }
        }
    }
    string ans = to_string(f + sN);
    F0R(j, 7) {
        F0R(i, (int)ans.length()) {
            if (i) cout << ".";
            cout << d[7*(ans[i]-'0')+j];
        }
        cout << endl;
    }
    return 0;
}
