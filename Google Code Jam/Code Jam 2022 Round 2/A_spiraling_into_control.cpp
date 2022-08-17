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
#include <climits>

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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e4;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int m[MX][MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    F0R(tt, t) {
        int n, k; cin >> n >> k;
        cout << "Case #" << tt+1 << ": ";
        if (k < n-1 || k%2 == 1) {
            cout << "IMPOSSIBLE" << nl;
            continue;
        }
        F0R(i, n) F0R(j, n) m[i][j] = 0;
        int c = 1;
        int x = 0, y = 0, d = 0;
        F0R(i, n*n) {
            m[x][y] = c++;
            int nx = x+dx[d], ny = y+dy[d];
            if (nx >= n || nx < 0 || ny >= n || ny < 0 || m[nx][ny]) {
                d = (d+1)%4;
            }
            x += dx[d];
            y += dy[d];
        }
        // F0R(i, n) {
        //     F0R(j, n) cout << m[i][j] << " ";
        //     cout << nl;
        // }

        x = 0, y = 0, d = 0;
        int mid = (n-1)/2;
        F0R(i, n*n-1) {
            int cur = abs(mid-x) + abs(mid-y);
            if (k == cur+i) {
                vpi v;
                int nx = x+dx[d], ny = y+dy[d];
                int dist = abs(mid-nx) + abs(mid-ny);
                int prev = cur;
                int cnt = 0;
                while (dist <= prev) {
                    cnt++;
                    x = x+dx[d]; y = y+dy[d];
                    nx = x+dx[d]; ny = y+dy[d];
                    prev = dist;
                    dist = abs(mid-nx) + abs(mid-ny);
                    if (cnt > MX) assert(0);
                } 
                d = (d+1)%4;
                nx = x+dx[d], ny = y+dy[d];
                prev = abs(mid-x) + abs(mid-y);
                dist = abs(mid-nx) + abs(mid-ny);
                cnt = 0;
                while (dist <= prev) {
                    if (m[nx][ny] > m[x][y]+1) {
                        v.pb({m[x][y], m[nx][ny]});
                    }
                    x = x+dx[d]; y = y+dy[d];
                    nx = x+dx[d]; ny = y+dy[d];
                    prev = dist;
                    dist = abs(mid-nx) + abs(mid-ny);
                    if (cnt > MX) assert(0);
                } 

                d = (d+1)%4;
                nx = x+dx[d], ny = y+dy[d];
                prev = abs(mid-x) + abs(mid-y);
                dist = abs(mid-nx) + abs(mid-ny);
                cnt = 0;
                while (dist <= prev) {
                    if (m[nx][ny] > m[x][y]+1) {
                        v.pb({m[x][y], m[nx][ny]});
                    }
                    x = x+dx[d]; y = y+dy[d];
                    nx = x+dx[d]; ny = y+dy[d];
                    prev = dist;
                    dist = abs(mid-nx) + abs(mid-ny);
                    if (cnt > MX) assert(0);
                }
                cout << sz(v) << nl;
                trav(vv, v) cout << vv.f << " " << vv.s << nl;
                break;
            }
            int nx = x+dx[d], ny = y+dy[d];
            if (nx >= n || nx < 0 || ny >= n || ny < 0 || m[nx][ny] != m[x][y]+1) {
                d = (d+1)%4;
            }
            x += dx[d];
            y += dy[d];
        }

    }
    
    return 0;
}
