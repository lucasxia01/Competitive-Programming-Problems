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
#include <bitset>

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

const int MX = 1<<20;

string nums[10] = {"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};

int convert(string a, string b) { // a to b
    int ans = 0;
    F0R(i, 7) {
        if (a[i]=='0' && b[i]=='1') ans++;
        if (a[i]=='1' && b[i]=='0') return -1;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    string a[n];
    F0R(i, n) cin >> a[n-1-i];
    int dp[n+1][k+1];
    F0R(i, n+1) F0R(j, k+1) dp[i][j] = 0;
    dp[0][0] = 1;
    FOR(i, 1, n) {
        F0R(j, k+1) {
            if (!dp[i-1][j]) continue;
            F0R(m, 10) {
                int ret = convert(a[i-1], nums[m]);
                if (ret == -1 || j+ret > k) continue;
                dp[i][j+ret] = 1;
            }
        }
    }
    if (!dp[n][k]) {
        cout << -1 << endl;
        return 0;
    }
    int cur = k;
    FORd(i, 1, n) {
        F0Rd(m, 10) {
            int ret = convert(a[i-1], nums[m]);
            if (ret == -1 || cur-ret < 0 || !dp[i-1][cur-ret]) continue;
            cout << (char)(m+'0');
            cur -= ret;
            break;
        }
    }
    
    return 0;
}
