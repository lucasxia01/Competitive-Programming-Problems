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

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 100+5;

int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
struct State {
    int x, y;
    int dir;
};
int r, c;

int outside1[MX*MX], outside2[MX*MX];

vpi v;
int par1[MX*MX], sz1[MX*MX], par2[MX*MX], sz2[MX*MX];

int find1(int i) {
    return (i==par1[i]?i:par1[i]=find1(par1[i]));
}
int find2(int i) {
    return (i==par2[i]?i:par2[i]=find2(par2[i]));
}
void merge1(int a, int b) {
    a = find1(a);
    b = find1(b);
    if (a == b) return;
    if (sz1[a] < sz1[b]) swap(a, b);
    par1[b] = a;
    sz1[a] += sz1[b];
}
void merge2(int a, int b) {
    a = find2(a);
    b = find2(b);
    if (a == b) return;
    if (sz2[a] < sz2[b]) swap(a, b);
    par2[b] = a;
    sz2[a] += sz2[b];
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> r >> c;
    string m[r+2]; FOR(i, 1, r) {
        cin >> m[i];
        m[i] = "."+m[i]+".";
    }
    string temp = "";
    F0R(i, c+2) temp += '.';
    m[0] = m[r+1] = temp;
    r+=2; c+=2;
    
    F0R(i, r) F0R(j, c) {
        par1[i*c+j] = par2[i*c+j] =i*c+j;
        sz1[i*c+j] = sz2[i*c+j] = 1;
    }
    
    queue<State> qA, qB;
    F0R(i, r) F0R(j, c) {
        if (m[i][j] == 'A') qA.push({i, j, -1});
        if (m[i][j] == 'B') qB.push({i, j, -1});
    }
    int a[r][c], b[r][c]; F0R(i, r) F0R(j, c) a[i][j] = b[i][j] = 0;
    while (!qA.empty()) {
        State cur = qA.front(); qA.pop();
        int cnt = 0;
        F0R(d, 4) {
            int nx = cur.x+dx[d], ny = cur.y+dy[d];
            if (nx < 0 || nx >= r || ny < 0 || ny >= c || m[nx][ny] == '.') continue;
            cnt++;
        }
        assert(cnt%2==0);
        if (cnt == 4) {
            int nx = cur.x+dx[cur.dir], ny = cur.y+dy[cur.dir];
            qA.push({nx, ny, cur.dir});
            a[nx][ny] = 1;
        } else {
            F0R(d, 4) {
                int nx = cur.x+dx[d], ny = cur.y+dy[d];
                if (nx < 0 || nx >= r || ny < 0 || ny >= c || m[nx][ny] == '.' || a[nx][ny]) continue;
                qA.push({nx, ny, d});
                a[nx][ny] = 1;
            }
        }
    }
    while (!qB.empty()) {
        State cur = qB.front(); qB.pop();
        int cnt = 0;
        F0R(d, 4) {
            int nx = cur.x+dx[d], ny = cur.y+dy[d];
            if (nx < 0 || nx >= r || ny < 0 || ny >= c || m[nx][ny] == '.') continue;
            cnt++;
        }
        assert(cnt%2==0);
        if (cnt == 4) {
            int nx = cur.x+dx[cur.dir], ny = cur.y+dy[cur.dir];
            qB.push({nx, ny, cur.dir});
            b[nx][ny] = 1;
        } else {
            F0R(d, 4) {
                int nx = cur.x+dx[d], ny = cur.y+dy[d];
                if (nx < 0 || nx >= r || ny < 0 || ny >= c || m[nx][ny] == '.' || b[nx][ny]) continue;
                qB.push({nx, ny, d});
                b[nx][ny] = 1;
            }
        }
    }
//    F0R(i, r) {
//        F0R(j, c) cout << a[i][j] << " ";
//        cout << nl;
//    }
    F0R(i, r) F0R(j, c) {
        if (a[i][j]) continue;
        F0R(d, 4) {
            int nx = i+dx[d], ny = j+dy[d];
            if (nx < 0 || nx >= r || ny < 0 || ny >= c || a[nx][ny] == 1) continue;
            merge1(i*c+j, nx*c+ny);
        }
    }
    F0R(i, r) {
        outside1[find1(i*c+0)] = 1;
        outside1[find1(i*c+c-1)] = 1;
    }
    F0R(j, c) {
        outside1[find1(0*c+j)] = 1;
        outside1[find1((r-1)*c+j)] = 1;
    }
    
//    cout << nl;
//    F0R(i, r) {
//        F0R(j, c) cout << b[i][j] << " ";
//        cout << nl;
//    }
    F0R(i, r) F0R(j, c) {
        if (b[i][j]) continue;
        F0R(d, 4) {
            int nx = i+dx[d], ny = j+dy[d];
            if (nx < 0 || nx >= r || ny < 0 || ny >= c || b[nx][ny] == 1) continue;
            merge2(i*c+j, nx*c+ny);
        }
    }
    F0R(i, r) {
        outside2[find2(i*c+0)] = 1;
        outside2[find2(i*c+c-1)] = 1;
    }
    F0R(j, c) {
        outside2[find2(0*c+j)] = 1;
        outside2[find2((r-1)*c+j)] = 1;
    }
    
    
    int ans[4] = {};
    F0R(i, r) F0R(j, c) {
        if (m[i][j] != '.') continue;
        bool insideA = !outside1[find1(i*c+j)];
        bool insideB = !outside2[find2(i*c+j)];
        int cur = 0;
        if (insideA) cur++;
        if (insideB) cur += 2;
        ans[cur]++;
    }
    cout << ans[1] << " " << ans[2] << " " << ans[3] << nl;
    return 0;
}
