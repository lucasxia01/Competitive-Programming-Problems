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
#include <cassert>

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

const int MX = 5e5 +5;
int n;
int nextStart[MX], length[MX];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s;
    getline(cin, s);
    n = (int) s.length();
    int start = 0;
    int maxLen = 0;
    F0R(i, n) {
        if (i == 0) {
            int j = 0;
            while (j < n && s[j] != ' ') j++;
            length[i] = j;
            ckmax(maxLen, j);
        } else if (i != n-1 && s[i] == ' ') {
            int j = i+1;
            while (j < n && s[j] != ' ') j++;
            length[i+1] = j-i-1; // doesn't include the space
            ckmax(maxLen, length[i+1]);
            start = i+1;
        }
        nextStart[i] = start;
        assert(start < n);
    }
    int a, b;
    cin >> a >> b;
    FOR(i, a, b) {
        // simulate it
        int ans = 0;
        for (int j = 0; j < n;) {
            ans += length[j];
            ans++; // count the space if it exists or if its the last one
            if (j+i < n) j = nextStart[j+i];
            else break;
        }
        cout << ans-1 << '\n'; // subtract the space at the end
    }
    return 0;
}
