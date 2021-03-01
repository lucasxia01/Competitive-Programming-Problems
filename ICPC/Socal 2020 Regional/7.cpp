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

const int MX = 15, MXM = 50;
int n; char t;
char c[MX];
int M;
vi h[MXM];
ld dp[1<<MX][2][50][MX];

void print(int state, char turn, int hint, int k) {
    bitset<4> bs(state);
    dbg(bs, turn, hint, k);
}

char other(char turn) {
    if (turn == 'R') return 'B';
    else return 'R';
}

int cnvt(char turn) {
    return (turn == t);
}

int checkWinLose(int state, char turn) {
    bool done = 1;
    F0R(ii, n) { // check if we have won
        if (c[ii] == turn && (state&(1<<ii)) == 0) done = 0;
    }
    if (done) return 0;
    done = 1;
    F0R(ii, n) { // check if we have lost
        if (c[ii] == other(turn) && (state&(1<<ii)) == 0) done = 0;
    }
    if (done) return 1;
    return 2;
}

ld solveWithHint(int state, char turn, int hint, int k);
ld solve(int state, char turn) {
    ld p = 0;
    F0R(i, M) {
        int cnt = 0; // number of guys unused in this hint
        trav(j, h[i]) if ((state&(1<<j)) == 0) cnt++;
        FOR(j, 1, cnt) ckmax(p, solveWithHint(state, turn, i, j));
    }
    return p;
}

ld solveWithHint(int state, char turn, int hint, int k) {
    if (dp[state][cnvt(turn)][hint][k] != -1) return dp[state][cnvt(turn)][hint][k];
    if (k == 0) { // turn has ended
        return (1-solve(state, other(turn))); // we want the opposite probability of the other guy
    }
    int cnt = 0;
    trav(i, h[hint]) {
        if ((state&(1<<i)) == 0) {
            cnt++;
        }
    }
    ld q = (ld)1.0/cnt;
    ld ret = 0;
    trav(i, h[hint]) {
        if ((state&(1<<i)) == 0) {
            // we are guessing i
            state |= (1<<i);
            int res = checkWinLose(state, turn);
            // print(state, turn, hint, k);
            // dbg(res, i);
            if (res == 0) ret += 1; // we win
            else if (res == 1) ret += 0; // we lose
            else { // play on
                if (c[i] == 'I' || c[i] == other(turn)) { // turn ends
                    ret += (1-solve(state, other(turn)));
                } else if (c[i] == 'A') {
                    ret += 0;
                } else { // our turn continues
                    ret += solveWithHint(state, turn, hint, k-1); // continue guessing
                }
            }
            state ^= (1<<i);
            // dbg(state, i);
        }
    }
    // if (state == 0) {
    //     print(state, turn, hint, k);
    //     dbg(ret*q);
    // }
    return (dp[state][cnvt(turn)][hint][k]=(ret*q));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    F0R(i, 1<<MX) F0R(j, 2) F0R(k, 50) F0R(l, MX) dp[i][j][k][l] = -1;
    cin >> n; cin >> t;
    map<string, int> m;
    F0R(i, n) {
        string s; cin >> s;
        m[s] = i;
    }
    F0R(i, n) cin >> c[i];
    cin >> M;
    F0R(i, M) {
        int k; cin >> k;
        F0R(j, k) {
            string s; cin >> s;
            h[i].pb(m[s]);
        }
    }
    ld ans = 0;
    int res = checkWinLose(0, t);
    if (res == 0) ans = 1;
    else if (res == 1) ans = 0;
    else ans = solve(0, t);
    
    cout.precision(7);
    cout << fixed << ans << nl;
    return 0;
}