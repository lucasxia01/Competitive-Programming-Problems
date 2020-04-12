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

const int MX = 1<<20;

void print(int i, ll x) {
    cout << "Case #" << i << ": " << x << "\n";
}

int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    FOR(t, 1, T) {
        int r, c;
        cin >> r >> c;
        ll s[r][c];
        ll sum = 0;
        F0R(i, r) F0R(j, c) {
            cin >> s[i][j];
            sum += s[i][j];
        }
        bool done = false;
        ll ans = 0;
        while (!done) {
            done = true;
            ans += sum;
            vpi marked;
            F0R(i, r) F0R(j, c) {
                if (s[i][j] == 0) continue;
                ll total = 0;
                int count = 0;
                F0R(d, 4) {
                    int x = i, y = j;
                    do {
                        x += dx[d]; y += dy[d];
                    } while (x >= 0 && x < r && y >= 0 && y < c && !s[x][y]);
                    if (x >= 0 && x < r && y >= 0 && y < c) {
                        total += 1LL*s[x][y];
                        count++;
                    }
                }
                // cout << i << " " << j << " " << total << " " << count << endl;
                if (!count) continue;
                if (s[i][j]*count < total) {
                    marked.pb(mp(i, j));
                    done = false;
                }
            }
            trav(a, marked) {
                sum -= s[a.f][a.s];
                s[a.f][a.s] = 0;
            }
        }
        print(t, ans);
    }
    return 0;
}
