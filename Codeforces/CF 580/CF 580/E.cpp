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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int board[n+1][n+1][2];
    F0R(i, n) F0R(j, n) board[i+1][j+1][0] = -1;
    board[1][1][0] = 1;
    board[1][2][0] = 1; // guess
    board[n][n][0] = 0;
    int res = 0;
    int count = 0;
    F0R(i, n/2) {
        printf("? %d %d %d %d\n", 1, 2*i+1, 2, 2*i+2); count++; fflush(stdout);
        cin >> res;
        if (res == -1) exit(0);
        board[2][2*i+2][0] = (1-res)^board[1][2*i+1][0];
        printf("? %d %d %d %d\n", 1, 2*i+1, 1, 2*i+3); count++; fflush(stdout);
        cin >> res;
        if (res == -1) exit(0);
        board[1][2*i+3][0] = (1-res)^board[1][2*i+1][0];
        
        printf("? %d %d %d %d\n", 1, 2*i+2, 2, 2*i+3); count++; fflush(stdout);
        cin >> res;
        if (res == -1) exit(0);
        board[2][2*i+3][0] = (1-res)^board[1][2*i+2][0];
        if (i == n/2-1) break;
        printf("? %d %d %d %d\n", 1, 2*i+2, 1, 2*i+4); count++; fflush(stdout);
        cin >> res;
        if (res == -1) exit(0);
        board[1][2*i+4][0] = (1-res)^board[1][2*i+2][0];
    }
    cout << "? 2 1 2 3" << endl; count++; fflush(stdout);
    cin >> res;
    if (res == -1) exit(0);
    board[2][1][0] = (1-res)^board[2][3][0];
    
    FOR(i, 1, n+1) {
        FOR(j, 3, n+1) {
            printf("? %d %d %d %d\n", j-2, i, j, i); count++; fflush(stdout);
            cin >> res;
            if (res == -1) exit(0);
            board[j][i][0] = (1-res)^board[j-2][i][0];
        }
    }
    
    F0R(i, n) {
        F0R(j, n) {
            if ((i+j)%2)board[i+1][j+1][1] = 1-board[i+1][j+1][0];
            else board[i+1][j+1][1] = board[i+1][j+1][0];
            //cout << (board[j+1][i+1][0]);
        }
        //cout << endl;
    }
    int dp[n+1][n+1][n+1][n+1][2];
    FOR(dx,0,n) {
        FOR(dy,0,n) {
            FOR(i, 1, n+1) {
                FOR(j, 1, n+1) {
                    if (i+dx > n || j+dy > n) continue;
                    F0R(k, 2) {
                        if (dx + dy == 0) {
                            dp[i][j][i][j][k] = 1;
                            continue;
                        }
                        dp[i][j][i+dx][j+dy][k] = 0;
                        if (board[i][j][k] == board[i+dx][j+dy][k]) {
                            if (dx + dy == 1) dp[i][j][i+dx][j+dy][k] = 1;
                            if ((dx > 0 && dy > 0 && dp[i+1][j][i+dx][j+dy-1][k]) ||
                                (dx > 0 && dy > 0 && dp[i][j+1][i+dx-1][j+dy][k]) ||
                                (dx > 1 && dp[i+1][j][i+dx-1][j+dy][k]) ||
                                (dy > 1 && dp[i][j+1][i+dx][j+dy-1][k])) {
                                dp[i][j][i+dx][j+dy][k] = 1;
                            }
                        }
                    }
                    if (dx + dy > 1 && dp[i][j][i+dx][j+dy][0] != dp[i][j][i+dx][j+dy][1]) {
                        printf("? %d %d %d %d\n", i, j, i+dx, j+dy); count++; fflush(stdout);
                        cin >> res;
                        if (res == -1) exit(0);
                        int x = res == dp[i][j][i+dx][j+dy][0] ? 0 : 1;
                        cout << "!" << endl;
                        F0R(i, n) {
                            F0R(j, n) {
                                cout << board[i+1][j+1][x];
                            } cout << endl;
                        }
                        fflush(stdout);
                        exit(0);
                    }
                }
            }
            
        }
    }
//    F0R(i, n) {
//        F0R(j, n) {
//            FOR(ii, i, n) {
//                FOR(jj, j, n) {
//                    printf("%d %d %d %d: %d %d\n", i+1, j+1, ii+1, jj+1, dp[i+1][j+1][ii+1][jj+1][0], dp[i+1][j+1][ii+1][jj+1][1]);
//                    
//                }
//            }
//        }
//    }
//    cout << count << endl;
    return 0;
}
